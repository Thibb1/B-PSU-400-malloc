/*
** EPITECH PROJECT, 2022
** malloc
** File description:
** my_block
*/

#include "my_memory.h"

void split_block(t_block block, size_t size)
{
    t_block new_block = GET_DATA(block) + size;

    ASSERT(block->size > ALIGN_SIZE(size + BLOCK_SIZE));
    new_block->size = block->size - size - BLOCK_SIZE;
    new_block->next = block->next;
    new_block->prev = block;
    new_block->free = 1;
    block->size = size;
    block->next = new_block;
    if (new_block->next)
        new_block->next->prev = new_block;
    if (*my_base() < new_block)
        *my_base() = new_block;
}
