#ifndef _SSH_DII_H_
#define _SSH_DII_H_

#include<stdint.h>

#include"access_types.h"

#define SSH_TARGET_HOST_ENV "SSH_DII_TARGET_HOST"

#define SSH_TARGET_USER_ENV "SSH_DII_TARGET_USER"

#define SSH_TARGET_PASSWORD_ENV "SSH_DII_TARGET_PASSWORD"

#define SSH_DII_SUCCESS 0

#define SSH_DII_FAILURE 1

#define SSH_DII_NULL_PARAMS 2

#define SSH_DII_BAD_ARGS 4

typedef uint32_t ssh_dii_status_t;

typedef struct ssh_dii_connection ssh_dii_connection_t;

ssh_dii_connection_t *init_ssh_dii();

ssh_dii_status_t ssh_dii_exec_command(const ssh_dii_connection_t *ssh, const char* cmd, uint32_t* result);

ssh_dii_status_t ssh_create_volume(const ssh_dii_connection_t* ssh, volume_t* vol);

ssh_dii_status_t ssh_export_volume(const ssh_dii_connection_t *ssh, volume_t* vol, hypervisor_t *hypervisor);

ssh_dii_status_t close_ssh_dii(ssh_dii_connection_t *ssh);

#endif
