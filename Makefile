FLAGS=-Wall -Wextra -Werror
BUILD_DIR=build/
INCLUDE_DIR=include/
SOURCE_DIR=src/

all: install

build:
	mkdir -p $(BUILD_DIR)
	sudo mkdir -p /usr/local/include/gnl
	sudo cp include/get_next_line.h /usr/local/include/gnl
	gcc $(FLAGS) -c -g -o $(BUILD_DIR)gnl.o $(SOURCE_DIR)get_next_line.c 
	ar rcs $(BUILD_DIR)libgnl.a $(BUILD_DIR)gnl.o

install: build 
	sudo cp build/libgnl.a /usr/local/lib
