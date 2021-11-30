all: main.o args.o cd.o redirection.o err.o
	gcc -o bababooey main.o args.o cd.o redirection.o err.o

main.o: main.c
	gcc -c main.c

args.o: args.c args.h
	gcc -c args.c

cd.o: cd.c cd.h
	gcc -c cd.c

redirection.o: redirection.c redirection.h
	gcc -c redirection.c

err.o: err.c err.h
	gcc -c err.c

run:
	./bababooey

clean:
	@rm *.o *.exe* *.gch || true
