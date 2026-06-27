#ifndef _DB_DII_H_
#define _DB_DII_H_

#include"db_volumes.h"

#include"db_hypervisor.h"

#define DB_DII_HOSTNAME_ENV "DB_DII_HOSTNAME"

#define DB_DII_USER_ENV "DB_DII_USER"

#define DB_DII_PASSWORD_ENV "DB_DII_PASSWORD"

#define DB_DII_DATABASE_ENV "DB_DII_DATABASE"

#define DB_DII_PORT_ENV "DB_DII_PORT"

#define DB_DII_SUCCESS 0

#define DB_DII_FAILURE 1

#define DB_DII_NULL_PARAMS 2

#define DB_DII_BAD_ARGS 4

typedef uint32_t db_dii_status_t;

typedef struct db_dii_conection db_dii_connection_t;

db_dii_connection_t* init_db_dii();

db_dii_status_t get_volume_by_id(const db_dii_connection_t *db, uint32_t id, volume_t *vol);

db_dii_status_t get_hypervisor_by_id(const db_dii_connection_t *db, uint32_t id, hypervisor_t *hyperv);

db_dii_status_t get_all_hypervisors(const db_dii_connection_t *db, hypervisor_list_t *list);

db_dii_status_t close_db_dii(db_dii_connection_t* db);

#endif
