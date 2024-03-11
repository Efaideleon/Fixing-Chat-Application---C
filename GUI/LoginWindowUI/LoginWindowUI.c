#include "LoginWindowUI.h"
#include <stdio.h>

void create_login_window_ui(LoginWindowUI *login_window_ui, CredentialService *credential_service)
{
    login_window_ui->window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(login_window_ui->window), 300, 350);

    // Button Click To End Program
    // g_signal_connect(login_window_ui.window, "delete_event", G_CALLBACK(close_program), NULL);
    login_window_ui->label = gtk_label_new("");
    login_window_ui->label3 = gtk_label_new("");
    login_window_ui->invalid_label = gtk_label_new("");
    login_window_ui->table = gtk_table_new(2, 2, 0);
    login_window_ui->vbox = gtk_vbox_new(0, 0);
    login_window_ui->hpaned = gtk_hpaned_new();

    login_window_ui->hbutton_box = gtk_hbutton_box_new();
    login_window_ui->buffer = gtk_entry_buffer_new("Empty", -1);
    login_window_ui->buffer2 = gtk_entry_buffer_new("Empty", -1);
    login_window_ui->label = gtk_label_new("Login");
    gtk_box_pack_start(GTK_BOX(login_window_ui->vbox), login_window_ui->label, 1, 0, 0);
    login_window_ui->label = gtk_label_new("Username:");
    gtk_table_attach(GTK_TABLE(login_window_ui->table), login_window_ui->label, 0, 1, 0, 1, GTK_FILL, GTK_FILL, 0, 0);
    login_window_ui->label = gtk_label_new("Password:");

    gtk_table_attach(GTK_TABLE(login_window_ui->table), login_window_ui->label, 0, 1, 1, 2, GTK_FILL, GTK_FILL, 0, 0);

    login_window_ui->entry = gtk_entry_new();
    gtk_entry_set_buffer(GTK_ENTRY(login_window_ui->entry), (login_window_ui->buffer));
    gtk_table_attach(GTK_TABLE(login_window_ui->table), login_window_ui->entry, 2, 6, 0, 1, GTK_FILL, GTK_FILL, 0, 0);

    login_window_ui->entry2 = gtk_entry_new();
    gtk_entry_set_buffer(GTK_ENTRY(login_window_ui->entry2), (login_window_ui->buffer2));
    gtk_table_attach(GTK_TABLE(login_window_ui->table), login_window_ui->entry2, 2, 6, 1, 2, GTK_FILL, GTK_FILL, 0, 0);

    gtk_box_pack_start(GTK_BOX(login_window_ui->vbox), login_window_ui->table, 0, 0, 0);
    login_window_ui->button = gtk_button_new_with_label("Login");
    login_window_ui->button2 = gtk_button_new_with_label("Register");
    login_window_ui->button3 = gtk_button_new_with_label("Quit");

    // Button Clicks For Login

    CredentialsData *credentials_data = g_new(CredentialsData, 1); // remember to free using g_free()
    credentials_data->credential_service = credential_service;

    credentials_data->data = login_window_ui->entry;
    g_signal_connect(login_window_ui->button, "clicked", G_CALLBACK(get_name_and_usermane), credentials_data);

    credentials_data->data = login_window_ui->entry2;
    g_signal_connect(login_window_ui->button, "clicked", G_CALLBACK(get_password), credentials_data);

    // g_signal_connect(login_window_ui.button, "clicked", G_CALLBACK(create_friend_window), NULL);

    // credentials_data->data = NULL;
    // g_signal_connect(login_window_ui->button, "clicked", G_CALLBACK(check_credentials), NULL);

    // g_signal_connect(login_window_ui.button, "clicked", G_CALLBACK(CreateWindow), NULL);

    // Button Clicks for Register
    // g_signal_connect(login_window_ui.button2, "clicked", G_CALLBACK(button_clicked_register), label3);
    // g_signal_connect(login_window_ui.button2, "clicked", G_CALLBACK(button_clicked_register2), label2);
    // g_signal_connect(login_window_ui.button2, "clicked", G_CALLBACK(create_friend_window), NULL);
    // g_signal_connect(login_window_ui.button2, "clicked", G_CALLBACK(check_credentials), NULL);
    // g_signal_connect(login_window_ui.button2, "clicked", G_CALLBACK(CreateWindow), NULL);

    // Button Clicks for Quit
    // g_signal_connect(login_window_ui.button3, "clicked", G_CALLBACK(gtk_main_quit), NULL);
    // g_signal_connect(login_window_ui.button3, "clicked", G_CALLBACK(close_program), NULL);

    gtk_box_pack_start(GTK_BOX(login_window_ui->vbox), login_window_ui->invalid_label, 0, 0, 0);
    gtk_box_pack_start(GTK_BOX(login_window_ui->hbutton_box), login_window_ui->button2, 0, 0, 0);
    gtk_box_pack_start(GTK_BOX(login_window_ui->hbutton_box), login_window_ui->button, 0, 0, 0);
    gtk_box_pack_start(GTK_BOX(login_window_ui->vbox), login_window_ui->hbutton_box, 2, 0, 0);
    gtk_container_add(GTK_CONTAINER(login_window_ui->window), login_window_ui->vbox);
}

// Helper Structs

typedef struct
{
    GtkWidget *data;
    CredentialService *credential_service;
} CredentialsData;

// Helper Functions

/**
 * @brief
 * Proxy function to call button_clicked from CredentialSerivce.c 
 * @param widget Must be initialized with gtk_entry_new();
 * @param data Must be of type CredentialsData initialized with g_new()
 */
void get_name_and_usermane(GtkWidget *, gpointer data)
{
    CredentialsData *credentials_data = (CredentialsData *)data;

    GtkWidget *temp_data = gtk_label_new("");
    gtk_label_set_text(GTK_LABEL(temp_data), gtk_entry_get_text(GTK_ENTRY(credentials_data->data)));
    
    int NAME_SIZE = sizeof(credentials_data->credential_service->name);
    int USERNAME_SIZE = sizeof(credentials_data->credential_service->username);
 
    char name[NAME_SIZE];
    char username[USERNAME_SIZE];
    strncpy(name, gtk_label_get_text(GTK_LABEL(temp_data)), sizeof(name));
    strncpy(username, gtk_label_get_text(GTK_LABEL(temp_data)), sizeof(username));
    button_clicked(credentials_data->credential_service, name, username);
}

/**
 * @brief
 * Proxy function to call button_clicked2 from CredentialService.c
 * @param widget Must be initialized with gtk_entry_new();
 * @param data Must be of type CredentialsData initialized with g_new()
 */
void get_password(GtkWidget *widget, gpointer data)
{
    CredentialsData *credentials_data = (CredentialsData *)data;

    GtkWidget *temp_data = gtk_label_new("");
    gtk_label_set_text(GTK_LABEL(temp_data), gtk_entry_get_text(GTK_ENTRY(credentials_data->data)));
    
    int PASS_SIZE = sizeof(credentials_data->credential_service->password);

    char password[PASS_SIZE];
    strncpy(password, gtk_label_get_text(GTK_LABEL(temp_data)), sizeof(password));
    button_clicked2(credentials_data->credential_service, password);
}

/**
 * @brief Void function for signin signup validation
 * @param widget NULL
 * @param data Must be of type CredentialsData initiazlied with g_new()
 */
void check_login_credentials(GtkWidget *widget, gpointer data);
