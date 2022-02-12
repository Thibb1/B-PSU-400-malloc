/*
** EPITECH PROJECT, 2022
** malloc
** File description:
** my_metadata
*/

#include "my_memory.h"

pthread_mutex_t *my_mutex(void)
{
    static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

    return (&mutex);
}

t_block *my_base(void)
{
    static t_block base_block = NULL;

    return (&base_block);
}