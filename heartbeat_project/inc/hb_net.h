#ifndef _HB_NET_H_
#define _HB_NET_H_
#include"net_types.h"

hb_net_status_t init_sock(sock_info_t* sock, ip_t ip, port_t port, socket_prot_e type);

hb_net_status_t init_sock_str_ip(sock_info_t* sock, const char *ip, port_t port, socket_prot_e type);


hb_net_status_t init_udp(sock_info_t* sock, ip_t ip, port_t port);

hb_net_status_t init_udp_str_ip(sock_info_t *sock, const char *ip, port_t port);


hb_net_status_t init_tcp(sock_info_t* sock, ip_t ip, port_t port);

hb_net_status_t init_tcp_str_ip(sock_info_t *sock, const char *ip, port_t port);


hb_net_status_t connect_socket(const sock_info_t *sock, ip_t ip, port_t port);

hb_net_status_t connect_socket_str_ip(const sock_info_t *sock, const char* ip, port_t port);


hb_net_status_t send_packet(const sock_info_t *sock, const void* buf, size_t len, ip_t ip, port_t port);

hb_net_status_t receive_packet(const sock_info_t *sock, void* buf, size_t len);



hb_net_status_t close_socket(sock_info_t *sock);

#endif
