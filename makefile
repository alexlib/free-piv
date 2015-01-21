# Compiler
CC = g++

# General C flags
CFLAGS_GEN = -ansi -Wall -pedantic

# Link OpenCV
CFLAGS_CV = `pkg-config opencv --cflags --libs`

# Link part of CUDA
CFLAGS_CUDA = -L/usr/local/cuda/lib -lcufft 

# Name of main program
PROGRAM = main

# Extension of main program.
EXT = cpp

all:
	$(CC) $(CFLAGS_GEN) $(CFLAGS_CV) $(CFLAGS_CUDA) -o $(PROGRAM) $(PROGRAM).$(EXT)
	
run:
	@make clean
	@make all
	./$(PROGRAM) image.jpg
	
clean:
	rm -f $(PROGRAM)