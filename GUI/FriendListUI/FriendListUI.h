#ifndef FRIEND_LIST_UI_HEADER
#define FRIEND_LIST_UI_HEADER

#include <stdlib.h>
#include "gtk/gtk.h"

typedef struct
{
    GtkWidget *window;
    GtkWidget *button;
    GtkWidget *label;
    GtkWidget *scroll_window;
    GtkWidget *vbox;
    GtkWidget *table;
} FriendListUI;

#endif