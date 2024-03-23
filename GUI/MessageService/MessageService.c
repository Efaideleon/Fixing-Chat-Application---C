#include "MessageService.h"

MessageService *create_message_service(NetworkService *network_service)
{
    MessageService *message_service = (MessageService *)malloc(sizeof(MessageService));

    message_service->network_service = network_service;
    message_service->OpenDialog = 0;
    return message_service;
}

void destroy_message_service(MessageService *message_service)
{
    free(message_service);
}

void button_clicked_add(NetworkService *network_service, char friendname[50])
{
	char response_add[40] = {};
    char add_to[40] = {};

	strcat(add_to, "addto ");
	strcat(add_to, friendname);
	SendMessage(add_to, response_add, network_service->SocketFD);
	printf("response from server = %s\n", response_add);

	strncpy(add_to, "", sizeof(add_to));
	strncpy(response_add, "", sizeof(response_add));
}

void send_message(MessageService *message_service, char *sent_message, char *send_to_user_name)
{
    char recieved[300];
    char st[500] = {};
    strcat(st, "sendto ");
    strcat(st, send_to_user_name);
    strcat(st, " ");
    strcat(st, sent_message);

    SendMessage(st, recieved, message_service->network_service->SocketFD);

    strncpy(sent_message, "", sizeof(*sent_message)); /* clear sent_message buffer */
    strncpy(st, "", sizeof(st));                     /* clear st buffer */
    strncpy(st, "", sizeof(st));
}

int request_message(GtkWidget *notebook, char contacts[10][30], char *username, int SocketFD, int *OpenDialog, GtkTextBuffer **message_buffer, MessageService *message_service)
{
    message_service->current_page_i = gtk_notebook_get_current_page(GTK_NOTEBOOK(notebook));

    if ((strcmp(contacts[message_service->current_page_i], username) != 0)) /* only request for message when chat window is open */
    {                                         /* and the current chat window is not yours */
        SendMessage("request", message_service->response, SocketFD);
        message_service->match = read_compare(message_service->response);
        // return that you can call show_open_dialog
        return 1;
    }
    return 0;
}

void delete_chat_window(MessageService *message_service)
{
    message_service->chat_flag = 1;
}

int read_compare(char response[400])
{
    FILE *fp;
    char content[100] = {};
    if ((fp = fopen("/Users/efaideleon/Desktop/Fixing Chat Application in c/UserList", "r+")) == NULL)
    { // Open in read-write mode
        printf("couldn't open file\n");
        return -1; // Indicate error
    }

    while (fgets(content, sizeof(content), fp))
    {
        if (response[0] == '\0')
        {
            break;
        }
        if (strstr(content, response))
        {
            strncpy(content, "", sizeof(content) - 1); // Leave space for null terminator
            content[sizeof(content) - 1] = '\0';       // Add null terminator
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}

void friend_list(MessageService *message_serivce, char *response)
{
    char *Message = "friend_list";
    get_friend_list(Message, response, message_serivce->network_service->SocketFD);
}