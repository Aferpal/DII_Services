#include<hb_master_types.h>

hyperv_list_status_t
hyperv_list_init(hypervisor_status_list_t* list)
{
    if (list == NULL) {
        return HYPERV_LIST_NULL_PARAMS;
    }

    if (pthread_mutex_init(&list->lock, NULL) != 0) {
        return HYPERV_LIST_FAILURE;
    }

    list->size = 0;

    return HYPERV_LIST_SUCCESS;
}

hyperv_list_status_t
hyperv_list_lock(hypervisor_status_list_t *list)
{
    if (list == NULL) {
        return HYPERV_LIST_NULL_PARAMS;
    }

    if (pthread_mutex_lock(&list->lock) != 0) {
        return HYPERV_LIST_FAILURE;
    }

    return HYPERV_LIST_SUCCESS;
}

hyperv_list_status_t
hyperv_list_unlock(hypervisor_status_list_t *list)
{
    if (list == NULL) {
        return HYPERV_LIST_NULL_PARAMS;
    }

    if (pthread_mutex_unlock(&list->lock) != 0) {
        return HYPERV_LIST_FAILURE;
    }

    return HYPERV_LIST_SUCCESS;
}

hyperv_list_status_t
hyperv_list_append(hypervisor_status_list_t *list, hypervisor_id_t id)
{
    if (list == NULL) {
        return HYPERV_LIST_NULL_PARAMS;
    }

    int was_full = 1;

    hyperv_list_lock(list);

    if (list->size < CLUSTER_MAX_NODES) {
        was_full = 0;
        list->data[list->size].id = id;
        list->data[list->size].last_timestamp = time(NULL);
        list->data[list->size].status = ON;
        list->size++;
    }

    hyperv_list_unlock(list);

    return was_full == 0 ? HYPERV_LIST_SUCCESS : HYPERV_LIST_FAILURE;
}

hyperv_list_status_t
hyperv_list_update_timestamp(hypervisor_status_list_t *list, hypervisor_id_t id, int64_t timestamp)
{
    if (list == NULL) {
        return HYPERV_LIST_NULL_PARAMS;
    }

    int existed = 0;

    hyperv_list_lock(list);

    for (int i = 0; i < list->size; i++) {
        if (list->data[i].id == id) {
            existed = 1;
            list->data[i].last_timestamp = timestamp;
        }
    }

    hyperv_list_unlock(list);

    return existed == 0 ? HYPERV_LIST_SUCCESS : HYPERV_LIST_FAILURE;
}