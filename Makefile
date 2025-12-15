all:
	gcc -Wall -Wextra -Werror -std=c99 fractal-renderer.c -o fractal-renderer -lraylib -lm

