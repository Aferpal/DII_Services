#ifndef _DB_NETWORK_H_
#define _DB_NETWORK_H_

#include<stdint.h>

typedef struct network network_t;

struct network {
	uint32_t id;
	char name[8];
};

#endif
