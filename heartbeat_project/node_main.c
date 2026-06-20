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
		return -1;
	} 

	heartbeat_info_t hb_info;

	if (init_hb_info_with_master(&m_info, &hb_info) != HB_SUCCESS) {
		return -1;
	}

	sock_info_t socket;

	init_udp(&socket, DEFAULT_IP, DEFAULT_PORT);

	while (1) {
	
		if (update_hb_info(&hb_info) == HB_SUCCESS) {
			send_hb_to_master(&socket, &m_info, &hb_info);
		}

		sleep(TIMEOUT_SECONDS);
	
	}

	close_socket(&socket);

	return 0;
}
