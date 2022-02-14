ITEM = Item/Item.c
MAIN = main.c
UTIL = Util/Util.c
LISTA = Lista/ListaEncadeada.c
BINARY = main

all:
	gcc -Wall -g $(LISTA) $(UTIL) $(ITEM) $(MAIN) -o $(BINARY)

run:
	./$(BINARY)

valgrind:
		valgrind --tool=memcheck --leak-check=full  --track-origins=yes --show-leak-kinds=all --show-reachable=yes ./$(BINARY)
