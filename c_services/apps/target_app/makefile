CC=gcc

CFLAGS=-Wall

CINCLUDE=-I./inc $(shell pkg-config --cflags libmicrohttpd)

CLINK=$(shell pkg-config --libs libmicrohttpd)

COPTIONS=-O2 $(CINCLUDE)

SRC_DIR=./src

OUT_DIR=./out

OBJ_DIR=./obj

TARGET=app

OBJ_LIST=

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
