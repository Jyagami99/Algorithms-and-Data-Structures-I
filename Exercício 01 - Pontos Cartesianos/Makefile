MAIN=./main.c
BINARY=main

all:
	gcc -Wall -Werror -g $(MAIN) -o $(BINARY) -lm

run:
	./$(BINARY)

valgrind:
	valgrind --tool=memcheck --leak-check=full  --track-origins=yes --show-leak-kinds=all --show-reachable=yes ./$(BINARY)