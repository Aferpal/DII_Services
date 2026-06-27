#include "ssh_dii.h"
#include <ssh_service.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

struct ssh_dii_connection {
	ssh_connection_t *conn;
};

ssh_dii_connection_t *
init_ssh_dii()
{
	ssh_dii_connection_t* res = malloc(sizeof(struct ssh_dii_connection));

	if (res == NULL) {
		return NULL;
	}

	res->conn = ssh_dii_connection_new();

	if (res->conn == NULL) {
		free(res);
		return NULL;
	}

	const char* host = getenv(SSH_TARGET_HOST_ENV);
	const char* user = getenv(SSH_TARGET_USER_ENV);
	const char* password = getenv(SSH_TARGET_PASSWORD_ENV);

	if (host == NULL || user == NULL || password == NULL) {
		printf("No están definidas las variables de entorno\n");
		close_ssh_dii(res);
		return NULL;
	}

	if (ssh_dii_create_connection(res->conn,
                                      host,
				      user,
				      password) != SSH_SUCCESS) {
		printf("No se ha podido conectar, los env están mal definidos\n");
		close_ssh_dii(res);
		return NULL;
	}

	return res;
}

ssh_dii_status_t
ssh_dii_exec_command(const ssh_dii_connection_t *ssh, const char* cmd, uint32_t* result)
{
	if (ssh == NULL || cmd == NULL || result == NULL) {
		printf("Null params en dii exec command\n");
		return SSH_DII_NULL_PARAMS;
	}

	ssh_result_t res;
	if (ssh_dii_exec(ssh->conn, cmd, &res) != SSH_SUCCESS) {
		printf("Fallo al  hacer el ssh dii exec\n");
		return SSH_DII_FAILURE;
	}

	*result = res.status;

	return SSH_DII_SUCCESS;

}

ssh_dii_status_t
ssh_create_volume(const ssh_dii_connection_t* ssh, volume_t* vol)
{
	if (ssh == NULL || vol == NULL) {
		return SSH_DII_NULL_PARAMS;
	}

	char command[256] = {0};

	snprintf(command, 256, "/root/bin/create_volume %s %d %dK", vol->name, vol->id, vol->size_kb);
	uint32_t res;
	if (ssh_dii_exec_command(ssh, command, &res) != SSH_DII_SUCCESS) {
		printf("Error ejecutando el exec de create con %s %d %dK\n", vol->name, vol->id, vol->size_kb);
		return SSH_DII_FAILURE;
	}

	return res == 0 ? SSH_DII_SUCCESS : SSH_DII_FAILURE;
}



ssh_dii_status_t
close_ssh_dii(ssh_dii_connection_t *ssh)
{
	ssh_dii_disconnect(ssh->conn);
	free(ssh);
	return SSH_DII_SUCCESS;
}

