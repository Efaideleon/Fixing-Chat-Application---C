#ifndef FRIEND_REQUEST_HANDLER_HEADER
#define FRIEND_REQUEST_HANDLER_HEADER

#include <stdlib.h>
#include "gtk/gtk.h"
#include "../MessageService/MessageService.h"
typedef struct
{
    char *FriendL[11];
    char contacts[10][30];
    char add_to[40];
    char friendname[50];
    GtkWidget *add_f_entry;
    MessageService *message_service;
    int friend_flag;
    int add_friend_window_flag;
    int chat_window_flag;
    // char friend_name[];
} FriendRequestHandler;


typedef struct 
{
    int *OpenDialog;
    int SocketFD;
    char **friend_list;
    FriendRequestHandler *friend_request_handler;
} AcceptFriendData;


void show_open_dialog(int match, char contacts[10][30], char *response, int *OpenDialog, int SocketFD, char *username, GtkTextBuffer *message_buffer[10], int i, FriendRequestHandler **friend_request_handler);

void open_dialog(int OpenDialog, int SocketFD, FriendRequestHandler **friend_request_handler);

void accept_friend(GtkWidget *widget, gpointer data);

void destroy_popup(GtkWidget *widget, gpointer data);

void button_clicked_remove();

/**
 * @brief updates FrindL
 * 
 * @param friend_list_window 
 * @param friend_request_handler 
 */
void update_contact_list(FriendRequestHandler **friend_request_handler);


/**
 * @brief Create a friend request handler object using malloc
 * 
 * @param message_service 
 * @return FriendRequestHandler* 
 */
FriendRequestHandler *create_friend_request_handler(MessageService *message_service);

/**
 * @brief Frees memory allocated to friend_request_handler
 * 
 * @param friend_request_handler 
 */
void destroy_friend_request_handler(FriendRequestHandler *friend_request_handler);

/**
 * @brief Set the friend flag 
 * 1 is friend_list_ui is open, 0 is close friend_list_ui 
 * @param state 
 */
void set_friend_flag(FriendRequestHandler *friend_request_handler, int state);

/**
 * @brief Set the add friend window flag object
 * 1 is add_friend_window is open, 0 is close add_friend_window 
 * 
 * @param friend_request_handler 
 * @param state 
 */
void set_add_friend_window_flag(FriendRequestHandler *friend_request_handler, int state);

/**
 * @brief Set the chat window flag object
 * 1 is chat window is open, 0 is close chat window 
 * 
 * @param friend_request_handler 
 * @param state 
 */
void set_chat_window_flag(FriendRequestHandler *friend_request_handler, int state);

#endif