#ifndef _HB_MASTER_TYPES_H_
#define _HB_MASTER_TYPES_H_

#include<pthread.h>

#include"hb_types.h"

#define MASTER_PORT_ENV "HB_MASTER_PORT"

#define CLUSTER_MAX_NODES 8

#define CHECK_TIMEOUT 5

#define HYPERV_LIST_FAILURE 0

#define HYPERV_LIST_SUCCESS 1

#define HYPERV_LIST_NULL_PARAMS 2

typedef uint32_t hyperv_list_status_t;

typedef struct hypervisor_status hypervisor_status_t;

typedef struct hypervisor_status_list hypervisor_status_list_t;

typedef enum HYPERVISOR_STATUS_ENUM hypervisor_status_e;

enum HYPERVISOR_STATUS_ENUM { ON, OFF };

struct hypervisor_status {
	hypervisor_id_t id;
	int64_t last_timestamp;
	hypervisor_status_e status;
};


struct hypervisor_status_list {
	hypervisor_status_t data[CLUSTER_MAX_NODES];
	uint32_t size;
	pthread_mutex_t lock;
};

hyperv_list_status_t hyperv_list_init(hypervisor_status_list_t* list);

hyperv_list_status_t hyperv_list_lock(hypervisor_status_list_t *list);

hyperv_list_status_t hyperv_list_unlock(hypervisor_status_list_t *list);

hyperv_list_status_t hyperv_list_append(hypervisor_status_list_t *list, hypervisor_id_t id);

hyperv_list_status_t hyperv_list_update_timestamp(hypervisor_status_list_t *list, hypervisor_id_t id, int64_t timestamp);


#endif
