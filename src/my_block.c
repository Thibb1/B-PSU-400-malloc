/*
** EPITECH PROJECT, 2022
** malloc
** File description:
** my_block
*/

#include "my_memory.h"

t_block extend_heap(t_block last, size_t size)
{
    t_block block = last ? last : sbrk(0);
    size_t new_size = get_page_size(size);

    if (sbrk(new_size) == (void *)-1)
        return NULL;
    block->size = new_size + (last ? last->size : 0) - BLOCK_SIZE;
    block->next = NULL;
    block->prev = (last ? last->prev : last);
    block->ptr = (last ? last->ptr : (void *)block + BLOCK_SIZE);
    block->free = 1;
    return block;
}

void split_block(t_block block, size_t size)
{
    t_block new_block = block->ptr + size;

    new_block->size = block->size - size - BLOCK_SIZE;
    new_block->next = block->next;
    new_block->prev = block;
    new_block->free = 1;
    new_block->ptr = (void *)new_block + BLOCK_SIZE;
    block->size = size;
    block->next = new_block;
    if (new_block->next)
        new_block->next->prev = new_block;
}

t_block fusion(t_block block)
{
    if (block->next && block->next->free) {
        block->size += block->next->size + BLOCK_SIZE;
        block->next = block->next->next;
        if (block->next)
            block->next->prev = block;
    }
    return block;
}

t_block get_block(void *ptr)
{
    char *tmp = ptr - BLOCK_SIZE;
    ptr = tmp;
    return ptr;
}

void copy_block(t_block src, t_block dst)
{
    char *src_data = src->ptr;
    char *dst_data = dst->ptr;
    size_t i = 0;

    for (i = 0; i < src->size && i < dst->size; i++)
        *(dst_data + i) = *(src_data + i);
}
