#ifndef _DB_SERVICE_H_
#define _DB_SERVICE_H_

#include"db_types.h"

db_connection_t* db_dii_connection_new();

db_status_t db_dii_create_connection(db_connection_t* conn,
                                     const char* host,
				     const char* user,
				     const char* password,
				     const char* database,
				     uint16_t port);

db_status_t db_dii_execute_query(const db_connection_t* conn,     
                                 const char* query,
				 db_result_t* result);

db_status_t db_dii_get(db_result_t* result, const char* col_name, int row_idx, const char** data);

db_status_t db_dii_free_result(db_result_t* result);

db_status_t db_dii_disconnect(db_connection_t* conn);

#endif
