#include "FriendRequestHandler.h"

FriendRequestHandler *create_friend_request_handler(MessageService *message_service)
{
    FriendRequestHandler *friend_request_handler = (FriendRequestHandler*)malloc(sizeof(FriendRequestHandler));
	friend_request_handler->friend_flag = 0;
    friend_request_handler->message_service = message_service;
    return friend_request_handler;
}

void destroy_friend_request_handler(FriendRequestHandler *friend_request_handler)
{
    free(friend_request_handler);
}

void accept_friend()
{
	// char G_temp[BUFFSIZE];
	// SendMessage("acceptrequest", G_temp, SocketFD);
	// strncpy(G_temp, "", sizeof(G_temp));
	// OpenDialog = 0;
}

void update_contanct_list(GtkWidget *friend_list_window, FriendRequestHandler *friend_request_handler)
{
	// Fix: new Fix
	// GtkWidget *tempFL = friend_list_window;
	// char *tempf = strtok(tempFL, " ");

	// int j = 0;
	// while (j < 10)
	// {
	// 	friend_request_handler->FriendL[j] = tempf;
	// 	tempf = strtok(NULL, " ");
	// 	j++;
	// }
	// char *MessageFF = NULL;
	// for (int i = 0; i < 10; i++)
	// {

	// 	if (friend_request_handler->FriendL[i] != NULL)
	// 	{
	// 		MessageFF = friend_request_handler->FriendL[i];
	// 	}
	// 	else
	// 	{
	// 		MessageFF = "No Friend";
	// 	}

	// 	strcpy(friend_request_handler->contacts[i], MessageFF);
	// }

	// // Fix: new Fix
	// free(tempFL);
}

void button_clicked_add()
{
	// char response_add[40];
	// gtk_label_set_text(GTK_LABEL(data), gtk_entry_get_text(GTK_ENTRY(add_f_entry)));
	// strncpy(friendname, gtk_label_get_text(GTK_LABEL(data)), sizeof(friendname));

	// strcat(add_to, "addto ");
	// strcat(add_to, friendname);
	// SendMessage(add_to, response_add, SocketFD);
	// printf("response from server = %s\n", response_add);

	// strncpy(add_to, "", sizeof(add_to));
	// strncpy(response_add, "", sizeof(response_add));
}

void button_clicked_remove()
{
	// gtk_label_set_text(GTK_LABEL(data), gtk_entry_get_text(GTK_ENTRY(rm_f_entry)));
	// strncpy(friendname, gtk_label_get_text(GTK_LABEL(data)), sizeof(friendname));
}

void set_friend_flag(FriendRequestHandler *friend_request_handler, int state)
{
    friend_request_handler->friend_flag = state;
}


void set_add_friend_window_flag(FriendRequestHandler *friend_request_handler, int state)
{
	friend_request_handler->add_friend_window_flag = state;
}

void set_chat_window_flag(FriendRequestHandler *friend_request_handler, int state)
{
	friend_request_handler->chat_window_flag = state;
}