#ifndef _HB_NET_TYPES_H_
#define _HB_NET_TYPES_H_

#include<stdint.h>

#include<stddef.h>

#define HB_NET_FAILURE 0

#define HB_NET_SUCCESS 1

#define HB_NET_NULL_PARAMS 2

#define HB_NET_BAD_ARGS 4

typedef uint32_t hb_net_status_t;

typedef uint32_t ip_t;

typedef uint16_t port_t;

typedef struct socket_info sock_info_t;

typedef enum SOCKET_PROT socket_prot_e;

enum SOCKET_PROT { UDP, TCP };

struct socket_info {
	int fd;
	ip_t ip;
	port_t port;
	socket_prot_e type;
};

#endif
