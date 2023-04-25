GUI_LIBRARIES = glfw3 glew
GUI_FLAGS := $(shell for flag in `pkg-config --libs $(GUI_LIBRARIES)`;\
	do echo $$flag; done)
FLAGS = -g -O2
CC = gcc

.PHONY: gui clean

gui: build/ bin/ build/config.o build/list.o build/helper.o bin/gui.out clean

bin/gui.out:
	$(CC) -o bin/gui.out $(GUI_FLAGS) build/gui.o build/config.o build/list.o build/helper.o

clean:
	rm -rf build/*

build/gui.o:
	$(CC) -o build/gui.o -c src/gui.c

build/config.o:
	$(CC) -o build/config.o -c src/config.c

build/:
	if test ! -d build; then mkdir build; fi

bin/:
	if test ! -d bin; then mkdir bin; fi

build/list.o:
	$(CC) -o build/list.o -c src/list.c

build/helper.o:
	$(CC) -o build/helper.o -c src/helper.c
