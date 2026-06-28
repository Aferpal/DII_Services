#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"db_service.h"
#include"db_dii.h"


struct db_dii_conection {
	db_connection_t *conn;
};

db_dii_connection_t* 
init_db_dii()
{
	db_dii_connection_t * res = malloc(sizeof(db_dii_connection_t));
	
	if (res == NULL) {
		printf("[ TARGET_DB ] An error ocurred trying to reserve memory for the connection\n");
		return res;
	}

	res->conn = db_dii_connection_new();

	if (res->conn == NULL) {
		printf("[ TARGET_DB ] An error ocurred trying to create the connection\n");
		db_dii_disconnect(res->conn);
		free(res);
		return NULL;
	}

	const char* port = getenv(DB_DII_PORT_ENV);

	if (port == NULL) {
		printf("[ TARGET_DB ] Error: DB_DII_PORT env is not defined, unable to connect to db\n");
		db_dii_disconnect(res->conn);
		free(res);
		return NULL;
	}

	if ( db_dii_create_connection(res->conn,
                                      getenv(DB_DII_HOSTNAME_ENV),
                                      getenv(DB_DII_USER_ENV),
                                      getenv(DB_DII_PASSWORD_ENV),
                                      getenv(DB_DII_DATABASE_ENV),
                                      atoi(getenv(DB_DII_PORT_ENV))) != DB_SUCCESS ) {
		printf("[ TARGET_DB ] Error: Unable to access the db, either env are not defined or are incorrect\n");
		db_dii_disconnect(res->conn);
		free(res);
		return NULL;
	}

	return res;
}

db_dii_status_t
get_volume_by_id(const db_dii_connection_t *db, uint32_t id, volume_t *vol)
{

	if (db == NULL || vol == NULL) {
		return DB_DII_NULL_PARAMS;
	}

	db_result_t query_result;

	char query[64] = {0};

	snprintf(query, 64, "SELECT * FROM VOLUME WHERE id=%d", id);

	if (db_dii_execute_query(db->conn, query, &query_result) != DB_SUCCESS) {
		return DB_DII_FAILURE;
	}
	

	if (query_result.n_rows != 1) {
		db_dii_free_result(&query_result);
		return DB_DII_FAILURE;
	}

	const char* storage;
	const char* name;
	fflush(stdout);
	if (db_dii_get(&query_result, "name", 0, &name) != DB_SUCCESS ||
            db_dii_get(&query_result, "storage_size_kbytes", 0, &storage) != DB_SUCCESS) {
		db_dii_free_result(&query_result);
		return DB_DII_FAILURE;
	}

	memset(vol, 0, sizeof(*vol));

	vol->id = id;

	strncpy(vol->name, name, STR_PARAM_LEN - 1);

	vol->size_kb=atoi(storage);

	db_dii_free_result(&query_result);

	return DB_DII_SUCCESS;
}

db_dii_status_t
get_vm_by_id(const db_dii_connection_t *db, uint32_t id, vm_t *vm)
{
	if (db == NULL || vm == NULL) {
		return DB_DII_NULL_PARAMS;
	}
	
	char query[64] = {0};

	snprintf(query, 64, "SELECT * FROM VM WHERE id = %d", id);

	db_result_t result;

	if (db_dii_execute_query(db, query, &result) != DB_DII_SUCCESS) {
		return DB_DII_FAILURE;
	}

	if (result.n_rows != 1) {
		db_dii_free_result(&result);
		return DB_DII_FAILURE;
	}

	const char* cpu;
	const char* hyperv;
	const char* memory;
	const char* status;

	if (db_dii_get(&result, "cpu", 0, &cpu) != DB_SUCCESS ||
        db_dii_get(&result, "hyperv", 0, &hyperv) != DB_SUCCESS ||
		db_dii_get(&result, "status", 0, &status) != DB_SUCCESS ||
		db_dii_get(&result, "memory", 0, &memory) != DB_SUCCESS) {

		db_dii_free_result(&result);
		return DB_DII_FAILURE;
	}

	memset(vm, 0, sizeof(*vm));

	vm->id = id;
	vm->cpu = atoi(cpu);
	vm->hyperv = atoi(hyperv);
	vm->memory = atoi(memory);
	vm->status = status[0];

	db_dii_free_result(&result);

	return DB_DII_SUCCESS;
}

db_dii_status_t
get_hypervisor_by_id(const db_dii_connection_t *db, uint32_t id, hypervisor_t *hyperv)
{
	if (db == NULL || hyperv == NULL) {
		return DB_DII_NULL_PARAMS;
	}

	char query[64] = {0};

	snprintf(query, 64, "SELECT * FROM HYPERVISOR WHERE id=%d", id);

	db_result_t result;

	if (db_dii_execute_query(db->conn, query, &result) != DB_SUCCESS) {
		return DB_DII_FAILURE;
	}

	if (result.n_rows != 1) {
		db_dii_free_result(&result);
		return DB_DII_FAILURE;
	}

	const char* hostname;
	const char* iqn;

	if (db_dii_get(&result, "hostname", 0, &hostname) != DB_SUCCESS ||
            db_dii_get(&result, "iqn", 0, &iqn) != DB_SUCCESS) {
		db_dii_free_result(&result);
		return DB_DII_FAILURE;
	}

	memset(hyperv, 0, sizeof(*hyperv));

	hyperv->id = id;
	strncpy(hyperv->hostname, hostname, STR_HOST_LEN - 1);
	strncpy(hyperv->iqn, iqn, STR_IQN_LEN - 1);

	db_dii_free_result(&result);

	return DB_DII_SUCCESS;
}

db_dii_status_t
get_all_hypervisors(const db_dii_connection_t *db, hypervisor_list_t *list)
{
	if (db == NULL || list == NULL) {
		return DB_DII_NULL_PARAMS;
	}

	const char* query = "SELECT * FROM HYPERVISOR";

	db_result_t result;

	if (db_dii_execute_query(db->conn, query, &result) != DB_SUCCESS) {
		return DB_DII_FAILURE;
	}

	const char* id;
	const char* hostname;
	const char* iqn;
	list->size = 0;
	for (int i = 0; i < result.n_rows && i < 8; i++) {
		if (db_dii_get(&result, "hostname", i, &hostname) != DB_SUCCESS ||
                    db_dii_get(&result, "iqn", i, &iqn) != DB_SUCCESS ||
		    db_dii_get(&result, "id", i, &id) != DB_SUCCESS) {
			db_dii_free_result(&result);
			return DB_DII_FAILURE;
		}

		memset(&list->data[i], 0, sizeof(hypervisor_t));

		list->data[i].id = atoi(id);
		strncpy(list->data[i].hostname, hostname, STR_HOST_LEN  -1);
		strncpy(list->data[i].iqn, iqn, STR_IQN_LEN - 1);
		list->size++;
	}

	db_dii_free_result(&result);

	return DB_DII_SUCCESS;
}

db_dii_status_t
get_all_volumes_from_vm_id(const db_dii_connection_t *db, uint32_t id, volume_list_t *list) 
{
	if (db == NULL || list == NULL) {
		return DB_DII_NULL_PARAMS;
	}

	char query[256] = {0};
	const char* fmt = "SELECT VOLUME.id, VOLUME.name, VOLUME.storage_size_kbytes \
						 FROM VOLUME, VM_HAS_VOLUME \
						 WHERE VM_HAS_VOLUME.vm_id = %d AND VM_HAS_VOLUME.volume_id = VOLUME.id;";

	snprintf(query, 256, fmt, id);

	db_result_t result;

	if (db_dii_execute_query(db->conn, query, &result) != DB_SUCCESS) {
		return DB_DII_FAILURE;
	}

	const char* storage;
	const char* name;
	const char* v_id;

	for (int i = 0; i < result.n_rows && i < 8; i++) {

		if (db_dii_get(&result, "name", i, &name) != DB_SUCCESS ||
			db_dii_get(&result, "storage_size_kbytes", i, &storage) != DB_SUCCESS ||
			db_dii_Get(&result, "id", i, &v_id)) {
			db_dii_free_result(&result);
			return DB_DII_FAILURE;
		}

		memset(&list->data[i], 0, sizeof(volume_t));

		list->data[i].id = atoi(id);

		strncpy(list->data[i].name, name, STR_PARAM_LEN - 1);

		list->data[i].size_kb=atoi(storage);
	}
	

	db_dii_free_result(&result);

	return DB_DII_SUCCESS;
}


db_dii_status_t
close_db_dii(db_dii_connection_t* db)
{
	db_dii_disconnect(db->conn);

	free(db);

	return DB_DII_SUCCESS;
}

