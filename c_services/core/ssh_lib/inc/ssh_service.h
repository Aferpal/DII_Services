#ifndef _SSH_SERVICE_H_
#define _SSH_SERVICE_H_

#include"ssh_types.h"

ssh_connection_t *ssh_dii_connection_new();

ssh_status_t ssh_dii_create_connection(ssh_connection_t* conn, 
                               const char *host, 
			       const char *user, 
			       const char *password);

ssh_status_t ssh_dii_exec(const ssh_connection_t* conn,
                      const char* cmd,
		      ssh_result_t* result);

ssh_status_t ssh_dii_disconnect(ssh_connection_t* conn);

#endif
