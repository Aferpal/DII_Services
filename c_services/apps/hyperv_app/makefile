CC=gcc

CFLAGS=-Wall -Wextra -O2 -ffunction-sections -fdata-sections -flto

LDFLAGS=-Wl,--gc-sections -flto

CINCLUDE=-I./inc -I../../core/db_conn_lib/inc -I../../core/ssh_lib/inc $(shell pkg-config --cflags libmicrohttpd) $(shell pkg-config --cflags libssh)

CLINK=-L../../build/lib -ldbconndii -lsshdii -lmicrohttpd -lssh -lmariadb

COPTIONS=$(CINCLUDE)

SRC_DIR=./src

BUILD_DIR=../../build

OUT_DIR=$(BUILD_DIR)/bin

OBJ_DIR=$(BUILD_DIR)/obj/hyperv

TARGET=hyperv_service

OBJ_LIST=$(OBJ_DIR)/db_dii.o $(OBJ_DIR)/ssh_dii.o

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(COPTIONS) -c $< -o $@

build: $(OBJ_LIST)
	mkdir -p $(OUT_DIR)
	$(CC) $(CFLAGS) $(COPTIONS) $(OBJ_LIST) main.c -o $(OUT_DIR)/$(TARGET) $(CLINK) $(LDFLAGS)

clean:
	rm -f $(OUT_DIR)/*
	rm -f $(OBJ_DIR)/*
run:
	$(OUT_DIR)/$(TARGET)
