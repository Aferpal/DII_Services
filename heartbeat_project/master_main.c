#include<stdio.h>
#include<unistd.h>
#include<defines.h>
#include<hb_net.h>
#include<net_utils.h>
#include<pthread.h>
#include<string.h>
#include<stdlib.h>

void*
attend_incoming_nodes(void*)
{

	sock_info_t listener;

	if (init_tcp(&listener, DEFAULT_IP, 9999) != HB_NET_SUCCESS) {
		printf("init() -> Error trying to create the tcp listener server\n");
		pthread_exit(0);
	}

	if (listen_socket(&listener) != HB_NET_SUCCESS) {
		printf("listen() -> Error trying to create the tcp listener server\n");
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
			printf("Error trying to accept..\n");
			sleep(5);
			continue;
		}

		if (receive_packet(&incoming, msg_buffer, HELLO_MSG_SIZE) != HB_NET_SUCCESS) {
			printf("Error trying to read a packet...\n");
			close_socket(&incoming);
			sleep(5);
			continue;
		}

		if (strncmp(msg_buffer, HELLO_MSG, HELLO_MSG_SIZE) != 0) {
			printf("La cadena recibida no es la esperada...\n");
			close_socket(&incoming);
			continue;
		}

		hb_response.hypervisor_id++;
		hb_response.seq_number = (rand() % 255);

		if (send_packet(&incoming, (const void*) &hb_response, sizeof(hb_response)) != HB_NET_SUCCESS) {
			printf("Error intentando enviar información de hb\n");
			close_socket(&incoming);
			continue;
		}

		close_socket(&incoming);

		printf("Se ha enviado un hyper: %d y un seq: %d\n", hb_response.hypervisor_id, hb_response.seq_number);

	}

	pthread_exit(0);
}

int
main(void)
{
	
	pthread_t listener_thread;

	pthread_create(&listener_thread, NULL, &attend_incoming_nodes, NULL);

	pthread_detach(listener_thread);
	
	
	sock_info_t sock_udp;

	init_udp(&sock_udp, DEFAULT_IP, 9999);

	heartbeat_info_t hb_rec;

	while (1) {
		if (receive_packet(&sock_udp, (void*) &hb_rec, sizeof(hb_rec)) == HB_NET_SUCCESS) {
			printf("Se ha recibido un paquete por con la info: {\n");
			printf("\thypervisor: %d,\n\ttotal_ram: %lu,\n", hb_rec.hypervisor_id, hb_rec.total_memory);
			printf("\tfree_ram: %ld,\n\ttimestamp: %lu,\n", hb_rec.free_memory, hb_rec.timestamp);
			printf("\tseq_number: %d\n}\n", hb_rec.seq_number);
		} else {
			printf("Error trying to rec packet. \n");
			sleep(5);
		}
	}

	return 0;
}
