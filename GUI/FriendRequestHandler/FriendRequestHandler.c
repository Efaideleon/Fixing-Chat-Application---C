#include "FriendRequestHandler.h"

void open_dialog(int OpenDialog, int SocketFD)
{
	GtkWidget *label, *button, *vbox, *window_dialog;
	window_dialog = gtk_window_new(GTK_WINDOW_TOPLEVEL);

	AcceptFriendData *accept_friend_data = g_new(AcceptFriendData, 1);
	accept_friend_data->OpenDialog = &OpenDialog;
	accept_friend_data->SocketFD = SocketFD;
	vbox = gtk_vbox_new(0, 0);
	label = gtk_label_new("Accept New Friend Request!");
	gtk_box_pack_start(GTK_BOX(vbox), label, 0, 0, 0);
	button = gtk_button_new_with_label("ACCEPT");
	g_signal_connect(button, "clicked", G_CALLBACK(accept_friend), accept_friend_data); // where is accept comming from
	g_signal_connect(button, "clicked", G_CALLBACK(destroy_popup), window_dialog);
	gtk_box_pack_start(GTK_BOX(vbox), button, 0, 0, 0);
	button = gtk_button_new_with_label("CLOSE");
	g_signal_connect(button, "clicked", G_CALLBACK(destroy_popup), NULL);
	gtk_box_pack_start(GTK_BOX(vbox), button, 0, 0, 0);
	gtk_container_add(GTK_CONTAINER(window_dialog), vbox);
	gtk_widget_show_all(window_dialog);
}

void show_open_dialog(int match, char contacts[10][30], char *response, int *OpenDialog, int SocketFD, char *username, GtkTextBuffer *message_buffer[10], int i)
{
	if ((match == 1) && (strcmp(contacts[i], response) != 0) && (strcmp(response, username) != 0))
	{
		*OpenDialog = 1;
		open_dialog(*OpenDialog, SocketFD);
		strncpy(response, "", sizeof(*response));
	}
	if (strcmp(response, "No messages were sent to you\n") != 0)
	{
		gtk_text_buffer_insert_at_cursor(message_buffer[i], "\n", -1);
		gtk_text_buffer_insert_at_cursor(message_buffer[i], contacts[i], -1);
		gtk_text_buffer_insert_at_cursor(message_buffer[i], ": ", -1);
		gtk_text_buffer_insert_at_cursor(message_buffer[i], response, -1);
		strncpy(response, "", sizeof(*response));
	}
}

FriendRequestHandler *create_friend_request_handler(MessageService *message_service)
{
	FriendRequestHandler *friend_request_handler = (FriendRequestHandler *)malloc(sizeof(FriendRequestHandler));
	friend_request_handler->friend_flag = 0;
	friend_request_handler->message_service = message_service;
	return friend_request_handler;
}

void destroy_friend_request_handler(FriendRequestHandler *friend_request_handler)
{
	free(friend_request_handler);
}

/**
 * @brief sends a message to the server to accept the friend request
 *
 */
void accept_friend(GtkWidget *widget, gpointer data)
{
	AcceptFriendData *accept_friend_data = (AcceptFriendData *)(data);
	char G_temp[512];
	SendMessage("acceptrequest", G_temp, accept_friend_data->SocketFD);
	strncpy(G_temp, "", sizeof(G_temp));
	accept_friend_data->OpenDialog = 0;
}

void destroy_popup(GtkWidget *widget, gpointer data)
{
	GtkWidget *window_dialog;  
	window_dialog = GTK_WIDGET(data);
	gtk_widget_destroy(window_dialog);
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