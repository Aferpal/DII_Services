#include<defines.h>
#include<net_utils.h>
#include<types.h>
#include<hb_net.h>
#include<sys/sysinfo.h>
#include<time.h>
#include<stdio.h>
#include<unistd.h>

int
main(void)
{

	heartbeat_info_t hb = {
		.hypervisor_id = 1,
		.seq_number = 1
	};

	sock_info_t sock;

	init_udp(&sock, DEFAULT_IP, 9999);

	struct sysinfo s_info;

	ip_t ip;

	if (str_to_ip("10.0.2.2", &ip) != HB_NET_SUCCESS) {
		return -1;	
	}

	while (1) {
		if (sysinfo(&s_info) != -1) {
			hb.total_memory = s_info.totalram;
			hb.free_memory = s_info.freeram;
			hb.seq_number++;
			if (time(&hb.timestamp) != -1) {
				send_packet(&sock, (const void*) &hb, sizeof(hb), ip, 9999);
			} else {
				printf("Failed to get time\n");
			}
			
		} else {
			printf("Failed to get sysinfo\n");
		}

		sleep(TIMEOUT_SECONDS);
	}

	return 0;
}
