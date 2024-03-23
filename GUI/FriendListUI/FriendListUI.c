#include "FriendListUI.h"

void create_chat_window_proxy(GtkWidget *widget, gpointer data)
{
    FriendListUIData *friend_list_ui_data = (FriendListUIData *)(data);
    set_chat_window_flag(friend_list_ui_data->friend_request_handler, 1);
}

void close_friend_window_proxy(GtkWidget *widget, gpointer data)
{
    FriendListUIData *friend_list_ui_data = (FriendListUIData *)(data);
    set_friend_flag(friend_list_ui_data->friend_request_handler, 1);
}

void create_Remove_Friend_Window_proxy(GtkWidget *widget, gpointer data)
{
}

void create_Add_Friend_Window_proxy(GtkWidget *widget, gpointer data)
{
    FriendListUIData *friend_list_ui_data = (FriendListUIData *)(data);
    create_friend_request_widget_ui(friend_list_ui_data->friend_request_handler);
}

void update_contact_list_ui(GtkWidget *widget, gpointer data)
{
    FriendListUIData *friend_list_ui_data = (FriendListUIData *)(data);
    FriendListUI *friend_list_ui = friend_list_ui_data->friend_list_ui;
    FriendRequestHandler *friend_request_handler = friend_list_ui_data->friend_request_handler;

    if (friend_list_ui->fl == NULL)
    {
        friend_list_ui->fl = malloc(30 * sizeof(char));
        friend_list_ui->fl[0] = '\0';
        strcat(friend_list_ui->fl, FriendList());

        int j = 0;
        char *tempf = strtok(friend_list_ui->fl, " ");
        while (j < 10)
        {
            friend_request_handler->FriendL[j] = tempf;
            tempf = strtok(NULL, " ");
            j++;
        }
    }
    char *MessageFF = NULL;
    for (int i = 0; i < 10; i++)
    {

        if (friend_request_handler->FriendL[i] != NULL)
        {
            MessageFF = friend_request_handler->FriendL[i];
        }
        else
        {
            MessageFF = "No Friend";
        }
        // Fills Buttons With Friend List
        if (friend_list_ui->friend_buttons[i] == NULL)
        {
            GtkWidget *new_button = gtk_button_new_with_label(MessageFF);
            friend_list_ui->friend_buttons[i] = new_button;
            strcpy(friend_request_handler->contacts[i], MessageFF);
            gtk_box_pack_start(GTK_BOX(friend_list_ui->vbox), friend_list_ui->friend_buttons[i], 0, 1, 1);
            g_signal_connect(friend_list_ui->friend_buttons[i], "clicked", G_CALLBACK(close_friend_window_proxy), friend_list_ui_data);
            g_signal_connect(friend_list_ui->friend_buttons[i], "clicked", G_CALLBACK(create_chat_window_proxy), friend_list_ui_data);
        }
        else
        {
            gtk_button_set_label(GTK_BUTTON(friend_list_ui->friend_buttons[i]), MessageFF);
            strcpy(friend_request_handler->contacts[i], MessageFF);
        }
        // g_signal_connect(button, "clicked", G_CALLBACK(update_contact_list), NULL);
        // g_signal_connect(friend_list_ui->button, "clicked", G_CALLBACK(CreateWindow), NULL);
    }
}

void delete_friend_window_proxy(GtkWidget *widget, gpointer data)
{
    FriendListUIData *friend_list_ui_data = (FriendListUIData *)(data);
    set_friend_flag(friend_list_ui_data->friend_request_handler, 0);
}

FriendListUI *create_friend_list_ui(FriendRequestHandler **friend_request_handler, char *user_name)
{
    FriendListUI *friend_list_ui = (FriendListUI *)malloc(sizeof(FriendListUI));
    friend_list_ui->user_name = user_name;
    FriendListUIData *friend_list_ui_data = g_new(FriendListUIData, 1);
    friend_list_ui_data->friend_request_handler = *friend_request_handler;
    friend_list_ui_data->friend_list_ui = friend_list_ui;

    friend_list_ui->window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(friend_list_ui->window), 260, 300);
    // g_signal_connect(window, "delete_event", G_CALLBACK(close_program), NULL);

    // initialization of vbox
    friend_list_ui->table = gtk_table_new(3, 10, 0);

    // vbox inside the scroll window

    friend_list_ui->vbox = gtk_vbox_new(0, 0);

    update_contact_list_ui(NULL, friend_list_ui_data);
    // if (friend_list_ui->fl == NULL)
    // {
    //     friend_list_ui->fl = malloc(30 * sizeof(char));
    //     friend_list_ui->fl[0] = '\0';
    //     strcat(friend_list_ui->fl, FriendList());
    // }
    // int j = 0;
    // char *tempf = strtok(friend_list_ui->fl, " ");
    // while (j < 10)
    // {
    //     friend_request_handler->FriendL[j] = tempf;
    //     tempf = strtok(NULL, " ");
    //     j++;
    // }
    // char *MessageFF = NULL;
    // for (int i = 0; i < 10; i++)
    // {

    //     if (friend_request_handler->FriendL[i] != NULL)
    //     {
    //         MessageFF = friend_request_handler->FriendL[i];
    //     }
    //     else
    //     {
    //         MessageFF = "No Friend";
    //     }
    //     // Fills Buttons With Friend List
    //     friend_list_ui->button = gtk_button_new_with_label(MessageFF);
    //     strcpy(friend_request_handler->contacts[i], MessageFF);
    //     gtk_box_pack_start(GTK_BOX(friend_list_ui->vbox),friend_list_ui->button, 0, 1, 1);
    //     g_signal_connect(friend_list_ui->button, "clicked", G_CALLBACK(close_friend_window_proxy), friend_list_ui_data);
    //     g_signal_connect(friend_list_ui->button, "clicked", G_CALLBACK(create_chat_window_proxy), friend_list_ui_data);
    //     // g_signal_connect(button, "clicked", G_CALLBACK(update_contact_list), NULL);
    //     // g_signal_connect(friend_list_ui->button, "clicked", G_CALLBACK(CreateWindow), NULL);
    // }

    friend_list_ui_data->widget = friend_list_ui->window;
    friend_list_ui->scroll_window = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(friend_list_ui->scroll_window), friend_list_ui->vbox);
    friend_list_ui->vbox = gtk_vbox_new(0, 0);
    friend_list_ui->button = gtk_button_new_with_label("  X  ");
    gtk_table_attach(GTK_TABLE(friend_list_ui->table), friend_list_ui->button, 0, 1, 0, 1, GTK_FILL, GTK_FILL, 40, 0);
    // g_signal_connect(friend_list_ui->button, "clicked", G_CALLBACK(Remove_Friend_Window), NULL);
    friend_list_ui->label = gtk_label_new(friend_list_ui->user_name);
    gtk_table_attach(GTK_TABLE(friend_list_ui->table), friend_list_ui->label, 4, 6, 0, 1, GTK_FILL, GTK_FILL, 0, 0);

    // Refresh friend list button
    friend_list_ui->button = gtk_button_new_with_label("  R  ");
    g_signal_connect(friend_list_ui->button, "clicked", G_CALLBACK(update_contact_list_ui), friend_list_ui_data);
    gtk_table_attach(GTK_TABLE(friend_list_ui->table), friend_list_ui->button, 8, 9, 0, 1, GTK_FILL, GTK_FILL, 10, 0);

    // Add friend button
    friend_list_ui->button = gtk_button_new_with_label("  +  ");
    g_signal_connect(friend_list_ui->button, "clicked", G_CALLBACK(create_Add_Friend_Window_proxy), friend_list_ui_data);
    gtk_table_attach(GTK_TABLE(friend_list_ui->table), friend_list_ui->button, 9, 10, 0, 1, GTK_FILL, GTK_FILL, 10, 0);

    gtk_box_pack_start(GTK_BOX(friend_list_ui->vbox), friend_list_ui->table, 0, 1, 1);
    gtk_box_pack_start(GTK_BOX(friend_list_ui->vbox), friend_list_ui->scroll_window, 1, 1, 0);
    friend_list_ui->table = gtk_table_new(3, 10, 0);
    // friend_list_ui->button = gtk_button_new_with_label("Next");
    // gtk_table_attach(GTK_TABLE(friend_list_ui->table), friend_list_ui->button, 9, 10, 0, 1, GTK_FILL, GTK_FILL, 35, 0);
    // g_signal_connect(friend_list_ui->button, "clicked", G_CALLBACK(close_friend_window_proxy), NULL);
    // g_signal_connect(friend_list_ui->button, "clicked", G_CALLBACK(create_chat_window_proxy), NULL);
    // g_signal_connect(friend_list_ui->button, "clicked", G_CALLBACK(update_contact_list_proxy), NULL);
    // // g_signal_connect(friend_list_ui->button, "clicked", G_CALLBACK(CreateWindow), NULL);
    // friend_list_ui->button = gtk_button_new_with_label("Previous");
    // gtk_table_attach(GTK_TABLE(friend_list_ui->table), friend_list_ui->button, 0, 1, 0, 1, GTK_FILL, GTK_FILL, 35, 0);
    // g_signal_connect(friend_list_ui->button, "clicked", G_CALLBACK(delete_friend_window_proxy), NULL);
    // g_signal_connect(friend_list_ui->button, "clicked", G_CALLBACK(CreateWindow), NULL);
    gtk_box_pack_start(GTK_BOX(friend_list_ui->vbox), friend_list_ui->table, 0, 1, 1);
    gtk_container_add(GTK_CONTAINER(friend_list_ui->window), friend_list_ui->vbox);
    return (friend_list_ui);
}

void destroy_friend_list_ui(FriendListUI *friend_list_ui)
{
    gtk_widget_destroy(friend_list_ui->window);
    free(friend_list_ui);
}