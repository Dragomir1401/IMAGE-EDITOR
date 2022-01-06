#Copyright Dragomir Andrei-Mihai
#compiler setup
CC=gcc
CFLAGS=-Wall -Wextra -lm -std=c99 -g

# define targets
TARGETS=photo_editor

build: $(TARGETS)

%.o: %.c
	$(CC) $(CFLAGS) -c $^

photo_editor: main.o load_commands.o free_command.o crop_image.o select_pixels.o save_command.o filters.o rotate.o
	$(CC) $(CFLAGS) main.o load_commands.o free_command.o crop_image.o select_pixels.o save_command.o filters.o rotate.o -o photo_editor

pack:
	zip -FSr 312CA_DragomirAndrei_Tema2.zip README Makefile *.c *.h

clean:
	rm -f $(TARGETS)

.PHONY: pack clean
