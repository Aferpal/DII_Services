CC=gcc

CFLAGS=-Wall

CINCLUDE=-I./inc $(shell pkg-config --cflags libssh)

COPTIONS=-O2 $(CINCLUDE)

SRC_DIR=./src

BUILD_DIR=../../build

OBJ_DIR=$(BUILD_DIR)/obj/ssh

LIB_DIR=$(BUILD_DIR)/lib

TARGET=libsshdii.a

OBJ_LIST=$(OBJ_DIR)/ssh_service.o

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(COPTIONS) -c $< -o $@

build: $(OBJ_LIST)
	mkdir -p $(LIB_DIR)
	ar rcs $(LIB_DIR)/$(TARGET) $^

clean:
	rm -f $(LIB_DIR)/$(TARGET)
	rm -rf $(OBJ_DIR)

.PHONY: build clean
