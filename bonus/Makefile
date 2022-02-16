##
## EPITECH PROJECT, 2022
## Documents
## File description:
## Makefile for a c++ project with all, clean, fclean, re, debug
##

#####################################################
#
# 					PARAMETERS
#
#####################################################

SOURCE = 	src/my_block.c		\
			src/my_free.c		\
			src/my_malloc.c		\
			src/my_metadata.c	\
			src/my_realloc.c
OBJS = $(SOURCE:.c=.o)
OBJS_TEST = $(SOURCE_TEST:.c=.o)
NAME = libmy_malloc.so
CC = gcc
CFLAGS = -W -Wall -Wshadow -Wextra -I./includes/ -fPIC
LDFLAGS = -shared

#####################################################
#
# 					RULES
#
#####################################################

all: $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LDFLAGS)

clean:
	$(RM) -f $(OBJS) $(OBJS_TEST)
	find . -type f -name '*.gc*' -delete

fclean: clean
	$(RM) -rf $(NAME)

re: fclean all

debug: CFLAGS += -g
debug: re

.PHONY: all clean fclean re debug
