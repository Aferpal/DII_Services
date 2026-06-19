#include<unistd.h>
#include<defines.h>
#include<hb_net.h>
#include<net_utils.h>
#include<pthread.h>
#include<string.h>
#include<stdlib.h>
#include<hb_master_types.h>
#include<heartbeat_master.h>

port_t listen_port;

hypervisor_status_list_t hyperv_list = {
	.size = 0
};

void*
attend_incoming_nodes(void* p)
{

	sock_info_t listener;

	if (create_tcp_server(&listener, listen_port) != HB_SUCCESS) {
		pthread_exit(0);
	}

	sock_info_t incoming;
	char msg_buffer[HELLO_MSG_SIZE];
	heartbeat_info_t hb_response = {
		.hypervisor_id = 2,
		.seq_number = 120
	};

	while (1) {

		if (accept_socket(&listener, &incoming) != HB_NET_SUCCESS){
			sleep(5);
			continue;
		}

		if (receive_packet(&incoming, msg_buffer, HELLO_MSG_SIZE) != HB_NET_SUCCESS) {
			close_socket(&incoming);
			sleep(5);
			continue;
		}

		if (strncmp(msg_buffer, HELLO_MSG, HELLO_MSG_SIZE) != 0) {
			close_socket(&incoming);
			continue;
		}

		hb_response.hypervisor_id++;
		hb_response.seq_number = (rand() % 255);

		if (send_packet(&incoming, (const void*) &hb_response, sizeof(hb_response)) != HB_NET_SUCCESS) {
			close_socket(&incoming);
			continue;
		}
		
		hyperv_list_append(&hyperv_list, hb_response.id);

		close_socket(&incoming);

	}

	pthread_exit(0);
}

void*
timestamp_checker(void* p)
{
	while (1) {

		sleep(CHECK_TIMEOUT);
	}
}


int
main(void)
{
	
	if (get_port_env(&listen_port) != HB_SUCCESS) {
		return -1;
	}

	pthread_t listener_thread;

	pthread_create(&listener_thread, NULL, &attend_incoming_nodes, NULL);

	pthread_detach(listener_thread);
	
	
	sock_info_t sock_udp;

	init_udp(&sock_udp, DEFAULT_IP, listen_port);

	heartbeat_info_t hb_rec;

	while (1) {
		if (receive_packet(&sock_udp, (void*) &hb_rec, sizeof(hb_rec)) != HB_NET_SUCCESS) {
			sleep(5);
		}

		hyperv_list_update_timestamp(&hyperv_list, hb_rec.hypervisor_id, hb_rec.timestamp);

	}

	return 0;
}
