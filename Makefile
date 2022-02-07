##
## EPITECH PROJECT, 2022
## Documents
## File description:
## Makefile for a c++ project with all, clean, fclean, re, debug
##

SOURCE = 	my_memory.c	\
			my_block.c	\
			my_alloc.c
OBJS = $(SOURCE:.c=.o)
NAME = libmy_malloc.so
CC = gcc
CFLAGS = -Wall -Wextra -W -fPIC
LDFLAGS = -shared

all: $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LDFLAGS)

clean:
	rm -f $(OBJS) *.report

fclean: clean
	rm -f $(NAME)

re: fclean all

debug: CFLAGS += -g
debug: re

.PHONY: all clean fclean re debug
