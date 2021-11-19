all: main.o
	gcc -o bababooey main.o

main.o: main.c
	gcc -c main.c

run:
	./bababooey