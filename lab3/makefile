CC = gcc
CFLAGS = -Wall -g
LDFLAGS =
TARGET = myps
OBJECTS = main.o proc.o

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

main.o: main.c proc.h
	$(CC) $(CFLAGS) -c main.c

proc.o: proc.c proc.h
	$(CC) $(CFLAGS) -c proc.c

clean:
	rm -f $(OBJECTS) $(TARGET)

test: $(TARGET)
	./$(TARGET) -l
	./$(TARGET) -p 1



.PHONY: all clean test

# ./myps -l
# ./myps -p 284