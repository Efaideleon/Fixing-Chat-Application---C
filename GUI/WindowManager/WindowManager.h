#ifndef WINDOW_MANAGER_HEADER
#define WINDOW_MANAGER_HEADER

#include <stdlib.h>
#include "gtk/gtk.h"

typedef struct
{
    int ChatFlag;
    int FriendFlag;
    GtkWidget *Window;
    GtkWidget *FriendWindow;
    GtkWidget *RemoveFriendWindow;
    GtkWidget *AddFriendWindow;
} WindowManager;

void create_friend_window();
void CreateWindow();
void delete_chat_window();
void close_friend_window();
void create_chat_window();
void delete_friend_window();
void Delete_Friend_Entry();
void Delete_Friend_Entry2();

#endif