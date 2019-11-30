
CC=gcc
CFLAGS=-W -Wall -pedantic
LDFLAGS=-lSDL2 -lSDL2_image
EXEC=mario
SRC= $(wildcard *.c)
OBJ= $(SRC:.c=.o)

all: $(EXEC)

mario: $(OBJ)
	@$(CC) -o $@ $^ $(LDFLAGS)

jeu.o: jeu.h declaration.h

%.o: %.c
	@$(CC) -o $@ -c $< $(CFLAGS)

.PHONY: clean mrproper

clean:
	@rm -rf *.o

mrproper: clean
	@rm -rf $(EXEC)

			
