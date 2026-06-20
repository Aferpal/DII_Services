#include<libssh/libssh.h>
#include<string.h>
#include<ssh_service.h>
#include<stdio.h>
#include<stdlib.h>
#define STR_PARAM_LEN 32

struct ssh_connection {
	char hostname[STR_PARAM_LEN];
	char user[STR_PARAM_LEN];
	ssh_session session;
};

ssh_connection_t *
ssh_dii_connection_new()
{
	return malloc(sizeof(struct ssh_connection));
}


ssh_status_t
ssh_dii_create_connection(ssh_connection_t* conn,
		  const char *host,
		  const char *user,
		  const char *password) 
{
	if (conn == NULL || host == NULL || user == NULL || password == NULL ) {
		return SSH_NULL_PARAMS;
	}

	if (strlen(host) >= STR_PARAM_LEN || strlen(user) >= STR_PARAM_LEN) {
		printf("Error en los nombres\n");
		return SSH_FAILURE;
	}

	memset(conn, 0, sizeof(*conn));

	strncpy(conn->hostname, host, STR_PARAM_LEN - 1);

	strncpy(conn->user, user, STR_PARAM_LEN - 1);

	conn->session = ssh_new();

	if (conn->session == NULL) {
		printf("no se puede crear sesion\n");
		return SSH_FAILURE;
	}

	ssh_options_set(conn->session, SSH_OPTIONS_HOST, conn->hostname);

	if (ssh_connect(conn->session) != SSH_OK) {
		printf("No se ha podido conectar\n");
		ssh_free(conn->session);
		conn->session = NULL;
		return SSH_FAILURE;
	}

	if (ssh_userauth_password(conn->session, conn->user, password) != SSH_AUTH_SUCCESS) {
		printf("No se ha podido autenticar\n");
		ssh_disconnect(conn->session);
		ssh_free(conn->session);
		conn->session = NULL;
		return SSH_FAILURE;
	}

	return SSH_SUCCESS;

}

ssh_status_t
ssh_dii_exec(const ssh_connection_t* conn,
         const char* cmd,
         ssh_result_t* result)
{
	if (conn == NULL || cmd == NULL) {
		return SSH_NULL_PARAMS;
	}

	ssh_channel ch = ssh_channel_new(conn->session);

	if (ch == NULL) {
		return SSH_FAILURE;
	}

	if (ssh_channel_open_session(ch) != SSH_OK) {
		ssh_channel_free(ch);
		return SSH_FAILURE;
	}

	if (ssh_channel_request_exec(ch, cmd) != SSH_OK) {
		ssh_channel_close(ch);
		ssh_channel_free(ch);
		return SSH_FAILURE;
	}

	if (result != NULL) {
		result->status = ssh_channel_get_exit_status(ch);
	}

	ssh_channel_send_eof(ch);

	ssh_channel_close(ch);

	ssh_channel_free(ch);

	return SSH_SUCCESS;
}

ssh_status_t
ssh_dii_disconnect(ssh_connection_t* conn)
{
	if (conn == NULL) {
		return SSH_NULL_PARAMS;
	}

	ssh_disconnect(conn->session);
	ssh_free(conn->session);
	conn->session = NULL;
	return SSH_SUCCESS;
}

