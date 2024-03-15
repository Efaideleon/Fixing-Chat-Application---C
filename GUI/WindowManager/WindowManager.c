#include "WindowManager.h"

int main(int argc, char *argv[])
{
    gtk_init(&argc, &argv);

    ApplicationManager *application_manager = create_application_manger();

    LoginWindowUI *login_window_ui = NULL;
    ChatWindowUI *chat_window_ui = NULL;
    FriendListUI *friend_list_ui = NULL;

    CreateSocket(argc, argv, &application_manager->network_service->SocketFD, application_manager->network_service->SendBuf,application_manager->network_service->RecvBuf);

    while (1)
    {
        CreateWindow(application_manager, &login_window_ui, &chat_window_ui, &friend_list_ui);
        while (gtk_events_pending())
        {
            gtk_main_iteration();
        }
    }
    return 0;
}

void CreateWindow(ApplicationManager *app_manager, LoginWindowUI **login_window_ui, ChatWindowUI **chat_window_ui, FriendListUI **friend_list_ui)
{
    int ChatFlag = get_ChatFlag(app_manager);
    int FriendFlag = get_FriendFlag(app_manager);

	if ((ChatFlag == 0) && (FriendFlag == 0) && (*login_window_ui == NULL))
	{
		if (*friend_list_ui != NULL)
		{
            destroy_friend_list_ui(*friend_list_ui);
			*friend_list_ui = NULL;
		}
		*login_window_ui = create_login_window_ui(app_manager->credential_service);
		gtk_widget_show_all((*login_window_ui)->window);
	}
	if ((ChatFlag == 1) && (*chat_window_ui == NULL))
	{
		if ((*friend_list_ui != NULL))
		{
            destroy_friend_list_ui(*friend_list_ui);
			*friend_list_ui = NULL;
		}
		*chat_window_ui = create_chat_window_ui();
		gtk_widget_show_all((*chat_window_ui)->window);
	}

	if ((FriendFlag == 1) && (*friend_list_ui == NULL))
	{
		if (*login_window_ui != NULL)
		{
            destroy_login_window_ui(*login_window_ui);
			*login_window_ui = NULL;
		}
		if (*login_window_ui != NULL)
		{
            destroy_chat_window_ui(*chat_window_ui);
            *chat_window_ui = NULL;
		}
		*friend_list_ui = create_friend_list_ui(app_manager->friend_request_handler);
		gtk_widget_show_all((*friend_list_ui)->window);
	}
}