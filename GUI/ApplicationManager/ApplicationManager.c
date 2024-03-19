#include "ApplicationManager.h"

ApplicationManager *create_application_manger()
{
    ApplicationManager *app_manager = (ApplicationManager *)malloc(sizeof(ApplicationManager));

    app_manager->network_service = create_network_service();
    app_manager->credential_service = create_credential_service(app_manager->network_service);
    app_manager->message_service = create_message_service(app_manager->network_service);
    app_manager->friend_request_handler = create_friend_request_handler(app_manager->message_service);
    return app_manager;
}

void destroy_application_manager(ApplicationManager *app_manager)
{
    destroy_credential_service(app_manager->credential_service);
    destroy_message_service(app_manager->message_service);
    destroy_network_service(app_manager->network_service);
    destroy_friend_request_handler(app_manager->friend_request_handler);
    free(app_manager);
}

int get_FriendFlag(ApplicationManager *app_manager)
{
    if (app_manager->credential_service->logged_in == 1 || app_manager->friend_request_handler->friend_flag == 1)
    {
        return 1;
    }
    return 0;
}

int get_ChatFlag(ApplicationManager *app_manager)
{
    if (app_manager->friend_request_handler->chat_window_flag == 1)
    {
        return 1;
    }
    return 0;
}

void set_FriendFlag(ApplicationManager *app_manager, int state)
{
    app_manager->credential_service->logged_in = 0;
    app_manager->friend_request_handler->friend_flag = 0;
}

void set_ChatFlag(ApplicationManager *app_manager, int state)
{
    app_manager->friend_request_handler->chat_window_flag = 1;
    app_manager->message_service->chat_flag = 1;
}