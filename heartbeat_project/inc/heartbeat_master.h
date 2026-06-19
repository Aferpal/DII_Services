#ifndef _HEARTBEAT_MASTER_H_
#define _HEARTBEAT_MASTER_H_

#include<hb_types.h>

#include<net_types.h>

hb_status_t get_port_env(port_t *port);

hb_status_t create_tcp_server(sock_info_t *sock, port_t port);

#endif
