#include<stdio.h>
#include<mysql.h>
#include<unistd.h>
#include"db_conn.h"

MYSQL db_connection;

db_conn_config_t config;

void
print_mysql_row(char **row, unsigned int n_fields)
{
	printf("Row: ");
	for (unsigned int i=0; i < n_fields; i++) {
		printf("%s ", row[i] ? row[i] : "NULL");
	}
	printf("\n");
}

int
main(void)
{
	printf("Hello World From Alpine!\n");
	
	MYSQL* err;
	
	int err_code;

	mysql_init(&db_connection);
	
	err = mysql_real_connect(
		&db_connection,
		"10.0.2.2",
		"diicloud_develop",
		"cloud2526",
		"DII_CLOUD",
		3306,
		NULL,
		0
	);

	if (err == 0) {
		printf("An error occurred trying to connect to db: %s.\nExiting...\n", mysql_error(&db_connection));
		mysql_close(&db_connection);
		return -1;
	}

	err_code = mysql_query(&db_connection, "SELECT * FROM PLAN;");

	if (err_code != 0) {
		printf("An error occurred trying to query.\n");
	}

	MYSQL_RES *response;

	response = mysql_store_result(&db_connection);

	if (response == 0) {
		printf("An error ocurred trying to retrieve the query\n");
	} else {

		unsigned int n_fields = mysql_num_fields(response);
		
		MYSQL_ROW row = mysql_fetch_row(response);

		while (row != NULL) {
			print_mysql_row(row, n_fields);
			row = mysql_fetch_row(response);
		}

	}

	mysql_free_result(response);
	
	mysql_close(&db_connection);

	return 0;
}
