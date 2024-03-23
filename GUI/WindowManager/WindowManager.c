#include "WindowManager.h"

void currenttime(int *seconds_rn)
{
	time_t CurrentTime;
	CurrentTime = time(NULL);
	struct tm *myTime = localtime(&CurrentTime);
	*seconds_rn = myTime->tm_sec;
}

int main(int argc, char *argv[])
{
	gtk_init(&argc, &argv);

	ApplicationManager *application_manager = create_application_manger();

	LoginWindowUI *login_window_ui = NULL;
	ChatWindowUI *chat_window_ui = NULL;
	FriendListUI *friend_list_ui = NULL;

	CreateSocket(argc, argv, &application_manager->network_service->SocketFD, application_manager->network_service->SendBuf, application_manager->network_service->RecvBuf);

	int seconds_rn;
	char response[300] = {};
	int match;
	while (1)
	{
		CreateWindow(application_manager, &login_window_ui, &chat_window_ui, &friend_list_ui);
		while (gtk_events_pending())
		{
			currenttime(&seconds_rn);
			if (application_manager->credential_service->signInvalid == TRUE && application_manager->message_service->OpenDialog == 0 && friend_list_ui != NULL) // gotta set OpenDialog to 1 to receive messages
			{
				if ((seconds_rn % 2) == 0)
				{
					SendMessage("request", response, application_manager->network_service->SocketFD);
				}
				match = read_compare(response);
				if ((match == 1) && (strcmp(response, application_manager->credential_service->username) != 0))
				{
					application_manager->message_service->OpenDialog = 1;
					open_dialog(application_manager->message_service->OpenDialog, application_manager->network_service->SocketFD, &application_manager->friend_request_handler);
					strncpy(response, "", sizeof(response));
				}
			}

			if ((chat_window_ui != NULL) && (application_manager->message_service->OpenDialog == 0))
			{
				if ((seconds_rn % 2) == 0)
				{
					if (request_message(chat_window_ui->notebook, application_manager->friend_request_handler->contacts, application_manager->credential_service->username, application_manager->network_service->SocketFD, &chat_window_ui->OpenDialog, chat_window_ui->message_buffer, application_manager->message_service) == 1)
					{
						show_open_dialog(application_manager->message_service->match, application_manager->friend_request_handler->contacts, application_manager->message_service->response, &application_manager->message_service->OpenDialog, application_manager->network_service->SocketFD, application_manager->credential_service->username, chat_window_ui->message_buffer, application_manager->message_service->current_page_i, &application_manager->friend_request_handler);
					}
				}
			}
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
			set_FriendFlag(app_manager, 0);
			*friend_list_ui = NULL;
		}
		*login_window_ui = create_login_window_ui(app_manager->credential_service);
		gtk_widget_show_all((*login_window_ui)->window);
	}

	ChatFlag = get_ChatFlag(app_manager);
	FriendFlag = get_FriendFlag(app_manager);
	if ((ChatFlag == 1) && (*chat_window_ui == NULL))
	{
		if ((*friend_list_ui != NULL))
		{
			destroy_friend_list_ui(*friend_list_ui);
			set_FriendFlag(app_manager, 0);
			*friend_list_ui = NULL;
		}
		*chat_window_ui = create_chat_window_ui(app_manager->friend_request_handler, app_manager->message_service, app_manager->credential_service);
		gtk_widget_show_all((*chat_window_ui)->window);
	}

	ChatFlag = get_ChatFlag(app_manager);
	FriendFlag = get_FriendFlag(app_manager);
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
			set_ChatFlag(app_manager, 0);
			*chat_window_ui = NULL;
		}
		*friend_list_ui = create_friend_list_ui(&app_manager->friend_request_handler, app_manager->credential_service->username);
		gtk_widget_show_all((*friend_list_ui)->window);
	}
}