CC=gcc

CFLAGS=-Wall

CINCLUDE=-I./inc -I../../core/db_conn_lib/inc $(shell pkg-config --cflags libmicrohttpd)

CLINK=-L../../build/lib -ldbconndii $(shell pkg-config --libs libmicrohttpd) $(shell pkg-config --libs libmariadb) 

COPTIONS=-O2 $(CINCLUDE)

SRC_DIR=./src

BUILD_DIR=../../build

OUT_DIR=$(BUILD_DIR)/bin

OBJ_DIR=$(BUILD_DIR)/obj/target

TARGET=target_service

OBJ_LIST=$(OBJ_DIR)/db_dii.o

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(COPTIONS) -c $< -o $@ $(CLINK)

build: $(OBJ_LIST)
	mkdir -p $(OUT_DIR)
	$(CC) $(CFLAGS) $(COPTIONS) $(OBJ_LIST) main.c -o $(OUT_DIR)/$(TARGET) $(CLINK)

clean:
	rm -f $(OUT_DIR)/*
	rm -f $(OBJ_DIR)/*
run:
	$(OUT_DIR)/$(TARGET)
