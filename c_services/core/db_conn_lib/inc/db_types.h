#ifndef _DB_TYPES_H_
#define _DB_TYPES_H_

#include<stdint.h>

#define DB_FAILURE 0

#define DB_SUCCESS 1

#define DB_NULL_PARAMS 2

#define DB_BAD_ARGS 4

typedef uint32_t db_status_t;

typedef struct db_connection db_connection_t;

typedef struct db_result db_result_t;

typedef struct db_row db_row_t;

struct db_row {
	char **columns;
	int n_columns;
};

struct db_result {
	db_row_t *rows;
	db_row_t col_names;
	uint64_t n_rows;
	int n_columns;
};




#endif
