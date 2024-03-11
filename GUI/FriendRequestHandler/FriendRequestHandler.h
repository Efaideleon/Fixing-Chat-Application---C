#ifndef FRIEND_REQUEST_HANDLER_HEADER
#define FRIEND_REQUEST_HANDLER_HEADER

#include <stdlib.h>
#include "gtk/gtk.h"

typedef struct
{
    char *FriendL;
    char contacts[10][30];
    char add_to[40];
    char friendname[50];
    GtkWidget *add_f_entry;
    char friend_name[];
} FriendRequestHandler;

void accept_friend();
void Remove_Friend_Window();
void Add_Friend_Window();
void update_contanct_list();
void button_clicked_add();
void button_clicked_remove();

#endif