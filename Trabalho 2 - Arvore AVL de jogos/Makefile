INPUT = main.c arvore.c jogo.c 
OUTPUT = out
NAME = trab2

all:
		gcc -Wall -Werror -g $(INPUT) -o $(OUTPUT) 

run:
		./$(OUTPUT)

zip:
		@zip -r $(NAME).zip *

debug:
		gcc -DDEBUG -Wall $(INPUT) -o $(OUTPUT)

valgrind:
		valgrind --tool=memcheck --leak-check=full  --track-origins=yes --show-leak-kinds=all --show-reachable=yes ./$(OUTPUT)
