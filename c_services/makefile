.PHONY: all ssh_lib db_lib target_app clean docker

LIBS_DIR=./core

APPS_DIR=./apps

all: target_app

ssh_lib:
	$(MAKE) -C $(LIBS_DIR)/ssh_lib build

db_lib:
	$(MAKE) -C $(LIBS_DIR)/db_conn_lib build

target_app: ssh_lib db_lib
	$(MAKE) -C $(APPS_DIR)/target_app build

docker_target: target_app 
	rm -rf build/docker_fs
	mkdir -p build/docker_fs
	mkdir -p build/docker_fs/app
	mkdir -p build/docker_fs/usr/lib
	mkdir -p build/docker_fs/lib
	cp build/bin/target_service build/docker_fs/app/
	ldd build/bin/target_service | awk '{print $$3}' | grep '^/' | xargs -I{} cp -v {} build/docker_fs/usr/lib/
	cp /lib/ld-musl-x86_64.so.1 build/docker_fs/lib/
	docker build -f docker/Dockerfile_target -t target_service:min .
	rm -f build/docker_images/*
	mkdir -p build/docker_images
	docker save -o build/docker_images/target_service.tar target_service:min
	gzip build/docker_images/target_service.tar
clean:
	$(MAKE) -C $(LIBS_DIR)/ssh_lib clean
	$(MAKE) -C $(LIBS_DIR)/db_conn_lib clean
	$(MAKE) -C $(APPS_DIR)/target_app clean
	rm -rf build/docker_fs
	rm -rf build/docker_images
