# Created by Oscar Avellan

## CC  = Compiler.
## CFLAGS = Compiler flags.
CC	= gcc
CFLAGS =	-Wall -Wextra


## OBJ = Object files.
## SRC = Source files.
## EXE = Executable name.

SRC =		lz78.c treeops.c
OBJ =		lz78.o treeops.o
EXE = 	lz78

## Top level target is executable.
$(EXE):	$(OBJ)
		$(CC) $(CFLAGS) -o $(EXE) $(OBJ)


## Clean: Remove object files and core dump files.
clean:
		/bin/rm $(OBJ)

## Clobber: Performs Clean and removes executable file.

clobber: clean
		/bin/rm $(EXE)

## Dependencies

lz78.o:		treeops.h
treeops.o:	treeops.h
