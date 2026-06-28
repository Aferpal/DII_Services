CC=gcc

CFLAGS=-Wall -Wextra -O2 -ffunction-sections -fdata-sections -flto

LDFLAGS=-Wl,--gc-sections -flto

CINCLUDE=-I./inc -I../../core/access_lib/inc -I../../core/models $(shell pkg-config --cflags libmicrohttpd)

CLINK=-L../../build/lib -laccessdii -ldbconndii -lsshdii -lmicrohttpd -lssh -lmariadb

COPTIONS=$(CINCLUDE)

SRC_DIR=./src

BUILD_DIR=../../build

OUT_DIR=$(BUILD_DIR)/bin

OBJ_DIR=$(BUILD_DIR)/obj/hyperv

DOCK_TEMP_DIR=$(BUILD_DIR)/docker_fs/hyperv

DOCK_IMG_DIR=$(BUILD_DIR)/docker_images

TARGET=hyperv_service

OBJ_LIST=$(OBJ_DIR)/hyperv_connections.o

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(COPTIONS) -c $< -o $@

build: $(OBJ_LIST)
	mkdir -p $(OUT_DIR)
	$(CC) $(CFLAGS) $(COPTIONS) $(OBJ_LIST) main.c -o $(OUT_DIR)/$(TARGET) $(CLINK) $(LDFLAGS)

docker: clean build
	mkdir -p $(DOCK_TEMP_DIR)
	mkdir -p $(DOCK_TEMP_DIR)/app
	mkdir -p $(DOCK_TEMP_DIR)/usr/lib
	mkdir -p $(DOCK_TEMP_DIR)/lib
	cp $(OUT_DIR)/$(TARGET) $(DOCK_TEMP_DIR)/app/$(TARGET)
	ldd $(OUT_DIR)/$(TARGET) | awk '{print $$3}' | grep '^/' |\
		xargs -I{} cp -v {} $(DOCK_TEMP_DIR)/usr/lib/
	cp /lib/ld-musl-x86_64.so.1 $(DOCK_TEMP_DIR)/lib/
	docker build -f Dockerfile_hyperv -t hyperv_service:min $(DOCK_TEMP_DIR)
	mkdir -p $(DOCK_IMG_DIR)
	docker save -o $(DOCK_IMG_DIR)/$(TARGET).tar hyperv_service:min
	gzip $(DOCK_IMG_DIR)/$(TARGET).tar
	rm -rf $(DOCK_TEMP_DIR)

clean:
	rm -f $(OUT_DIR)/*
	rm -f $(OBJ_DIR)/*
	rm -rf $(DOCK_IMG_DIR)
run:
	$(OUT_DIR)/$(TARGET)
