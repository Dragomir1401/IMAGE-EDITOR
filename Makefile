#Copyright Dragomir Andrei-Mihai
#compiler setup
CC=gcc
CFLAGS=-Wall -Wextra -std=c99 -g -lm

# define targets
TARGET=image_editor

build: $(TARGET)

image_editor: main.o load_commands.o free_command.o crop_image.o select_pixels.o save_command.o filters.o rotate.o
	$(CC) $(CFLAGS) $^ -o $@ -lm

%.o: %.c
	$(CC) $(CFLAGS) -c $^

pack:
	zip -FSr 312CA_DragomirAndrei_Tema2.zip README Makefile *.c *.h

clean:
	rm -f $(TARGETS)

.PHONY: pack clean
