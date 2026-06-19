#include<stdlib.h>
#include<heartbeat_master.h>
#include<hb_net.h>
#include<hb_master_types.h>
#include<net_utils.h>

hb_status_t
get_port_env(port_t *port)
{
	if (port == NULL) {
		return HB_NULL_PARAMS;
	}

	char* port_env = getenv(MASTER_PORT_ENV);

	if (port_env == NULL) {
		return HB_FAILURE;
	}

	uint64_t read_port = strtoul(port_env, NULL, 10);
				
	if (read_port == 0 || read_port > UINT16_MAX) {
		return HB_FAILURE;
	}

	*port = (port_t) read_port;

	return HB_SUCCESS;

}

hb_status_t
create_tcp_server(sock_info_t *sock, port_t port)
{
	if (sock == NULL) {
		return HB_NULL_PARAMS;
	}

	if (init_tcp(sock, DEFAULT_IP, port) != HB_NET_SUCCESS) {
		return HB_FAILURE;
	}

	if (listen_socket(sock) != HB_NET_SUCCESS) {
		return HB_FAILURE;
	}

	return HB_SUCCESS;
}

