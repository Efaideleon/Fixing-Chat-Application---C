#ifndef FRIEND_LIST_UI_HEADER
#define FRIEND_LIST_UI_HEADER

#include <stdlib.h>
#include "gtk/gtk.h"
#include "../FriendRequestHandler/FriendRequestHandler.h"
#include "../../TestClient.h"

typedef struct
{
    GtkWidget *window;
    GtkWidget *button;
    GtkWidget *label;
    GtkWidget *scroll_window;
    GtkWidget *vbox;
    GtkWidget *table;
    char *fl;
} FriendListUI;

typedef struct
{
    GtkWidget *widget;
    FriendRequestHandler *friend_request_handler;
} FriendListUIData;

/**
 * @brief Create a friend list ui object using malloc()
 * 
 * @return FriendListUI* 
 */
FriendListUI *create_friend_list_ui(FriendRequestHandler *friend_request_handler);

/**
 * @brief Destroys the FriendListUI->window by calling `gtk_widget_destroy()`
 * frees the memory allocated to friend_list_ui 
 * 
 * @param friend_list_ui 
 */
void destroy_friend_list_ui(FriendListUI *friend_list_ui);

void close_friend_window_proxy(GtkWidget *widget, gpointer data);
void create_Remove_Friend_Window_proxy(GtkWidget *widget, gpointer data);
void create_Add_Friend_Window_proxy(GtkWidget *widget, gpointer data);
void update_contact_list_proxy(GtkWidget *widget, gpointer data);
void delete_friend_window_proxy(GtkWidget *widget, gpointer data);


#endif