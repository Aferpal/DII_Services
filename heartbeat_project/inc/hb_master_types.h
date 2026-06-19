#ifndef _HB_MASTER_TYPES_H_
#define _HB_MASTER_TYPES_H_

#include<pthread.h>

#include"hb_types.h"

#define MASTER_PORT_ENV "HB_MASTER_PORT"

#define CLUSTER_MAX_NODES 8

typedef struct hypervisor_status hypervisor_status_t;

typedef struct hypervisor_status_list hypervisor_status_list_t;

typedef enum HYPERVISOR_STATUS_ENUM hypervisor_status_e;

enum HYPERVISOR_STATUS_ENUM { ON, OFF };

struct hypervisor_status {
	hypervisor_t id;
	int64_t last_timestamp;
	hypervisor_status_e status;
};


struct hypervisor_status_list {
	hypervisor_status_t data[CLUSTER_MAX_NODES];
	uint32_t size;
	pthread_mutex_t lock;
}

#endif
