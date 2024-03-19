#include "FriendListUI.h"


void close_friend_window_proxy(GtkWidget *widget, gpointer data)
{
    FriendListUIData *friend_list_ui_data = (FriendListUIData*)(data);
    set_friend_flag(friend_list_ui_data->friend_request_handler, 1);
}

void create_Remove_Friend_Window_proxy(GtkWidget *widget, gpointer data)
{
}

void create_Add_Friend_Window_proxy(GtkWidget *widget, gpointer data)
{
    FriendListUIData *friend_list_ui_data = (FriendListUIData*)(data);
    set_add_friend_window_flag(friend_list_ui_data->friend_request_handler, 1);
}

void updatae_contact_list_proxy(GtkWidget *widget, gpointer data)
{
    // FriendListUIData *friend_list_ui_data = (FriendListUIData*)(data);
    // updata_contact_list(friend_list_ui_data->widget, friend_list_ui_data->friend_request_handler);
}

void delete_friend_window_proxy(GtkWidget *widget, gpointer data)
{
    FriendListUIData *friend_list_ui_data = (FriendListUIData*)(data);
    set_friend_flag(friend_list_ui_data->friend_request_handler, 0);
}

void create_chat_window_proxy(GtkWidget *widget, gpointer data)
{
    FriendListUIData *friend_list_ui_data = (FriendListUIData*)(data);
    set_chat_window_flag(friend_list_ui_data->friend_request_handler, 1);
}

FriendListUI *create_friend_list_ui(FriendRequestHandler *friend_request_handler)
{
    FriendListUI *friend_list_ui = (FriendListUI *)malloc(sizeof(FriendListUI));
    FriendListUIData *friend_list_ui_data = g_new(FriendListUIData, 1);
    friend_list_ui_data->friend_request_handler = friend_request_handler;

    friend_list_ui->window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(friend_list_ui->window), 260, 300);
    // g_signal_connect(window, "delete_event", G_CALLBACK(close_program), NULL);

    // initialization of vbox
    friend_list_ui->table = gtk_table_new(3, 10, 0);

    // vbox inside the scroll window

    friend_list_ui->vbox = gtk_vbox_new(0, 0);

    if (friend_list_ui->fl == NULL) 
    {
        friend_list_ui->fl = malloc(30 * sizeof(char));
        friend_list_ui->fl[0] = '\0';
        strcat(friend_list_ui->fl, FriendList());
    }
    int j = 0;
    char *tempf = strtok(friend_list_ui->fl, " ");
    while (j < 10)
    {
        friend_request_handler->FriendL[j] = tempf;
        tempf = strtok(NULL, " ");
        j++;
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
        friend_list_ui->button = gtk_button_new_with_label(MessageFF);
        strcpy(friend_request_handler->contacts[i], MessageFF);
        gtk_box_pack_start(GTK_BOX(friend_list_ui->vbox),friend_list_ui->button, 0, 1, 1);
        g_signal_connect(friend_list_ui->button, "clicked", G_CALLBACK(close_friend_window_proxy), friend_list_ui_data);
        g_signal_connect(friend_list_ui->button, "clicked", G_CALLBACK(create_chat_window_proxy), friend_list_ui_data);
        // g_signal_connect(button, "clicked", G_CALLBACK(update_contact_list), NULL);
        // g_signal_connect(friend_list_ui->button, "clicked", G_CALLBACK(CreateWindow), NULL);
    }

    friend_list_ui_data->widget = friend_list_ui->window;
    friend_list_ui->scroll_window = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(friend_list_ui->scroll_window),friend_list_ui->vbox);
    friend_list_ui->vbox = gtk_vbox_new(0, 0);
    friend_list_ui->button = gtk_button_new_with_label("  X  ");
    gtk_table_attach(GTK_TABLE(friend_list_ui->table), friend_list_ui->button, 0, 1, 0, 1, GTK_FILL, GTK_FILL, 40, 0);
    // g_signal_connect(friend_list_ui->button, "clicked", G_CALLBACK(Remove_Friend_Window), NULL);
    // label = gtk_label_new(username);
    // gtk_table_attach(GTK_TABLE(friend_list_ui->table),friend_list_ui->label, 4, 6, 0, 1, GTK_FILL, GTK_FILL, 0, 0);
    friend_list_ui->button = gtk_button_new_with_label("  +  ");
    g_signal_connect(friend_list_ui->button, "clicked", G_CALLBACK(create_Add_Friend_Window_proxy), friend_list_ui_data);
    gtk_table_attach(GTK_TABLE(friend_list_ui->table), friend_list_ui->button, 9, 10, 0, 1, GTK_FILL, GTK_FILL, 40, 0);
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