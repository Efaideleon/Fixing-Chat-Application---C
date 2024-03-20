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
#include "../FriendRequestHandler/FriendRequestHandler.h"

typedef struct
{
    int ChatFlag;
    int FriendFlag;
    GtkWidget *Window;
    GtkWidget *FriendWindow;
    GtkWidget *RemoveFriendWindow;
    GtkWidget *AddFriendWindow;
} WindowManager;

/**
 * @brief Determines which window should be created or destroyed
 * 
 * @param app_manager 
 * @param login_window_ui 
 * @param chat_window_ui 
 * @param friend_list_ui 
 */
void CreateWindow(ApplicationManager *app_manager, LoginWindowUI **login_window_ui, ChatWindowUI **chat_window_ui, FriendListUI **friend_list_ui);
void delete_chat_window(MessageService *message_service);
#endif