FLAGS = -g -c -Wall

all: main.c musica.c musica.h artista.c artista.h criterios.h criterios.c
	gcc $(FLAGS) main.c
	gcc $(FLAGS) musica.c 
	gcc $(FLAGS) artista.c 
	gcc $(FLAGS) spotfes.c
	gcc $(FLAGS) criterios.c
	gcc $(FLAGS) playlist.c
	gcc -o main main.o musica.o artista.o spotfes.o criterios.o playlist.o

clean:
	rm -f main main.o musica.o spotfes.o artista.o playlist.o criterios.o
	rm relatorio_mus.txt
	clear

run:
	make
	./main artists_full.csv tracks_full.csv

valgrind:
	make
	valgrind ./main artists_full.csv tracks_full.csv

gdb:
	make
	gdb ./main