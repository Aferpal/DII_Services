#include<mysql.h>
#include<stdlib.h>
#include<db_service.h>
#include<string.h>
#include<stdio.h>
#define STR_PARAM_LEN 32

struct db_connection {
	MYSQL* connection;
	char hostname[STR_PARAM_LEN];
	char user[STR_PARAM_LEN];
	char database[STR_PARAM_LEN];
	uint16_t port;
};


db_connection_t*
db_dii_connection_new()
{
	return malloc(sizeof(struct db_connection));
}

db_status_t db_dii_create_connection(db_connection_t* conn,
		                     const char* host,
				     const char* user,
				     const char* password,
				     const char* database,
				     uint16_t port)
{
	if (conn == NULL || host == NULL || user == NULL ||
            password == NULL || database == NULL) {
		return DB_NULL_PARAMS;
	}

	if (strlen(host) >= STR_PARAM_LEN ||
            strlen(user) >= STR_PARAM_LEN ||
	    strlen(database) >= STR_PARAM_LEN) {
		return DB_BAD_ARGS;
	}

	memset(conn, 0, sizeof(*conn));

	strncpy(conn->hostname, host, STR_PARAM_LEN - 1);

	strncpy(conn->user, user, STR_PARAM_LEN - 1);

	strncpy(conn->database, database, STR_PARAM_LEN - 1);

	conn->connection = mysql_init(NULL);

	if (conn->connection == NULL) {
		return DB_FAILURE;
	}

	my_bool verify = 0;

	mysql_optionsv(conn->connection,
			MYSQL_OPT_SSL_VERIFY_SERVER_CERT,
			&verify);

	if (mysql_real_connect(conn->connection, 
                               conn->hostname,
			       conn->user,
			       password, 
			       conn->database,
			       port,
			       NULL,
			       0) == NULL) {
		printf("[ CORE_DB ] Auth error: %s\n", mysql_error(conn->connection));
		mysql_close(conn->connection);
		return DB_FAILURE;
	}

	return DB_SUCCESS;

}

db_status_t
init_db_dii_result(db_result_t *result, uint64_t n_rows, int n_columns)
{
	if (result == NULL) {
		return DB_NULL_PARAMS;
	}


	result->col_names.columns = malloc( sizeof(char*) * n_columns);
	result->col_names.n_columns = n_columns;

	result->n_rows = n_rows;
	result->n_columns = n_columns;

	result->rows = malloc( sizeof(struct db_row) * n_rows);

	for (int i = 0; i < n_rows; i++) {
		result->rows[i].columns = malloc( sizeof(char*) * n_columns);
		result->rows[i].n_columns = n_columns;
	}

	return DB_SUCCESS;
}

db_status_t
db_dii_free_result(db_result_t *result)
{
	if (result == NULL) {
		return DB_NULL_PARAMS;
	}

	for (int i = 0; i < result->col_names.n_columns; i++) {
		if (result->col_names.columns != NULL && result->col_names.columns[i] != NULL) {
			free(result->col_names.columns[i]);
		}
	}
	free(result->col_names.columns);
	result->col_names.columns = NULL;

	for (int i = 0; i < result->n_rows; i++) {
		
		for (int j = 0; j < result->rows[i].n_columns; j++) {
			if (result->rows[i].columns[j] != NULL) {
				free(result->rows[i].columns[j]);
			}
		}
		free(result->rows[i].columns);
	}

	free(result->rows);
	result->rows = NULL;
	return DB_SUCCESS;
}

db_status_t
db_dii_execute_query(const db_connection_t* conn,
                     const char* query,
		     db_result_t* result)
{
	if (conn == NULL || query == NULL || result == NULL) {
		return DB_NULL_PARAMS;
	}

	if (mysql_query(conn->connection, query) != 0) {
		return DB_FAILURE;
	}

	MYSQL_RES * response = mysql_store_result(conn->connection);

	if (response == NULL) {
		
		if (mysql_field_count(conn->connection) == 0) {
			result->n_rows = mysql_affected_rows(conn->connection);
			return DB_SUCCESS;
		}
		return DB_FAILURE;
	}

	result->n_columns = mysql_num_fields(response);

	result->n_rows = mysql_num_rows(response);
	init_db_dii_result(result, result->n_rows, result->n_columns);
	MYSQL_FIELD* fields = mysql_fetch_fields(response);
	
	for (int i = 0; i < result->n_columns; i++) {
		result->col_names.columns[i] = strdup(fields[i].name);	
	}

	MYSQL_ROW c_row;
	for (int i = 0; i < result->n_rows; i++) {
		
		c_row = mysql_fetch_row(response);
		
		if (c_row == NULL) {
			mysql_free_result(response);
			db_dii_free_result(result);
			return DB_FAILURE;
		}

		for (int j = 0; j < result->n_columns; j++) {
			if (c_row[j] == NULL) {
				result->rows[i].columns[j] = NULL;
				continue;
			}
			result->rows[i].columns[j] = strdup(c_row[j]);
		}
	}

	mysql_free_result(response);

	return DB_SUCCESS;

}


db_status_t
db_dii_get(db_result_t* result, const char* col_name, int row_idx, const char** data)
{
	if (result == NULL || col_name == NULL || data == NULL) {
		return DB_NULL_PARAMS;
	}

	if (row_idx > result->n_rows) {
		return DB_BAD_ARGS;
	}

	int col_idx = -1;

	for (int i = 0; i < result->n_columns; i++) {
		if (strcmp(col_name, result->col_names.columns[i]) == 0) {
			col_idx = i;
		}
	}

	if (col_idx == -1) {
		return DB_BAD_ARGS;
	}

	*data = result->rows[row_idx].columns[col_idx];

	return DB_SUCCESS;
}

db_status_t
db_dii_disconnect(db_connection_t* conn)
{
	mysql_close(conn->connection);
	free(conn);
	return DB_SUCCESS;
}

