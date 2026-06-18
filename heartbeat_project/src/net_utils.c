#include<net_utils.h>
#include<arpa/inet.h>
hb_net_status_t
str_to_ip(const char *ip_str, ip_t *ip)
{
	if (inet_pton(AF_INET, ip_str, ip) != 1) {
		return HB_NET_FAILURE;
	}

	return HB_NET_SUCCESS;

}
