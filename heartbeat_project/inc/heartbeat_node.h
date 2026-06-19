#ifndef _HEARTBEAT_NODE_H_
#define _HEARTBEAT_NODE_H_

#include"hb_types.h"

#include"hb_node_types.h"

hb_status_t init_master_config_default(master_info_t *m_info);

hb_status_t init_hb_info_with_master(const master_info_t *m_info, heartbeat_info_t* hb_info);

hb_status_t update_hb_info(heartbeat_info_t *info);

hb_status_t send_hb_to_master(const sock_info_t *sock, const master_info_t *m_info, const heartbeat_info_t *hb_info);

#endif
