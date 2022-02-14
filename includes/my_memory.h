/*
** EPITECH PROJECT, 2022
** malloc
** File description:
** my_memory
*/

#ifndef MY_MEMORY_H_
#define MY_MEMORY_H_

#include <unistd.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>

typedef struct s_block *t_block;

struct s_block {
    size_t size;
    t_block next;
    t_block prev;
    char free;
};

#define ASSERT(assertion) \
if (!(assertion)) { \
    return; \
}

#define ASSERT_RET(assertion) \
if (!(assertion)) { \
    return NULL; \
}

#define ASSERT_RET_VAL(assertion, value) \
if (!(assertion)) { \
    return value; \
}

#define ALIGN_PADDING 8
#define ALIGN_SIZE_N(x, n) (((x) + (n - 1)) & ~(n - 1))
#define ALIGN_SIZE(x) ALIGN_SIZE_N((x), ALIGN_PADDING)

#define BLOCK_SIZE (sizeof(struct s_block))

#define NB_PAGES 2
#define PAGE_SIZE sysconf(_SC_PAGESIZE)
#define GET_PAGE_SIZE(size) ALIGN_SIZE_N((size) + BLOCK_SIZE, \
    PAGE_SIZE * NB_PAGES)

#define GET_BLOCK(block) ((t_block) ((char *) (block) - BLOCK_SIZE))
#define GET_DATA(block) ((void *) ((char *) (block) + BLOCK_SIZE))

void *malloc(size_t size);
void free(void *ptr);
void *calloc(size_t nmemb, size_t size);
void *realloc(void *ptr, size_t size);
void *reallocarray(void *ptr, size_t nmemb, size_t size);

void *my_malloc(size_t size);
void my_free(void *ptr);

void split_block(t_block block, size_t size);
t_block fusion(t_block block);
pthread_mutex_t *my_mutex(void);
t_block *my_base(void);

#endif
