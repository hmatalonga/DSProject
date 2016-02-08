OBJS=src/main.c src/dataobj.c src/file.c src/utils.c
CC=gcc
COMPILER_FLAGS=-Wall -Werror
LINKER_FLAGS=-lm
DEPS=src/projed.h
OBJ_NAME=projed

all: projed

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(COMPILER_FLAGS)
projed: $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
clean:
	rm $(OBJ_NAME)