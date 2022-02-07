/*
** EPITECH PROJECT, 2022
** malloc
** File description:
** my_memory
*/

#ifndef MY_MEMORY_H_
#define MY_MEMORY_H_

// size_t and brk/sbrk imports
#include <unistd.h>
#include <stddef.h>

// macros for block alignment and block size
// https://stackoverflow.com/questions/13122846/align-macro-kernel
#define align4(x) (((x) + 3) & ~3)
#define BLOCK_SIZE 40UL

// block structure
typedef struct s_block *t_block;

struct s_block {
    size_t size;
    t_block next;
    t_block prev;
    int free;
    void *ptr;
    char data[1];
};

// Methods implemented
void *malloc(size_t size);
void free(void *ptr);
void *calloc(size_t nmemb, size_t size);
void *realloc(void *ptr, size_t size);
void *reallocarray(void *ptr, size_t nmemb, size_t size);

// block functions
t_block find_block(t_block *last, size_t size);
t_block extend_heap(t_block last, size_t size);
void split_block(t_block block, size_t size);
t_block fusion(t_block block);
t_block get_block(void *ptr);
void copy_block(t_block src, t_block dst);
int valid_addr(void *ptr);

#endif /* !MY_MEMORY_H_ */
