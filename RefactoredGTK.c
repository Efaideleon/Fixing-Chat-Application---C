#include <gtk/gtk.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "TestClient.h"
#include "GlobalDefs.h"
#include <sys/time.h>

typedef struct
{
    int *SocketFD;
    char *SendBuf;
    char *RecvBuf;
} NetworkData;

typedef struct
{
    GtkWidget *window;
} GUI;

int main(int argc, char *argv[])
{
    gtk_init(&argc, &argv);

    NetworkData networkData;
    memset(&networkData, 0, sizeof(NetworkData));

    CreateSocket(argc, argv, &networkData.SocketFD, networkData.SendBuf, networkData.RecvBuf);


}