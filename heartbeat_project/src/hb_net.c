#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<stddef.h>
#include<net_utils.h>
#include<hb_net.h>


hb_net_status_t
init_sock(sock_info_t* sock, ip_t ip, port_t port, socket_prot_e type)
{

	if (sock == NULL) {
		return HB_NET_NULL_PARAMS;
	}

	sock->fd = socket(AF_INET, type == UDP ? SOCK_DGRAM : SOCK_STREAM, 0);

	if (sock->fd == -1) {
		// LOG("[ ERROR ] Failure in socket() call: %s", strerr(errno));
		
		return HB_NET_FAILURE;

	}

	struct sockaddr_in addr = {AF_INET, toHex(port), {ip}};

	if (bind(sock->fd, (const struct sockaddr*) &addr, sizeof(addr)) == -1) {
		// LOG("[ ERROR ] Failure in socket() call: %s", strerr(errno));

		return HB_NET_FAILURE;
	}

	sock->ip = ip;

	sock->port = (port_t) port;

	return HB_NET_SUCCESS;

}

hb_net_status_t
init_sock_str_ip(sock_info_t* sock, const char *ip, port_t port, socket_prot_e type)
{
	if (ip == NULL) {
		return HB_NET_NULL_PARAMS;
	}

	ip_t f_ip;

	if (str_to_ip(ip, &f_ip) != HB_NET_SUCCESS) {
		return HB_NET_BAD_ARGS;
	}

	return init_sock(sock, f_ip, port, type);
}


hb_net_status_t
init_udp(sock_info_t* sock, ip_t ip, port_t port)
{
	return init_sock(sock, ip, port, UDP);
}

hb_net_status_t
init_udp_str_ip(sock_info_t *sock, const char *ip, port_t port)
{
	return init_sock_str_ip(sock, ip, port, UDP);
}



hb_net_status_t
init_tcp(sock_info_t* sock, ip_t ip, port_t port)
{
	return init_sock(sock, ip, port, TCP);
}

hb_net_status_t
init_tcp_str_ip(sock_info_t *sock, const char *ip, port_t port)
{
	return init_sock_str_ip(sock, ip, port, TCP);
}

hb_net_status_t
connect_socket(const sock_info_t *sock, ip_t ip, port_t port)
{
	if (sock == NULL) {
		return HB_NET_NULL_PARAMS;
	}

	struct sockaddr_in addr = {AF_INET, toHex(port), {ip}};

	if (connect(sock->fd, (const struct sockaddr*) &addr, sizeof(addr)) == -1) {
		return HB_NET_FAILURE;
	}

	return HB_NET_SUCCESS;
}

hb_net_status_t
connect_socket_str_ip(const sock_info_t *sock, const char* ip, port_t port)
{
	if (ip == NULL) {
		return HB_NET_NULL_PARAMS;
	}

	ip_t f_ip;

	if (str_to_ip(ip, &f_ip) != HB_NET_SUCCESS) {
		return HB_NET_BAD_ARGS;
	}

	return connect_socket(sock, f_ip, port);

}

hb_net_status_t
listen_socket(const sock_info_t *sock)
{
	if (sock == NULL) {
		return HB_NET_NULL_PARAMS;
	}

	if (listen(sock->fd, 5) == -1) {
		return HB_NET_FAILURE;
	}

	return HB_NET_SUCCESS;
}

hb_net_status_t
accept_socket(const sock_info_t *sock, sock_info_t* incoming)
{
	if (sock == NULL || incoming == NULL) {
		return HB_NET_NULL_PARAMS;
	}

	struct sockaddr_in incoming_addr;

	incoming->fd = accept(sock->fd, (struct sockaddr*)&incoming_addr, NULL);

	if (incoming->fd == -1) {
		return HB_NET_FAILURE;
	}

	incoming->ip = incoming_addr.sin_addr.s_addr;
	incoming->port = incoming_addr.sin_port;

	return HB_NET_SUCCESS;
}


hb_net_status_t
send_packet_to(const sock_info_t *sock, const void* buf, size_t len, ip_t ip, port_t port)
{
	if (sock == NULL || buf == NULL) {
		return HB_NET_NULL_PARAMS;
	}

	struct sockaddr_in addr = {AF_INET, toHex(port), {ip}};

	int res = sendto(sock->fd, buf, len, 0, (const struct sockaddr*) &addr, sizeof(addr));
	
	if (res == -1) {
		return HB_NET_FAILURE;
	}

	return HB_NET_SUCCESS;

}

hb_net_status_t
send_packet(const sock_info_t* sock, const void *buf, size_t len)
{
	if (sock == NULL || buf == NULL) {
		return HB_NET_NULL_PARAMS;
	}


	if (send(sock->fd, buf, len, 0) == -1) {
		return HB_NET_FAILURE;
	}

	return HB_NET_SUCCESS;

}

hb_net_status_t
receive_packet(const sock_info_t *sock, void* buf, size_t len)
{
	if (sock == NULL) {
		return HB_NET_NULL_PARAMS;
	}

	if (recv(sock->fd, buf, len, 0) == -1) {
		return HB_NET_FAILURE;
	}

	return HB_NET_SUCCESS;
}



hb_net_status_t
close_socket(sock_info_t *sock)
{
	if (sock == NULL) {
		return HB_NET_NULL_PARAMS;
	}

	if (close(sock->fd) == -1) {
		return HB_NET_FAILURE;
	}

	return HB_NET_SUCCESS;
}
