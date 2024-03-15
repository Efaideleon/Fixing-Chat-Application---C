#ifndef NETWORK_SERVICE_HEADER
#define NETWORK_SERVICE_HEADER

#include <stdlib.h>
#include "gtk/gtk.h"

typedef struct
{
    char RecvBuf[512];
    char SendBuf[512];
    int SocketFD;
} NetworkService;

/**
 * @brief Create a network service object using malloc
 * 
 * @return NetworkService* 
 */
NetworkService *create_network_service();

/**
 * @brief frees memory allocated to network_service
 * 
 * @param network_service 
 */
void destroy_network_service(NetworkService *network_service);
#endif