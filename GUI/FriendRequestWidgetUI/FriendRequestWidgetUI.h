#ifndef FRIEND_REQUEST_WIDGET_UI_HEADER
#define FRIEND_REQUEST_WIDGET_UI_HEADER

#include <stdlib.h>
#include "gtk/gtk.h"
#include "../FriendRequestHandler/FriendRequestHandler.h"
#include "../MessageService/MessageService.h"
typedef struct
{
    GtkWidget *button;
    GtkWidget *label;
    GtkWidget *label2;
    GtkWidget *vbox;
    GtkWidget *friend_invalid_label;
    GtkWidget *add_f_entry;
    FriendRequestHandler *friend_request_handler;
} FriendRequestWidgetUI;

GtkWidget *friend_request_widget_window;
typedef struct
{
    GtkWidget *add_f_entry;
    FriendRequestHandler *friend_request_handler;
    FriendRequestWidgetUI *friend_request_widget_ui;
} FriendRequestProxyData;


/**
 * @brief Destroys the FriendRequestWidgetUI->window by calling `gtk_widget_destroy()`
 * frees the memory allocated to friend_request_widget_ui 
 * 
 * @return FriendRequestWidgetUI* 
 */
FriendRequestWidgetUI *create_friend_request_widget_ui(FriendRequestHandler *friend_request_handler);

/**
 * @brief frees the allocated memory to friend_request_widget_iu
 * destroyes the window gtk widget
 * 
 * @param widget 
 * @param data 
 */
void destroy_friend_request_widget_ui(GtkWidget *widget, gpointer data);


/**
 * @brief calls button_clicked_add() from message service
 * sends a friend request message to a friend
 * Used by G_CALLBACK
 * @param widget 
 * @param data 
 */
void button_clicked_add_proxy(GtkWidget *widget, gpointer data);

#endif