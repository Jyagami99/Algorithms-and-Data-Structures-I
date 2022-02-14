MAIN = main.c
UTIL = Util/Util.c
MATRIZ = MatrizEsparsa/MatrizEsparsa.c
BINARY = main

all:
	gcc -Wall -g $(MATRIZ) $(UTIL) $(MAIN) -o $(BINARY)

run:
	./$(BINARY)

valgrind:
		valgrind --tool=memcheck --leak-check=full  --track-origins=yes --show-leak-kinds=all --show-reachable=yes ./$(BINARY)
