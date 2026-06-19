#ifndef _HB_NODE_TYPES_H_
#define _HB_NODE_TYPES_H_

#include"net_types.h"

typedef struct master_info master_info_t;

struct master_info {
	ip_t ip;
	port_t port;
};

#endif
