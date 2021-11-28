all: main.o args.o cd.o
	gcc -o bababooey main.o args.o cd.o

main.o: main.c
	gcc -c main.c

args.o: args.c args.h
	gcc -c args.c

cd.o: cd.c cd.h
	gcc -c cd.c

run:
	./bababooey

clean:
	@rm *.o *.exe* *.gch || true