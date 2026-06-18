#include<defines.h>
#include<hb_net.h>
#include<stdio.h>

int
main(void)
{

	heartbeat_info_t hb_info = {
		.hypervisor_id = 10,
		.seq_number = 1220
	};

	sock_info_t sock_sender;

	init_udp_str_ip(&sock_sender, "127.0.0.1", 8080);

	sock_info_t sock_rec;

	init_udp_str_ip(&sock_rec, "127.0.0.1", 8081);

	connect_socket_str_ip(&sock_sender, "127.0.0.1", 8081);

	send_packet(&sock_sender, (const void*)&hb_info, sizeof(hb_info), sock_rec.ip, 8081);

	heartbeat_info_t hb_info_cp;

	receive_packet(&sock_rec, (void*) &hb_info_cp, sizeof(hb_info_cp));

	printf("Se ha recibido al final %d %d\n", hb_info_cp.hypervisor_id, hb_info_cp.seq_number);

	return 0;
}
