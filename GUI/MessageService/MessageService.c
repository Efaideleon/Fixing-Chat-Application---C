#include "MessageService.h"

MessageService *create_message_service(NetworkService *network_service)
{
    MessageService *message_service = (MessageService*)malloc(sizeof(MessageService));
    
    message_service->network_service = network_service;
    return message_service;
}

void destroy_message_service(MessageService *message_service)
{
    free(message_service);
}