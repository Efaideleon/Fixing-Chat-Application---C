#include <stdlib.h>
#include "gtk/gtk.h"
#include "../MessageService/MessageService.h"
#include "../FriendRequestHandler/FriendRequestHandler.h"
#include "../CredentialService/CredentialService.h"
typedef struct
{
    GtkWidget *window;
    GtkWidget *scrolled_window;
    GtkWidget *button;
    GtkWidget *table;
    GtkWidget *label;
    GtkWidget *text_area[10];
    GtkEntryBuffer *buffer[10];
    GtkWidget *message_label;
    GtkWidget *notebook;
    GtkWidget *message[10];
    GtkTextBuffer *message_buffer[10];
    MessageService *message_service;
    FriendRequestHandler *friend_request_handler;
    CredentialService *credential_service;
    int OpenDialog;
} ChatWindowUI;

typedef struct 
{
    GtkWidget *notebook;
    GtkWidget *message[10];
    GtkTextBuffer *message_buffer[10];
    FriendRequestHandler *friend_request_handler;
    MessageService *message_service;
    CredentialService *credential_service;
    int OpenDialog;
} ChatWindowProxyData;

/**
 * @brief Create a chat window ui object using malloc()
 * 
 * @return ChatWindowUI* 
 */
ChatWindowUI *create_chat_window_ui(FriendRequestHandler *friend_request_handler, MessageService *message_service, CredentialService *credential_service);

/**
 * @brief Destroys the ChatWindowUI->window by calling `gtk_widget_destroy()`
 * frees the memory allocated to chat_window_ui 
 * 
 * @param chat_window_ui 
 */
void destroy_chat_window_ui(ChatWindowUI *chat_window_ui);

void send_message_proxy(GtkWidget *widget, gpointer data);

void request_message_proxy(GtkWidget *widget, gpointer data);

void close_chat_window_proxy(GtkWidget *widget, gpointer data);