# Makefile for DSSimul.c

# Compiler to use
CC = gcc

# Compiler flags
# -g    : adds debugging information to the executable file
# -Wall : turns on most compiler warnings
CFLAGS = -g -Wall

# The name of your output file
TARGET = DSSimul

all: $(TARGET)

$(TARGET): DSSimul.c
	$(CC) $(CFLAGS) -o $(TARGET) DSSimul.c

clean:
	rm $(TARGET)
