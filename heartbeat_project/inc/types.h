#ifndef _HB_TYPES_H_
#define _HB_TYPES_H_

#include<stdint.h>

typedef struct heartbeat_info heartbeat_info_t;

typedef uint32_t hypervisor_id_t;

struct heartbeat_info {
	hypervisor_id_t hypervisor_id;
	uint64_t total_memory;
	uint64_t free_memory;
	uint64_t timestamp;
	uint32_t seq_number;
};


#endif



