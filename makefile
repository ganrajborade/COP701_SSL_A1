# Makefile for Project

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra

# Targets and dependencies
all: output

output: main.o functions.o bison.tab.o lex.yy.o
	@$(CC) $(CFLAGS) -o output main.o functions.o bison.tab.o lex.yy.o 2>/dev/null

main.o: main.c
	@$(CC) $(CFLAGS) -c main.c 2>/dev/null

functions.o: functions.c
	@$(CC) $(CFLAGS) -c functions.c 2>/dev/null

bison.tab.o: bison.tab.c
	@$(CC) $(CFLAGS) -c bison.tab.c 2>/dev/null

bison.tab.c: bison.y
	@bison -dt bison.y 2>/dev/null

lex.yy.o: lex.yy.c
	@$(CC) $(CFLAGS) -c lex.yy.c 2>/dev/null

lex.yy.c: lexer.l
	@flex lexer.l 2>/dev/null

clean:
	@rm -f *.o bison.tab.* lex.yy.c output

.PHONY: clean
