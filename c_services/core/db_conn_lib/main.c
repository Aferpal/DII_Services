#include<db_service.h>
#include<stdio.h>
int
main(void)
{
	db_connection_t* conn = db_dii_connection_new();

	if (db_dii_create_connection(conn, "10.0.2.2", "diicloud_develop", "cloud2526", "DII_CLOUD", 3306) != DB_SUCCESS) {
		printf("No se pudo crear la conexión\n");
		return -1;
	}
	
	db_result_t result;
	db_dii_execute_query(conn, "SELECT * FROM PLAN", &result);

	const char* name;
	const char* st;
	const char* mem;
	for (int i = 0; i < result.n_rows; i++) {
		printf("Fila %d: \n\t", i+1);

		db_dii_get(&result, "name", i, &name);
		db_dii_get(&result, "max_storage", i, &st);
		db_dii_get(&result, "max_memory", i, &mem);
		printf("Name: %s, max_storage: %s, max_memory: %s\n", name, st, mem);
	}

	db_dii_free_result(&result);
	db_dii_disconnect(conn);

	return 0;
}
