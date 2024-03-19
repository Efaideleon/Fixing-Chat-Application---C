#ifndef APPLICATION_MANAGER_HEADER
#define APPLICATION_MANAGER_HEADER

#include "../NetworkService/NetworkService.h"
#include "../MessageService/MessageService.h"
#include "../FriendRequestHandler/FriendRequestHandler.h"
#include "../CredentialService/CredentialService.h"

typedef struct
{
    NetworkService *network_service;
    MessageService *message_service;
    FriendRequestHandler *friend_request_handler;
    CredentialService *credential_service;
    int *ChatFlag; // When friend is clicked, it's set to 1 create ChatWindow
    int *FriendFlag; // When the user logs in it's set to 1 to create FriendFlag
} ApplicationManager;

/**
 * @brief Create a application manger object using malloc
 * 
 * @return ApplicationManager* 
 */
ApplicationManager *create_application_manger();

/**
 * @brief frees memory allocated to *application_manager and all the attributes it depends on
 * 
 * @param app_manager 
 */
void destroy_application_manager(ApplicationManager *app_manager);

/**
 * @brief Get the FriendFlag state
 * 
 * @param app_manager 
 * @return int 
 */
int get_FriendFlag(ApplicationManager *app_manager);

/**
 * @brief Get the ChatFlag state 
 * 
 * @param app_manager 
 * @return int 
 */
int get_ChatFlag(ApplicationManager *app_manager);

/**
 * @brief Set the chat_flag in message service to open and close chat window 
 * 
 * @param app_manager 
 * @param state 
 */
void set_ChatFlag(ApplicationManager *app_manager, int state);

/**
 * @brief Set the friend_flag in friend_request_handler to open and close friend window
 * 
 * @param app_manager 
 * @param state 
 */
void set_FriendFlag(ApplicationManager *app_manager, int state);
#endif