#ifndef MESSAGE_SERVICE_HEADER
#define MESSAGE_SERVICE_HEADER

#include <stdlib.h>
#include "gtk/gtk.h"

typedef struct
{
    GtkWidget *message;
    char sent_messager[300];
    GtkTextBuffer *messager_buffer[10];
    char st[500];
    int OpenDialog;
} MessageService;

void send_message();
void request_message();

#endif