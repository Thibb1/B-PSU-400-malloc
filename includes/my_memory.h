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
#include <pthread.h>

    #ifdef DEBUG
        #define malloc __malloc__
        #define calloc __calloc__
        #define free __free__
        #define realloc __realloc__
        #define reallocarray __reallocarray__
    #endif
typedef struct s_block *t_block;

struct __attribute__((__packed__)) s_block {
    size_t size;
    t_block next;
    t_block prev;
    char free;
    void *ptr;
};


// macros for block alignment and block size
// https://stackoverflow.com/questions/13122846/align-macro-kernel
#define ALIGN4(x) (((x) + 3) & ~3)
#define BLOCK_SIZE (sizeof(struct s_block))

// Methods implemented
void *malloc(size_t size);
void free(void *ptr);
void *calloc(size_t nmemb, size_t size);
void *realloc(void *ptr, size_t size);
void *reallocarray(void *ptr, size_t nmemb, size_t size);

// base block
void **base(void);
void *get_ptr(void *ptr);

// page size util
size_t get_page_size(size_t size);

// block functions
t_block find_block(t_block *last, size_t size);
t_block extend_heap(t_block last, size_t size);
void split_block(t_block block, size_t size);
t_block fusion(t_block block);
t_block get_block(void *ptr);
void copy_block(t_block src, t_block dst);

#endif /* !MY_MEMORY_H_ */
