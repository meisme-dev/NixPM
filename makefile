CFLAGS = -Wall -Wextra -Werror -std=c99 -pedantic -g
CC = cc
ALL: config.c cmd.c configure

configure:
	mkdir -p bin

cmd.c:
	$(CC) src/cmd.c $(CFLAGS) -o bin/cmd

config.c:
	$(CC) src/config.c $(CFLAGS) -o bin/config