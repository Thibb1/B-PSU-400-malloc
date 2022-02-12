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
SOURCE_TEST = 	tests/tests_my_memory.c
OBJS = $(SOURCE:.c=.o)
OBJS_TEST = $(SOURCE_TEST:.c=.o)
NAME = libmy_malloc.so
CC = gcc
CFLAGS = -W -Wall -Wshadow -Wextra -I./includes/ -fPIC -lpthread
LDLIBS = -lcriterion -L. -l:$(NAME) -Wl,-rpath,./ -ldl
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
	find . -type f \( -name '*.gc*' -o -name '*.report' \) -delete

fclean: clean
	$(RM) -rf $(NAME) unit_tests unit_tests.info
	$(RM) -rf unit_tests_report

re: fclean all

debug: CFLAGS += -g
debug: re

test: CFLAGS += -g -D DEBUG
test: re
	$(CC) $(CFLAGS) test.c -o test.out -L./ -l:$(NAME) -Wl,-rpath,./ -ldl -fPIC -ggdb

.PHONY: all clean fclean re debug

#####################################################
#
# 					UNIT TEST RULES
#
#####################################################
unit_tests: CFLAGS += -fprofile-arcs -ftest-coverage --coverage -ggdb -D DEBUG
unit_tests: re $(OBJS_TEST)
	$(CC) $(CFLAGS) -o unit_tests $(OBJS_TEST) $(LDLIBS) -ggdb

unit_tests_page: unit_tests
	./unit_tests --always-succeed --verbose
	gcov *.gcda src/*.gcda
	lcov -c --directory . --output-file unit_tests.info
	genhtml unit_tests.info --output-directory unit_tests_report


.PHONY: unit_tests unit_tests_page
