CC=gcc

CFLAGS=-Wall

CINCLUDE=-I./inc

CLINK=

COPTIONS=-static -O2 $(CINCLUDE)

SRC_DIR=./src

OUT_DIR=./out

OBJ_DIR=./obj

TARGET_MASTER=master

TARGET_NODE=node

OBJ_LIST_NODE=$(OBJ_DIR)/hb_net.o $(OBJ_DIR)/net_utils.o $(OBJ_DIR)/heartbeat_node.o

OBJ_LIST_MASTER=$(OBJ_DIR)/hb_net.o $(OBJ_DIR)/net_utils.o $(OBJ_DIR)/heartbeat_master.o $(OBJ_DIR)/hb_master_types.o

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(COPTIONS) -c $< -o $@ $(CLINK)

build_node: $(OBJ_LIST_NODE)
	mkdir -p $(OUT_DIR)
	$(CC) $(CFLAGS) $(COPTIONS) $(OBJ_LIST_NODE) node_main.c -o $(OUT_DIR)/$(TARGET_NODE) $(CLINK)

build_master: $(OBJ_LIST_MASTER)
	mkdir -p $(OUT_DIR)
	$(CC) $(CFLAGS) $(COPTIONS) $(OBJ_LIST_MASTER) master_main.c -o $(OUT_DIR)/$(TARGET_MASTER) $(CLINK)

clean:
	rm -f $(OUT_DIR)/*
	rm -f $(OBJ_DIR)/*
run_node:
	$(OUT_DIR)/$(TARGET_NODE)

run_master:
	$(OUT_DIR)/$(TARGET_MASTER)
