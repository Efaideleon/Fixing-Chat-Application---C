#include "FriendRequestWidgetUI.h"

void destroy_friend_request_widget_ui(GtkWidget *widget, gpointer data)
{
    gtk_widget_destroy(friend_request_widget_window);
}

void button_clicked_add_proxy(GtkWidget *widget, gpointer data){
    FriendRequestProxyData *friend_request_proxy_data = (FriendRequestProxyData*)data;
    char friendname[40] = {};
    GtkWidget *temp_label = gtk_label_new("");
	gtk_label_set_text(GTK_LABEL(temp_label), gtk_entry_get_text(GTK_ENTRY(friend_request_proxy_data->add_f_entry)));
	strncpy(friendname, gtk_label_get_text(GTK_LABEL(temp_label)), sizeof(friendname));

    button_clicked_add(friend_request_proxy_data->friend_request_handler->message_service->network_service, friendname);
	gtk_widget_destroy(friend_request_widget_window);
}

FriendRequestWidgetUI *create_friend_request_widget_ui(FriendRequestHandler *friend_request_handler)
{
    FriendRequestWidgetUI *friend_request_widget_ui = (FriendRequestWidgetUI*)malloc(sizeof(FriendRequestWidgetUI)); 

    friend_request_widget_ui->friend_request_handler = friend_request_handler;

    FriendRequestProxyData *friend_request_proxy_data = g_new(FriendRequestProxyData, 1);
    friend_request_proxy_data->friend_request_handler = friend_request_widget_ui->friend_request_handler;

    char friend_response[20] = "LABEL FOR INVALID";
	friend_request_widget_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_default_size(GTK_WINDOW(friend_request_widget_window), 80, 80);

    friend_request_proxy_data->friend_request_widget_ui = friend_request_widget_ui;

	friend_request_widget_ui->vbox = gtk_vbox_new(0, 0);
	friend_request_widget_ui->add_f_entry = gtk_entry_new();
	friend_request_widget_ui->label = gtk_label_new("Friend Name: ");
	friend_request_widget_ui->friend_invalid_label = gtk_label_new(friend_response);
	friend_request_widget_ui->button = gtk_button_new_with_label("ADD");
    
    friend_request_proxy_data->add_f_entry = friend_request_widget_ui->add_f_entry;
	g_signal_connect(friend_request_widget_ui->button, "clicked", G_CALLBACK(button_clicked_add_proxy), friend_request_proxy_data);

	gtk_box_pack_start(GTK_BOX(friend_request_widget_ui->vbox),friend_request_widget_ui->label, 0, 0, 0);
	gtk_box_pack_start(GTK_BOX(friend_request_widget_ui->vbox),friend_request_widget_ui->add_f_entry, 0, 0, 0);
	gtk_box_pack_start(GTK_BOX(friend_request_widget_ui->vbox), friend_request_widget_ui->button, 0, 0, 0);
	gtk_box_pack_start(GTK_BOX(friend_request_widget_ui->vbox),friend_request_widget_ui->friend_invalid_label, 0, 0, 0);
	gtk_container_add(GTK_CONTAINER(friend_request_widget_window),friend_request_widget_ui->vbox);
	gtk_widget_show_all(friend_request_widget_window);

	g_signal_connect(friend_request_widget_window, "delete_event", G_CALLBACK(destroy_friend_request_widget_ui), NULL);

    return friend_request_widget_ui;
}
