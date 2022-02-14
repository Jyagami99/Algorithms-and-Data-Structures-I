ITEM = Item/Item.c
MAIN = main.c
UTIL = Util/Util.c
LISTA = Lista/Lista.c
BINARY = main
NAME = Ex5

all:
	gcc -Wall -g $(LISTA) $(ITEM) $(UTIL) $(MAIN) -o $(BINARY)

run:
	./$(BINARY)

valgrind:
	valgrind --tool=memcheck --leak-check=full  --track-origins=yes --show-leak-kinds=all --show-reachable=yes ./$(BINARY)

zip:
	@zip -r $(NAME).zip *

clean:
	@rm *.o