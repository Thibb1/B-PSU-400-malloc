/*
** EPITECH PROJECT, 2022
** malloc
** File description:
** my_memory
*/

#include "my_memory.h"

void *base = NULL;

t_block find_block(t_block *last, size_t size) {
    t_block block = base;

    while (block && !(block->free && block->size >= size)) {
        *last = block;
        block = block->next;
    }
    return block;
}

int valid_addr(void *ptr) {
    if (base && ptr > base && ptr < sbrk(0))
        return (ptr == get_block(ptr)->ptr);
    return 0;
}

void *malloc(size_t size) {
    t_block last = base;
    size_t sa = align4(size);
    t_block block = base ? find_block(&last, sa) : extend_heap(last, sa);

    if (base) {
        if (block) {
            if ((block->size - sa) >= (BLOCK_SIZE + 4))
                split_block(block, sa);
            block->free = 0;
        } else {
            block = extend_heap(last, sa);
            if (!block)
                return NULL;
        }
    } else {
        if (!block)
            return NULL;
        base = block;
    }
    return block->data;
}

void free(void *ptr) {
    t_block block;

    if (valid_addr(ptr)) {
        block = get_block(ptr);
        block->free = 1;
        if (block->prev && block->prev->free)
            block = fusion(block->prev);
        if (block->next)
            fusion(block);
        else {
            if (block->prev)
                block->prev->next = NULL;
            else
                base = NULL;
            brk(block);
        }
    }
}
