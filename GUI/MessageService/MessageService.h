#ifndef MESSAGE_SERVICE_HEADER
#define MESSAGE_SERVICE_HEADER

#include <stdlib.h>
#include "gtk/gtk.h"
#include "../NetworkService/NetworkService.h"
typedef struct
{
    GtkWidget *message;
    char sent_messager[300];
    GtkTextBuffer *messager_buffer[10];
    char st[500];
    int OpenDialog;
    NetworkService *network_service;
} MessageService;

void send_message();
void request_message();

/**
 * @brief Create a message service object using malloc
 * 
 * @param network_service 
 * @return MessageService* 
 */
MessageService *create_message_service(NetworkService *network_service);

/**
 * @brief frees memory allocated to message_service
 * 
 * @param message_service 
 */
void destroy_message_service(MessageService *message_service);
#endif