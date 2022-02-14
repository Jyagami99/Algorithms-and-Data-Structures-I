ITEM = Item/Item.c
MAIN = main.c
UTIL = Util/Util.c
ARVORE = Arvore/Arvore.c
BINARY = main

all:
	gcc -Wall -g $(ARVORE) $(ITEM) $(UTIL) $(MAIN) -o $(BINARY)

run:
	./$(BINARY)

valgrind:
		valgrind --tool=memcheck --leak-check=full  --track-origins=yes --show-leak-kinds=all --show-reachable=yes ./$(BINARY)
