CC=gcc
FLAGS=-c -Wall
LIBS=-lm
OBS=main.o file.o dataobj.o utils.o

all : projed
 
main.o : projed.h main.c
	$(CC) $(FLAGS) main.c
file.o : projed.h file.c
	$(CC) $(FLAGS) file.c
dataobj.o : projed.h dataobj.c
	$(CC) $(FLAGS) dataobj.c	
utils.o : projed.h utils.c
	$(CC) $(FLAGS) utils.c		
projed : $(OBS)
	$(CC) -o projed $(OBS) $(LIBS)
clean:
	rm -f projed *.o