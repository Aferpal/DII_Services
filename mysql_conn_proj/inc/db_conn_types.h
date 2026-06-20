#ifndef _DB_CONN_TYPES_H_
#define _DB_CONN_TYPES_H

#include<stdint.h>

#include"defines.h"

#define DB_CONN_FAILURE 0

#define DB_CONN_SUCCESS 1

#define DB_CONN_NULL_PARAMS 2

#define DB_CONN_BAD_PARAMS 4 

typedef uint32_t db_conn_result_t;

typedef struct db_conn_config db_conn_config_t;

/*
 *
 *
 */
struct db_conn_config {
	char hostname[DEF_STRING_LEN];
	char user[DEF_STRING_LEN];
	char passwd[DEF_STRING_LEN];
	char db[DEF_STRING_LEN];
	uint32_t port;
	uint64_t flags;
};


db_conn_result_t read_config_from_env(const db_conn_config_t *);

#endif
