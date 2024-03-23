#ifndef MESSAGE_SERVICE_HEADER
#define MESSAGE_SERVICE_HEADER

#include <stdlib.h>
#include "gtk/gtk.h"
#include "../NetworkService/NetworkService.h"
#include "../../TestClient.h"
typedef struct
{
    GtkWidget *message;
    char sent_messager[300];
    GtkTextBuffer *messager_buffer[10];
    char st[500];
    int OpenDialog;
    NetworkService *network_service;
    int chat_flag;
    int match;
    int current_page_i;
    char response[300];
} MessageService;

void friend_list(MessageService *message_serivce, char *response);

int read_compare(char response[400]);

void send_message(MessageService *message_service, char *sent_message, char *send_to_user_name);

/**
 * @brief checks if a message has been sent to the user and displays in on screen
 * 
 * @param notebook 
 * @param contacts 
 * @param username 
 * @param SocketFD 
 * @param OpenDialog 
 * @param message_buffer 
 * @return int : 1 if it should call show_open_dialog
 */
int request_message(GtkWidget *notebook, char contacts[10][30], char *username, int SocketFD, int *OpenDialog, GtkTextBuffer **message_buffer, MessageService *message_service);

void delete_chat_window(MessageService *message_serivce);

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

/**
 * @brief sends a friend request a friend by their name
 * 
 * @param network_service 
 * @param friendname 
 */
void button_clicked_add(NetworkService *network_service, char friendname[50]);
#endif