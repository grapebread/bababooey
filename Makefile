all: main.o args.o
	gcc -o bababooey main.o args.o

main.o: main.c
	gcc -c main.c

args.o: args.c
	gcc -c args.c

run:
	./bababooey