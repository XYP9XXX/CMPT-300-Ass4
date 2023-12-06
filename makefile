## Makefile for DSSimul.c
#
## Compiler to use
#CC = gcc
#
## Compiler flags
## -g    : adds debugging information to the executable file
## -Wall : turns on most compiler warnings
#CFLAGS = -g -Wall
#
## The name of your output file
#TARGET = DSSimul
#
#all: $(TARGET)
#
#$(TARGET): DSSimul.c
#	$(CC) $(CFLAGS) -o $(TARGET) DSSimul.c
#
#clean:
#	rm $(TARGET)
CC = gcc
CFLAGS = -I.

# Name of the executable
EXECUTABLE = DSSimul

# Object files
OBJ = DSSimul.o sstf.o scan.o utils.o

# Default target
all: $(EXECUTABLE)

# Linking the executable from object files
$(EXECUTABLE): $(OBJ)
	$(CC) -o $@ $^

# Compiling source files to object files
DSSimul.o: DSSimul.c list.h sstf.h scan.h utils.h globalConfig.h
	$(CC) -c $(CFLAGS) DSSimul.c

sstf.o: sstf.c sstf.h list.h globalConfig.h
	$(CC) -c $(CFLAGS) sstf.c

scan.o: scan.c scan.h list.h globalConfig.h
	$(CC) -c $(CFLAGS) scan.c

utils.o: utils.c utils.h list.h
	$(CC) -c $(CFLAGS) utils.c

# Clean target for removing compiled files
clean:
	rm -f $(EXECUTABLE) $(OBJ)
