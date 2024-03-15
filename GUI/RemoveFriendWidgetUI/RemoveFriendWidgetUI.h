#ifndef REMOVE_FRIEND_WIDGET_UI_HEADER
#define REMOVE_FRIEND_WIDGET_UI_HEADER

#include <stdlib.h>
#include "gtk/gtk.h"

typedef struct
{
    GtkWidget *button;
    GtkWidget *label;
    GtkWidget *label2;
    GtkWidget *hbox;
} RemoveFriendWidgetUI;

RemoveFriendWidgetUI *create_remove_friend_widget_ui();

void destroy_remove_friend_widget_ui(RemoveFriendWidgetUI *remove_friend_widget_ui);
#endif