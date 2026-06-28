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
#include"hyperv_connections.h"

#define PORT_ENV "HYPERV_HTTP_PORT"

db_dii_connection_t* db;

hyperv_connections_t h_conns;

int last_h = 0;

volatile int running = 1;

void stop(int sig) 
{
	running = 0;
}

int
create_vm(int id)
{
	/* Look in the database for the vm */
	vm_t vm;
	if (get_vm_by_id(db, id, &vm) != DB_DII_SUCCESS) {
		printf("[ HYPERV_SERVICE ] Error finding vm %d in database\n", id);
		return -1;
	}

	volume_list_t vol_list;
	/* Get all volumes related to vm */
	if (get_all_volumes_from_vm_id(db, id, &vol_list) != SSH_DII_SUCCESS) {
		printf("[ HYPERV_SERVICE ] Error retrieving volumes for vm  %d\n", id);
		return -1;
	}


	/* logic to decide the next hypervisor */

	if (ssh_create_vm_with_volumes(h_conns.data[last_h], &vm, &vol_list) != SSH_DII_SUCCESS) {
	
		printf("[ HYPERV_SERVICE ] Errot trying to create vm %d in hypervisor %d\n", vm.id, list.data[0].id);

	} else {
		last_h++;
		last_h %= h_conns.size;
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
	
	const char *prefix = "/vm/";
	if (strncmp(url, prefix, strlen(prefix)) != 0) {
		printf("[ HYPERV_SERVICE ] Bad route, only allowed is /volume/{id}: %s\n", url);
		return MHD_NO;
	}
	
	const char *id_str = url + strlen(prefix);
	int id = atoi(id_str);

	if (create_volume(id) != 0) {
		printf("[ HYPERV_SERVICE ] Volume %d was in db but could not create on ssh target\n", id);
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
		printf("[ HYPERV_SERVICE ] Error trying to stablish connection with sql database. Check correctness of %s, %s, %s, %s or %s\n", DB_DII_HOSTNAME_ENV, DB_DII_USER_ENV, DB_DII_PASSWORD_ENV, DB_DII_PORT_ENV, DB_DII_DATABASE_ENV);
		return -1;
	}

	init_hyperv_connections_on_db_data(db, &h_conns);

	signal(SIGTERM, stop);
	signal(SIGINT, stop);

	const char* port = getenv(PORT_ENV);

	if (port == NULL) {
		close_db_dii(db);
		printf("[ HYPERV_SERVICE ] Error: %s is not defined. Exiting...\n", PORT_ENV);
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
	
	clean_connections(&h_conns);

	printf("[ HYPERV_SERVICE ] Program ends\n");
	return 0;
}
