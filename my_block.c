/*
** EPITECH PROJECT, 2022
** malloc
** File description:
** my_block
*/

#include "my_memory.h"

t_block extend_heap(t_block last, size_t size) {
    t_block block = sbrk(0);

    if (sbrk(BLOCK_SIZE + size) == (void *)-1)
        return NULL;
    block->size = size;
    block->next = NULL;
    block->prev = last;
    block->ptr = block->data;
    block->free = 0;
    if (last)
        last->next = block;
    return block;
}

void split_block(t_block block, size_t size) {
    t_block new_block = (t_block)block->data + size;

    new_block->size = block->size - size - BLOCK_SIZE;
    new_block->next = block->next;
    new_block->prev = block;
    new_block->free = 1;
    new_block->ptr = new_block->data;
    block->size = size;
    block->next = new_block;
    if (new_block->next)
        new_block->next->prev = new_block;
}


t_block fusion(t_block block) {
    if (block->next && block->next->free) {
        block->size += BLOCK_SIZE + block->next->size;
        block->next = block->next->next;
        if (block->next)
            block->next->prev = block;
    }
    return block;
}

t_block get_block(void *ptr) {
    char *tmp = ptr;
    return (t_block)(tmp - BLOCK_SIZE);
}

void copy_block(t_block src, t_block dst) {
    int *src_data = src->ptr;
    int *dst_data = dst->ptr;
    size_t i = 0;

    for (i = 0; i * 4 < src->size && i * 4 < dst->size; i++)
        *(dst_data + i) = *(src_data + i);
}
