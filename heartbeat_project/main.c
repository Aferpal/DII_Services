#include<stdio.h>
#include<unistd.h>
#include<defines.h>
#include<hb_net.h>
#include<net_utils.h>
#include<heartbeat_node.h>

int
main(void)
{
	master_info_t m_info;

	if (init_master_config_default(&m_info) != HB_SUCCESS) {
		printf("Error leyendo la configuración por defecto de master\n");
		return -1;
	} else {
		printf("Se ha leido la configuracion del master:  \n");
		printf("Se ha leido la ip %d.%d.%d.%d\n", getip3(m_info.ip), getip2(m_info.ip), getip1(m_info.ip), getip0(m_info.ip));
		printf("Se ha leido el puerto %d\n\n", m_info.port);
	}

	heartbeat_info_t hb_info = {
		.hypervisor_id = 1,
		.seq_number = 0
	};

	sock_info_t socket;

	init_udp(&socket, DEFAULT_IP, DEFAULT_PORT);

	while (1) {
		if (update_hb_info(&hb_info) == HB_SUCCESS) {
			send_hb_to_master(&socket, &m_info, &hb_info);
		} else {
			printf("Ha habido algun error por ahi\n");
		}

		sleep(TIMEOUT_SECONDS);
	
	}

	close_socket(&socket);

	return 0;
}
