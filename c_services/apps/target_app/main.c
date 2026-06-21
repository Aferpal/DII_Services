#include <sys/types.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <string.h>
#include <microhttpd.h>
#include<stdio.h>

#define PORT 8888

void
create_volume(int id)
{
	/* Look in the database for the volume */
	/* Do the ssh to the machine with the info */
}

static enum MHD_Result
connection_handler (void *cls, struct MHD_Connection *connection,
	const char *url, const char *method,
	const char *version, const char *upload_data,
	size_t *upload_data_size, void **req_cls)
{

	if (strcmp(method, "POST") != 0) {
		return MHD_NO;
	}		
	
	const char *prefix = "/volume/";
	if (strncmp(url, prefix, strlen(prefix)) != 0) {
		return MHD_NO;
	}
	
	const char *id_str = url + strlen(prefix);
	int id = atoi(id_str);

	create_volume(id);

	struct MHD_Response *response;
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
	struct MHD_Daemon *daemon;
	daemon = MHD_start_daemon (MHD_USE_AUTO | MHD_USE_INTERNAL_POLLING_THREAD,
	PORT, NULL, NULL,
	&connection_handler, NULL, MHD_OPTION_END);
	
	if (NULL == daemon) {
		return 1;
	}
	
	(void) getchar ();
	MHD_stop_daemon (daemon);
	return 0;
}
