#ifndef WINDOW_MANAGER_HEADER
#define WINDOW_MANAGER_HEADER

#include <stdlib.h>
#include "gtk/gtk.h"
#include "../NetworkService/NetworkService.h"
#include "../LoginWindowUI/LoginWindowUI.h"
#include "../FriendListUI/FriendListUI.h"
#include "../ChatWindowUI/ChatWindowUI.h"
#include "../CredentialService/CredentialService.h"
#include <stdio.h>
#include "../../TestClient.h"
#include "../ApplicationManager/ApplicationManager.h"

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

/**
 * @brief Determines which window should be created or destroyed
 * 
 * @param app_manager 
 * @param login_window_ui 
 * @param chat_window_ui 
 * @param friend_list_ui 
 */
void CreateWindow(ApplicationManager *app_manager, LoginWindowUI **login_window_ui, ChatWindowUI **chat_window_ui, FriendListUI **friend_list_ui);
void delete_chat_window();
void close_friend_window();
void create_chat_window();
void delete_friend_window();
void Delete_Friend_Entry();
void Delete_Friend_Entry2();
#endif