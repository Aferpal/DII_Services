#include <sys/types.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <string.h>
#include <microhttpd.h>
#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include"db_dii.h"
#include"ssh_dii.h"

#define PORT_ENV "TARGET_HTTP_PORT"

db_dii_connection_t* db;
ssh_dii_connection_t *target;

volatile int running = 1;

void stop(int sig) 
{
	running = 0;
}

int
create_volume(int id)
{
	/* Look in the database for the volume */
	volume_t volume;
	if (get_volume_by_id(db, id, &volume) != DB_DII_SUCCESS) {
		printf("[ TARGET_SERVICE ] Error finding volume %d in database\n", id);
		return -1;
	}

	/* Do the ssh to the machine with the info */
	if (ssh_create_volume(target, &volume) != SSH_DII_SUCCESS) {
		printf("[ TARGET_SERVICE ] Error creating volume %d through ssh\n", id);
		return -1;
	}

	return 0;
}

static enum MHD_Result
connection_handler (void *cls, struct MHD_Connection *connection,
	const char *url, const char *method,
	const char *version, const char *upload_data,
	size_t *upload_data_size, void **req_cls)
{

	if (*upload_data_size != 0) {
		    *upload_data_size = 0;
		        return MHD_YES;
	}
	
	if (strcmp(method, "POST") != 0) {
		return MHD_NO;
	}		
	
	const char *prefix = "/volume/";
	if (strncmp(url, prefix, strlen(prefix)) != 0) {
		printf("[ TARGER_SERVICE ] Bad route, only allowed is /volume/{id}: %s\n", url);
		return MHD_NO;
	}
	
	const char *id_str = url + strlen(prefix);
	int id = atoi(id_str);

	if (create_volume(id) != 0) {
		printf("[ TARGET_SERVICE ] Volume %d was in db but could not create on ssh target\n", id);
		return MHD_NO;
	}

	enum MHD_Result ret;
	const char *response_text = "OK\n";

	struct MHD_Response *response = MHD_create_response_from_buffer(strlen(response_text), (void*)response_text, MHD_RESPMEM_PERSISTENT);

	ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
	MHD_destroy_response (response);
	
	return ret;
}

int
main (void)
{

	setvbuf(stdout, NULL, _IONBF, 0);

	db = init_db_dii();

	if (db == NULL) {
		printf("[ TARGET_SERVICE ] Error trying to stablish connection with sql database. Check correctness of %s, %s, %s, %s or %s\n", DB_DII_HOSTNAME_ENV, DB_DII_USER_ENV, DB_DII_PASSWORD_ENV, DB_DII_PORT_ENV, DB_DII_DATABASE_ENV);
		return -1;
	}

	target = init_ssh_dii();

	if (target == NULL) {
		printf("[ TARGET_SERVICE ] Error trying to stablish connection via ssh with target, check correctness of %s, %s or %s\n", SSH_TARGET_HOST_ENV, SSH_TARGET_USER_ENV, SSH_TARGET_PASSWORD_ENV);
		return -1;
	}
	
	signal(SIGTERM, stop);
	signal(SIGINT, stop);

	const char* port = getenv(PORT_ENV);

	if (port == NULL) {
		close_db_dii(db);
		printf("[ TARGET_SERVICE ] Error: %s is not defined. Exiting...\n", PORT_ENV);
		return -1;
	}

	int p_n = atoi(port);

	struct MHD_Daemon *daemon;
	daemon = MHD_start_daemon (MHD_USE_INTERNAL_POLLING_THREAD,
	p_n, NULL, NULL,
	&connection_handler, NULL, MHD_OPTION_END);
	
	if (NULL == daemon) {
		return 1;
	}
	
	while(running)
	{

	}

	MHD_stop_daemon (daemon);
	close_db_dii(db);
	printf("[ TARGET_SERVICE ] Program ends\n");
	return 0;
}
