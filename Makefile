LIBRARIES = glfw3 glew
FLAGS := $(shell for flag in `pkg-config --libs $(LIBRARIES)`;do echo $$flag; done)

.PHONY: all build_folder build run gui

all: build_folder build run

build: src/main.c
	$(CC) -o build/main $(FLAGS) src/main.c

gui:
	$(CC) -o build/gui $(FLAGS) src/gui.c

run:
	@clear
	@build/main

build_folder:
	if test ! -d build; then mkdir build; fi
