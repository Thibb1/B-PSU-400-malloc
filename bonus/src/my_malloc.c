/*
** EPITECH PROJECT, 2022
** malloc
** File description:
** my_malloc
*/

#include "my_memory.h"

static t_block get_new_heap(t_block last, size_t size, char is_free)
{
    size_t heap_size = GET_PAGE_SIZE(size);
    t_block new_heap = sbrk(heap_size);

    ASSERT_RET(new_heap != (void *) - 1);
    new_heap->size = heap_size - BLOCK_SIZE;
    new_heap->next = NULL;
    new_heap->prev = last;
    new_heap->free = is_free;
    return new_heap;
}

static t_block get_new_block(size_t size)
{
    t_block last = NULL;
    t_block current = *my_base();
    t_block smallest = NULL;

    while (current) {
        if (current->free && current->size >= size
            && (!smallest || current->size < smallest->size))
            smallest = current;
        last = current;
        current = current->next;
    }
    ASSERT_RET_VAL(smallest, get_new_heap(last, size, 0));
    return smallest;
}

void *my_malloc(size_t size)
{
    t_block new_block = NULL;

    if (!*my_base())
        *my_base() = get_new_heap(NULL, size, 1);
    ASSERT_RET(*my_base());
    new_block = get_new_block(size);
    ASSERT_RET(new_block);
    new_block->free = 0;
    split_block(new_block, size);
    return GET_DATA(new_block);
}

void *malloc(size_t size)
{
    void *ptr = NULL;

    ASSERT_RET(size != 0);
    pthread_mutex_lock(my_mutex());
    ptr = my_malloc(ALIGN_SIZE(size));
    pthread_mutex_unlock(my_mutex());
    return ptr;
}
