CC=gcc

CFLAGS=-Wall

CINCLUDE=-I./inc -I../ssh_lib/inc -I../db_conn_lib/inc -I../models

COPTIONS=-O2 $(CINCLUDE)

SRC_DIR=./src

BUILD_DIR=../../build

OBJ_DIR=$(BUILD_DIR)/obj/access

LIB_DIR=$(BUILD_DIR)/lib

TARGET=libaccessdii.a

OBJ_LIST=$(OBJ_DIR)/db_dii.o $(OBJ_DIR)/ssh_dii.o

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
