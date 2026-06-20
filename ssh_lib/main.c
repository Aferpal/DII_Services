#include<ssh_service.h>
#include<stdio.h>

int
main(void)
{
	ssh_connection_t* conn = ssh_dii_connection_new();
	if (ssh_dii_create_connection(conn, "localhost", "root", "cloud2526") != SSH_SUCCESS) {
		printf("Error creando la conn\n");
		return -1;
	}

	ssh_result_t result;
	if (ssh_dii_exec(conn, "/root/bin/create", &result) != SSH_SUCCESS) {
		printf("Error ejecutando el comando\n");
		ssh_dii_disconnect(conn);
		return -1;
	}

	ssh_dii_disconnect(conn);

	printf("El status recibido es %d\n", result.status);

	return 0;
}
