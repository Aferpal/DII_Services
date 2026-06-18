#include<stdlib.h>
#include<string.h>

#include<db_conn_types.h>

db_conn_result_t
db_conn_config_init(db_conn_config_t* config, char* hostname, char* username, char* password, char* db_name, uint32_t port, uint64_t flags)
{
	if (config == NULL || hostname == NULL || username == NULL || password == NULL || db_name == NULL) {
		return DB_CONN_NULL_PARAMS;
	}

	if (strlen(hostname) >= sizeof(config->hostname) || 
	    strlen(username) >= sizeof(config->username) ||
	    strlen(password) >= sizeof(config->password) ||
	    strlen(db_name) >= sizeof(config->db)) {
		return DB_CONN_BAD_PARAMS;
	}

	strncpy(config->hostname, hostname, sizeof(config->hostname));

	strncpy(config->username, username, sizeof(config->username));

	strncpy(config->password, password, sizeof(config->password));

	strncpy(config->db, db_name, sizeof(config->db));

	config->port = port;

	config->flags = flags;

	return DB_CONN_SUCCESS;
}

db_conn_result_t 
read_config_from_env(db_conn_config_t *config)
{
	if ( db_conn_config_init(config, 
				 getenv(ENV_BD_HOST),
				 getenv(ENV_DB_USER),
				 getenv(ENV_DB_PASSWORD),
				 getenv(ENV_DB_DATABASE)) != DB_CONN_SUCCESS) {
		return DB_CONN_FAILURE;
	}
	
	return DB_CONN_SUCCESS;

}
