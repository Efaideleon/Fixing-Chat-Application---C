#include "../GlobalDefs.h"
/**
 * @brief 
 * Login Window to register and check credentials
 * @return GtkWidget* 
 */
GtkWidget *Login_Window()
{
	GtkWidget *window, *vbox, *label, *label2, *label3;
	GtkWidget *button, *button2, *button3, *hbutton_box, *hpaned;
	GtkEntryBuffer *buffer;
	GtkEntryBuffer *buffer2;
	GtkWidget *table;

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_default_size(GTK_WINDOW(window), 300, 350);

	// Button Click To End Program
	g_signal_connect(window, "delete_event", G_CALLBACK(close_program), NULL);

	label2 = gtk_label_new("");
	label3 = gtk_label_new("");
	invalid_label = gtk_label_new("");
	table = gtk_table_new(2, 2, 0);
	vbox = gtk_vbox_new(0, 0);
	hpaned = gtk_hpaned_new();

	hbutton_box = gtk_hbutton_box_new();
	buffer = gtk_entry_buffer_new("Empty", -1);
	buffer2 = gtk_entry_buffer_new("Empty", -1);
	label = gtk_label_new("Login");
	gtk_box_pack_start(GTK_BOX(vbox), label, 1, 0, 0);
	label = gtk_label_new("Username:");
	gtk_table_attach(GTK_TABLE(table), label, 0, 1, 0, 1, GTK_FILL, GTK_FILL, 0, 0);
	label = gtk_label_new("Password:");

	gtk_table_attach(GTK_TABLE(table), label, 0, 1, 1, 2, GTK_FILL, GTK_FILL, 0, 0);

	entry = gtk_entry_new();
	gtk_entry_set_buffer(GTK_ENTRY(entry), (buffer));
	gtk_table_attach(GTK_TABLE(table), entry, 2, 6, 0, 1, GTK_FILL, GTK_FILL, 0, 0);

	entry2 = gtk_entry_new();
	gtk_entry_set_buffer(GTK_ENTRY(entry2), (buffer2));
	gtk_table_attach(GTK_TABLE(table), entry2, 2, 6, 1, 2, GTK_FILL, GTK_FILL, 0, 0);

	gtk_box_pack_start(GTK_BOX(vbox), table, 0, 0, 0);
	button = gtk_button_new_with_label("Login");
	button2 = gtk_button_new_with_label("Register");
	button3 = gtk_button_new_with_label("Quit");

	// Button Clicks For Login
	g_signal_connect(button, "clicked", G_CALLBACK(button_clicked), label3);
	g_signal_connect(button, "clicked", G_CALLBACK(button_clicked2), label2);
	g_signal_connect(button, "clicked", G_CALLBACK(create_friend_window), NULL);
	g_signal_connect(button, "clicked", G_CALLBACK(check_credentials), NULL);
	g_signal_connect(button, "clicked", G_CALLBACK(CreateWindow), NULL);

	// Button Clicks for Register
	g_signal_connect(button2, "clicked", G_CALLBACK(button_clicked_register), label3);
	g_signal_connect(button2, "clicked", G_CALLBACK(button_clicked_register2), label2);
	g_signal_connect(button2, "clicked", G_CALLBACK(create_friend_window), NULL);
	g_signal_connect(button2, "clicked", G_CALLBACK(check_credentials), NULL);
	g_signal_connect(button2, "clicked", G_CALLBACK(CreateWindow), NULL);

	// Button Clicks for Quit
	g_signal_connect(button3, "clicked", G_CALLBACK(gtk_main_quit), NULL);
	g_signal_connect(button3, "clicked", G_CALLBACK(close_program), NULL);

	gtk_box_pack_start(GTK_BOX(vbox), invalid_label, 0, 0, 0);
	gtk_box_pack_start(GTK_BOX(hbutton_box), button2, 0, 0, 0);
	gtk_box_pack_start(GTK_BOX(hbutton_box), button, 0, 0, 0);
	gtk_box_pack_start(GTK_BOX(vbox), hbutton_box, 2, 0, 0);
	gtk_container_add(GTK_CONTAINER(window), vbox);

	return (window);
}