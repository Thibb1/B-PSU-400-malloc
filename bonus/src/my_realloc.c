/*
** EPITECH PROJECT, 2022
** malloc
** File description:
** my_realloc
*/

#include "my_memory.h"

static void *grow_block(t_block block, size_t size)
{
    size_t heap_size = GET_PAGE_SIZE(size);

    ASSERT_RET(sbrk(heap_size) != (void *) -1);
    block->size = heap_size - BLOCK_SIZE;
    split_block(block, size);
    return GET_DATA(block);
}

void *my_realloc(void *ptr, size_t size)
{
    t_block block = GET_BLOCK(ptr);
    void *new_ptr = NULL;

    ASSERT_RET_VAL(block->size <= size, ptr);
    ASSERT_RET_VAL(block->next, grow_block(block, size));
    if (block->next->free &&
        (block->size + BLOCK_SIZE + block->next->size) >= size) {
        fusion(block);
        split_block(block, size);
    } else {
        new_ptr = my_malloc(size);
        ASSERT_RET(new_ptr);
        memcpy(new_ptr, ptr, size);
        my_free(ptr);
        return new_ptr;
    }
    return GET_DATA(block);
}

void *realloc(void *ptr, size_t size)
{
    ASSERT_RET_VAL(ptr, malloc(size));
    if (size == 0) {
        free(ptr);
        return malloc(size);
    }
    pthread_mutex_lock(my_mutex());
    ptr = my_realloc(ptr, ALIGN_SIZE(size));
    pthread_mutex_unlock(my_mutex());
    return ptr;
}

void *reallocarray(void *ptr, size_t nmemb, size_t size)
{
    return realloc(ptr, nmemb * size);
}

void *calloc(size_t nmemb, size_t size)
{
    void *ptr = NULL;

    ASSERT_RET_VAL(nmemb != 0 && size != 0, NULL);
    ptr = malloc(nmemb * size);
    ASSERT_RET(ptr);
    memset(ptr, 0, nmemb * size);
    return ptr;
}
