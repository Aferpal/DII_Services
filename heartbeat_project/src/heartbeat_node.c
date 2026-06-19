#include<fcntl.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<sys/sysinfo.h>
#include<time.h>
#include<heartbeat_node.h>
#include<hb_net.h>
#include<net_utils.h>
#include<defines.h>

#define CONF_BUF_LEN 256

hb_status_t
init_master_config_default(master_info_t *m_info)
{
	/* open the configuration file */
	int hb_conf_fd = open(CONF_PATH, O_RDONLY);

	if (hb_conf_fd == -1) {
		return HB_FAILURE;
	}

	/* read the conf_file contents */
	char conf_buffer[CONF_BUF_LEN];

	ssize_t bytes_read = read(hb_conf_fd, conf_buffer, CONF_BUF_LEN - 1);

	if (close(hb_conf_fd) == -1 || bytes_read < 0) {
		return HB_FAILURE;
	}

	conf_buffer[bytes_read] = '\0';

	/* format the contect looking for data */
	char ip_str[16];
	char *line = strtok(conf_buffer, "\n");
	int master_info = 0;
	int port_info = 0;
	while (line) {
		if (strncmp(line, "HbMasterIp=", 11) == 0) {

			strncpy(ip_str, line + 11, sizeof(ip_str) - 1);
			
			if (str_to_ip(ip_str, &m_info->ip) != HB_NET_SUCCESS) {
				return HB_FAILURE;
			}

			master_info++;

		} else if (strncmp(line, "HbMasterPort=", 13) == 0) {
			uint64_t read_port = strtoul(line + 13, NULL, 10);
			
			if (read_port == 0 || read_port > UINT16_MAX) {
				return HB_FAILURE;
			}

			m_info->port = (port_t) read_port;
			port_info++;
		}

		line = strtok(NULL, "\n");
	}

	if (master_info == 0 || port_info == 0) {
		return HB_FAILURE;
	}

	return HB_SUCCESS;
}

hb_status_t
init_hb_info_with_master(const master_info_t *m_info, heartbeat_info_t* hb_info)
{
	if (m_info == NULL || hb_info == NULL) {
		return HB_NULL_PARAMS;
	}

	sock_info_t sock_tcp;

	if (init_tcp(&sock_tcp, DEFAULT_IP, DEFAULT_PORT) != HB_NET_SUCCESS) {
		return HB_FAILURE;
	}

	if (connect_socket(&sock_tcp, m_info->ip, m_info->port) != HB_NET_SUCCESS) {
		return HB_FAILURE;
	}

	if (send_packet(&sock_tcp, HELLO_MSG, HELLO_MSG_SIZE) != HB_NET_SUCCESS) {
		return HB_FAILURE;
	}

	if (receive_packet(&sock_tcp, (void*) hb_info, sizeof(hb_info)) != HB_NET_SUCCESS) {
		return HB_FAILURE;
	}

	close_socket(&sock_tcp);

	return HB_SUCCESS;
}

hb_status_t
update_hb_info(heartbeat_info_t *info)
{
	if (info == NULL) {
		return HB_NULL_PARAMS;
	}

	struct sysinfo s_info;
	
	if (sysinfo(&s_info) == -1) {
		return HB_FAILURE;
	}

	info->total_memory = s_info.totalram;
	info->free_memory = s_info.freeram;
	info->seq_number++;

	if (time(&info->timestamp) == -1) {
		return HB_FAILURE;
	}
	
	return HB_SUCCESS;

}

hb_status_t
send_hb_to_master(const sock_info_t *sock, const master_info_t *m_info, const heartbeat_info_t *hb_info)
{
	if (send_packet_to(sock, (const void*) hb_info, sizeof((*hb_info)), m_info->ip, m_info->port) != HB_NET_SUCCESS) {
		return HB_FAILURE;
	}

	return HB_SUCCESS;
}

