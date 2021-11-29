all: main.o args.o cd.o redirection.o
	gcc -o bababooey main.o args.o cd.o redirection.o

main.o: main.c
	gcc -c main.c

args.o: args.c args.h
	gcc -c args.c

cd.o: cd.c cd.h
	gcc -c cd.c

redirection.o: redirection.c redirection.h
	gcc -c redirection.c

run:
	./bababooey

clean:
	@rm *.o *.exe* *.gch || true
