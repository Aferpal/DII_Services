#include"hyperv_connections.h"
#include"hypervisor.h"
#include<stddef.h>
#include<stdlib.h>
#include<string.h>
void
init_hyperv_connections_on_db_data(const db_dii_connection_t *db, hyperv_connections_t *conns)
{
	if (db == NULL || conns == NULL) {
		return;
	}

	const char* user = getenv(SSH_HYPERV_USER_ENV);
	const char* password = getenv(SSH_HYPERV_PASSWORD_ENV);
	
	if (user == NULL || password == NULL) {
		return;
	}

	hypervisor_list_t h_list;

	if (get_all_hypervisors(db, &h_list) != DB_DII_SUCCESS) {
		return;
	}

	memset(conns, 0, sizeof(*conns));

	int curr = 0;
	for (uint32_t i = 0; i < h_list.size; i++) {
		conns->data[curr] = init_ssh_dii_params(h_list.data[i].hostname,
                                                     user,
						     password);
		if (conns->data[curr] != NULL) {
			conns->size++;
			curr++;
		}
	}

	return;
}

void
clean_connections(const hyperv_connections_t *conns)
{
	for (uint32_t i = 0; i < conns->size; i++) {
		if (conns->data[i] == NULL) {
			continue;
		}
		close_ssh_dii(conns->data[i]);
	}
}

