#include "ChatWindowUI.h"

void send_message_proxy(GtkWidget *widget, gpointer data)
{
    ChatWindowProxyData *chat_window_proxy_data = (ChatWindowProxyData *)data;
    GtkWidget *message_label = gtk_label_new("");
    char sent_message[300];
    int i;
    i = gtk_notebook_get_current_page(GTK_NOTEBOOK(chat_window_proxy_data->notebook));
    gtk_label_set_text(GTK_LABEL(message_label), gtk_entry_get_text(GTK_ENTRY(chat_window_proxy_data->message[i])));
    strncpy(sent_message, gtk_label_get_text(GTK_LABEL(message_label)), sizeof(sent_message));

    gtk_label_set_text(GTK_LABEL(message_label), NULL);
    gtk_text_buffer_insert_at_cursor(chat_window_proxy_data->message_buffer[i], "\n", -1);
    gtk_text_buffer_insert_at_cursor(chat_window_proxy_data->message_buffer[i], "You: ", -1);
    gtk_text_buffer_insert_at_cursor(chat_window_proxy_data->message_buffer[i], sent_message, -1);
    char *send_to_user_name = chat_window_proxy_data->friend_request_handler->contacts[i];
    send_message(chat_window_proxy_data->message_service, sent_message, send_to_user_name);
}

void request_message_proxy(GtkWidget *widget, gpointer data)
{
    ChatWindowProxyData *chat_window_proxy_data = (ChatWindowProxyData *)data;
    if (request_message(chat_window_proxy_data->notebook, chat_window_proxy_data->friend_request_handler->contacts, chat_window_proxy_data->credential_service->username, chat_window_proxy_data->message_service->network_service->SocketFD, &chat_window_proxy_data->OpenDialog, chat_window_proxy_data->message_buffer, chat_window_proxy_data->message_service) == 1)
    {
        show_open_dialog(chat_window_proxy_data->message_service->match, chat_window_proxy_data->friend_request_handler->contacts, chat_window_proxy_data->message_service->response, &chat_window_proxy_data->message_service->OpenDialog, chat_window_proxy_data->message_service->network_service->SocketFD, chat_window_proxy_data->credential_service->username, chat_window_proxy_data->message_buffer, chat_window_proxy_data->message_service->current_page_i, &chat_window_proxy_data->friend_request_handler);
    }
}

void close_chat_window_proxy(GtkWidget *widget, gpointer data)
{
    ChatWindowProxyData *chat_window_proxy_data = (ChatWindowProxyData *)data;
    delete_chat_window(chat_window_proxy_data->message_service);
}

ChatWindowUI *create_chat_window_ui(FriendRequestHandler *friend_request_handler, MessageService *message_service, CredentialService *credential_serivce)
{
    ChatWindowUI *chat_window_ui = (ChatWindowUI *)malloc(sizeof(ChatWindowUI));
    chat_window_ui->friend_request_handler = friend_request_handler;
    chat_window_ui->message_service = message_service;
    chat_window_ui->credential_service = credential_serivce;
    chat_window_ui->window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(chat_window_ui->window), 300, 350);

    ChatWindowProxyData *chat_window_proxy_data = g_new(ChatWindowProxyData, 1);

    gtk_container_set_border_width(GTK_CONTAINER(chat_window_ui->window), 10);

    // message label not to be displayed
    chat_window_ui->message_label = gtk_label_new(" ");

    // Table Container Created
    chat_window_ui->table = gtk_table_new(3, 6, FALSE);
    gtk_container_add(GTK_CONTAINER(chat_window_ui->window), chat_window_ui->table);

    // Create a New notebook, Set Tab
    chat_window_ui->notebook = gtk_notebook_new();
    gtk_notebook_set_tab_pos(GTK_NOTEBOOK(chat_window_ui->notebook), GTK_POS_TOP);
    gtk_table_attach_defaults(GTK_TABLE(chat_window_ui->table), chat_window_ui->notebook, 0, 6, 0, 1);
    gtk_widget_show(chat_window_ui->notebook);

    for (int i = 0; i < 10; i++)
    {
        chat_window_ui->message_buffer[i] = gtk_text_buffer_new(NULL); // Create new buffers
        chat_window_proxy_data->message_buffer[i] = chat_window_ui->message_buffer[i];
    }
    chat_window_proxy_data->message_service = message_service;
    chat_window_proxy_data->friend_request_handler = friend_request_handler;
    chat_window_proxy_data->notebook = chat_window_ui->notebook;
    chat_window_proxy_data->credential_service = chat_window_ui->credential_service;
    chat_window_proxy_data->OpenDialog = chat_window_ui->OpenDialog;
    // Scrolled Window with Text Box
    for (int i = 9; i > -1; i--)
    {
        if (friend_request_handler->contacts[i] != NULL)
        {

            chat_window_ui->text_area[i] = gtk_text_view_new();

            chat_window_ui->message_buffer[i] = gtk_text_view_get_buffer(GTK_TEXT_VIEW(chat_window_ui->text_area[i]));

            chat_window_proxy_data->message_buffer[i] = chat_window_ui->message_buffer[i];
            
            gtk_text_buffer_set_text(chat_window_ui->message_buffer[i], "Hello!", -1);


            GtkWidget *console = gtk_table_new(3, 2, FALSE);

            chat_window_ui->scrolled_window = gtk_vscrollbar_new(gtk_text_view_get_vadjustment(GTK_TEXT_VIEW(chat_window_ui->text_area[i])));

            gtk_table_attach_defaults(GTK_TABLE(console), chat_window_ui->text_area[i], 0, 5, 0, 1);
            gtk_table_attach_defaults(GTK_TABLE(console), chat_window_ui->scrolled_window, 5, 6, 0, 1);

            gtk_widget_set_size_request(chat_window_ui->text_area[i], 200, 200);
            gtk_text_view_set_buffer(GTK_TEXT_VIEW(chat_window_ui->text_area[i]), chat_window_ui->message_buffer[i]);

            // Create Entry
            chat_window_ui->message[i] = gtk_entry_new();
            chat_window_ui->buffer[i] = gtk_entry_buffer_new("Enter Message", -1);
            gtk_entry_set_buffer(GTK_ENTRY(chat_window_ui->message[i]), (chat_window_ui->buffer[i]));

            gtk_table_attach_defaults(GTK_TABLE(console), chat_window_ui->message[i], 0, 4, 1, 2);
            gtk_widget_show(chat_window_ui->message[i]);

            chat_window_proxy_data->message[i] = chat_window_ui->message[i];
            // Create Buttons
            chat_window_ui->button = gtk_button_new_with_label("Send");
            gtk_table_attach_defaults(GTK_TABLE(console), chat_window_ui->button, 5, 6, 1, 2);
            g_signal_connect(chat_window_ui->button, "clicked", G_CALLBACK(send_message_proxy), chat_window_proxy_data);
            gtk_widget_show(chat_window_ui->button);

            chat_window_ui->button = gtk_button_new_with_label("Close");
            g_signal_connect(chat_window_ui->button, "clicked", G_CALLBACK(close_chat_window_proxy), chat_window_proxy_data);

            gtk_table_attach_defaults(GTK_TABLE(console), chat_window_ui->button, 0, 1, 2, 3);
            gtk_widget_show(chat_window_ui->button);

            chat_window_ui->button = gtk_button_new_with_label("Request Message");
            g_signal_connect(chat_window_ui->button, "clicked", G_CALLBACK(request_message_proxy), chat_window_proxy_data);
            gtk_table_attach_defaults(GTK_TABLE(console), chat_window_ui->button, 1, 2, 2, 3);
            gtk_widget_show(chat_window_ui->button);

            chat_window_ui->button = gtk_button_new_with_label("Accept Friend");

            gtk_table_attach_defaults(GTK_TABLE(console), chat_window_ui->button, 2, 3, 2, 3);
            gtk_widget_show(chat_window_ui->button);

            chat_window_ui->button = gtk_button_new_with_label("Remove Friend");
            gtk_table_attach_defaults(GTK_TABLE(console), chat_window_ui->button, 5, 6, 2, 3);
            gtk_widget_show(chat_window_ui->button);

            // Add Page
            chat_window_ui->label = gtk_label_new(friend_request_handler->contacts[i]);
            gtk_notebook_insert_page(GTK_NOTEBOOK(chat_window_ui->notebook), console, chat_window_ui->label, 0);
        }
    }
    gtk_notebook_set_current_page(GTK_NOTEBOOK(chat_window_ui->notebook), 0);

    return chat_window_ui;
}

void destroy_chat_window_ui(ChatWindowUI *chat_window_ui)
{
    gtk_widget_destroy(chat_window_ui->window);
    free(chat_window_ui);
}