CC = gcc
CFLAGS = -Wall -O2

SRC = src/main.c src/clipboard.c src/hid.c
OBJ = $(SRC:.c=.o)

TARGET = CopyPasteBoard.exe

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) -lhid -lsetupapi

clean:
	rm -f $(OBJ) $(TARGET)
