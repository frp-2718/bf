# Adapt this makefile to fit your needs

CC = gcc
CFLAGS = -O2

EXEC = bf 
SOURCES = $(wildcard *.c)
OBJECTS = $(SOURCES:.c=.o)

$(EXEC): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXEC)

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJECTS)
	
mrproper: clean
	rm -f $(EXEC)

