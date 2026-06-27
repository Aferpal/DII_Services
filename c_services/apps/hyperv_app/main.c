#include <sys/types.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <string.h>
#include <microhttpd.h>
#include<stdio.h>
#include<stdlib.h>
#include<signal.h>

#define PORT_ENV "HYPERV_HTTP_PORT"

volatile int running = 1;

void stop(int sig) 
{
	running = 0;
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
		printf("[ HYPERV_SERVICE ] Bad route, only allowed is /vm/{id}: %s\n", url);
		return MHD_NO;
	}
	
	const char *id_str = url + strlen(prefix);
	int id = atoi(id_str);

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

	signal(SIGTERM, stop);
	signal(SIGINT, stop);

	const char* port = getenv(PORT_ENV);

	if (port == NULL) {
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
	printf("[ HYPERV_SERVICE ] Program ends\n");
	return 0;
}
