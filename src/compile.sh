#!/bin/bash

gcc -Wall -Werror -Wextra -D BUFFER_SIZE=2 get_next_line.c get_next_line_utils.c get_next_line.h main.c

./a.out
