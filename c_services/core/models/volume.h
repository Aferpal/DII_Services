#ifndef _DB_VOLUMES_H_
#define _DB_VOLUMES_H_

#include<stdint.h>

#define STR_PARAM_LEN 32

typedef struct volume volume_t;

struct volume {
	uint32_t id;
	uint32_t size_kb;
	char name[STR_PARAM_LEN];
};

typedef struct volume_list volume_list_t;

struct volume_list {
	volume_t data[8];
	uint32_t size;
};

#endif
