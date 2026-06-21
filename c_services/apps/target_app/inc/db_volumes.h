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

#endif
