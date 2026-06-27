#include <sys/types.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <string.h>
#include <microhttpd.h>
#include<stdio.h>
#include<stdlib.h>
#include"db_dii.h"
#include"ssh_dii.h"

#define PORT_ENV "TARGET_HTTP_PORT"

db_dii_connection_t* db;
ssh_dii_connection_t *target;

int
create_volume(int id)
{
	/* Look in the database for the volume */
	volume_t volume;
	if (get_volume_by_id(db, id, &volume) != DB_DII_SUCCESS) {
		printf("Error intentando recuperar el volumen %d\n", id);
		return -1;
	}

	printf("El volume %d se llama %s y tiene %dkb\n", volume.id, volume.name, volume.size_kb);

	/* Do the ssh to the machine with the info */
	if (ssh_create_volume(target, &volume) != SSH_DII_SUCCESS) {
		printf("Error al intentar hacer el ssh\n");
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

	if (strcmp(method, "POST") != 0) {
		return MHD_NO;
	}		
	
	const char *prefix = "/volume/";
	if (strncmp(url, prefix, strlen(prefix)) != 0) {
		printf("Hemos recibido una ruta incorrecta: %s\n", url);
		return MHD_NO;
	}
	
	const char *id_str = url + strlen(prefix);
	int id = atoi(id_str);

	create_volume(id);

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

	db = init_db_dii();

	if (db == NULL) {
		printf("Error conectando con la base de datos\n");
		return -1;
	}

	target = init_ssh_dii();

	if (target == NULL) {
		printf("Error conectando por ssh\n");
		return -1;
	}

	const char* port = getenv(PORT_ENV);

	if (port == NULL) {
		close_db_dii(db);
		printf("Error, no está definido el puerto en la variable %s\n", PORT_ENV);
		return -1;
	}

	int p_n = atoi(port);

	struct MHD_Daemon *daemon;
	daemon = MHD_start_daemon (MHD_USE_AUTO | MHD_USE_INTERNAL_POLLING_THREAD,
	p_n, NULL, NULL,
	&connection_handler, NULL, MHD_OPTION_END);
	
	if (NULL == daemon) {
		return 1;
	}
	
	(void) getchar ();

	MHD_stop_daemon (daemon);
	close_db_dii(db);
	return 0;
}
