CC = gcc
CFLAGS = -Iinclude -Wall
LDFLAGS =

SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)

TARGET = traffic_simulator

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

run: $(TARGET)
	./$(TARGET)
