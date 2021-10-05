CC = cc
CFLAGS = -Wall -Wextra -Werror -std=c99 -pedantic
OBJFILES = src/config.o src/cmd.o
TARGET = bin/nixpm

ALL: configure $(TARGET)

configure:
	mkdir -p bin

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES)

clean:
	rm $(OBJFILES) $(TARGET)