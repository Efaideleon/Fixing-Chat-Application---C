#ifndef FRIEND_REQUEST_WIDGET_UI_HEADER
#define FRIEND_REQUEST_WIDGET_UI_HEADER

#include <stdlib.h>
#include "gtk/gtk.h"

typedef struct
{
    GtkWidget *button;
    GtkWidget *label;
    GtkWidget *label2;
    GtkWidget *vbox;
} FriendRequestWidgetUI;

#endif

/**
 * @brief Destroys the FriendRequestWidgetUI->window by calling `gtk_widget_destroy()`
 * frees the memory allocated to friend_request_widget_ui 
 * 
 * @return FriendRequestWidgetUI* 
 */
FriendRequestWidgetUI *create_friend_request_widget_ui();

/**
 * @brief 
 * 
 * @param friend_request_widget_ui 
 */
void destroy_friend_request_widget_ui(FriendRequestWidgetUI *friend_request_widget_ui);