#ifndef _HYPERV_CONNECTIONS_H_
#define _HYPERV_CONNECTIONS_H_

#include"db_dii.h"
#include"ssh_dii.h"

#define MAX_CONNECTIONS 8


#define SSH_HYPERV_USER_ENV "SSH_HYPERV_USER"

#define SSH_HYPERV_PASSWORD_ENV "SSH_HYPERV_PASSWORD_ENV"

typedef struct hyperv_connections hyperv_connections_t;

struct hyperv_connections {
	ssh_dii_connection_t* connections[MAX_CONNECTIONS];
	uint32_t size;
}

void init_hyperv_connections_on_db_data(const db_dii_connection_t *db, hyperv_connections_t *conns);

void clean_connections(const hyperv_connections_t *conns);

#endif
