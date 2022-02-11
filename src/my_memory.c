/*
** EPITECH PROJECT, 2022
** malloc
** File description:
** my_memory
*/

#include "my_memory.h"

t_block find_block(t_block *last, size_t size)
{
    t_block block = *base();
    t_block first_free = NULL;
    void **ptr = base();

    while (block && !(block->free && block->size >= size)) {
        first_free = (!first_free && block->free) ? block : first_free;
        *last = block;
        block = block->next;
    }
    *ptr = (*last)->free ? *last : *ptr;
    *ptr = first_free ? first_free : *ptr;
    return block;
}

t_block init_base(size_t size, pthread_mutex_t mutex)
{
    void **ptr = base();
    pthread_mutex_trylock(&mutex);
    if (*ptr)
        return *ptr;
    *ptr = extend_heap(NULL, size);
    return *ptr;
}

void *malloc(size_t size)
{
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    size_t sa = ALIGN4(size);
    t_block base_block = init_base(sa, mutex);
    t_block last = find_block(&base_block, sa);
    t_block block = last ? last : extend_heap(base_block, sa);

    if (size == 0) {
        pthread_mutex_unlock(&mutex);
        return NULL;
    }
    if ((block->size - sa) >= (BLOCK_SIZE + 4UL))
        split_block(block, sa);
    block->free = 0;
    pthread_mutex_unlock(&mutex);
    return block->ptr;
}

void free(void *ptr)
{
    t_block block = get_ptr(ptr);
    void **base_ptr = base();

    if (block) {
        block->free = 1;
        if (block->prev && block->prev->free)
            block = fusion(block->prev);
        if (block->next)
            fusion(block);
        if (*base_ptr < (void *)block)
            *base_ptr = block;
    }
}
