#ifndef _DB_VM_H_
#define _DB_VM_H_

#include<stdint.h>

typedef struct vm vm_t;


struct vm {
	uint32_t id;
	uint32_t cpu;
	uint32_t memory;
	uint32_t hyperv;
	char status;
};

#endif
