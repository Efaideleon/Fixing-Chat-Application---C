#include "NetworkService.h"

NetworkService *create_network_service()
{
    NetworkService *network_serivce = (NetworkService*)malloc(sizeof(NetworkService));

    return network_serivce;
}

void destroy_network_service(NetworkService *network_service)
{
    free(network_service);
}