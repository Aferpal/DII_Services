.PHONY: all ssh_lib db_lib target_app clean

LIBS_DIR=./core

APPS_DIR=./apps

all: target_app

ssh_lib:
	$(MAKE) -C $(LIBS_DIR)/ssh_lib build

db_lib:
	$(MAKE) -C $(LIBS_DIR)/db_conn_lib build

target_app:
	$(MAKE) -C $(APPS_DIR)/target_app build

clean:
	$(MAKE) -C $(LIBS_DIR)/ssh_lib clean
	$(MAKE) -C $(LIBS_DIR)/db_conn_lib clean
	$(MAKE) -C $(APPS_DIR)/target_app clean
