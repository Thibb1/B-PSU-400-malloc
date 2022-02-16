/*
** EPITECH PROJECT, 2022
** malloc
** File description:
** my_free
*/

#include "my_memory.h"

void my_free(void *ptr)
{
    t_block block = GET_BLOCK(ptr);

    ASSERT(!block->free);
    block->free = 1;
    if (block->prev && block->prev->free)
        block = fusion(block->prev);
    fusion(block);
}

void free(void *ptr)
{
    ASSERT(ptr);
    pthread_mutex_lock(my_mutex());
    my_free(ptr);
    pthread_mutex_unlock(my_mutex());
}
