#ifndef _DB_HYPERVISOR_H_
#define _DB_HYPERVISOR_H_

#include<stdint.h>

#define STR_IQN_LEN 64

#define STR_HOST_LEN 16

typedef struct hypervisor hypervisor_t;

struct hypervisor {
	uint32_t id;
	char hostname[STR_HOST_LEN];
	char iqn[STR_IQN_LEN];
};

typedef struct hypervisor_list hypervisor_list_t;

struct hypervisor_list {
	hypervisor_t data[8];
	uint32_t size;
};

#endif
