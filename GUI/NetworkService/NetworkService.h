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

#endif