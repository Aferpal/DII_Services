#ifndef _SSH_TYPES_H_
#define _SSH_TYPES_H_

#include<stdint.h>

#define SSH_FAILURE 0

#define SSH_SUCCESS 1

#define SSH_NULL_PARAMS 2

typedef uint32_t ssh_status_t;

typedef struct ssh_result ssh_result_t;

typedef struct ssh_connection ssh_connection_t;

struct ssh_result {
	uint32_t status;
};

#endif
