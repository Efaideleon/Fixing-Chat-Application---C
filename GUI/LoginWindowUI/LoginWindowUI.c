#include "LoginWindowUI.h"
#include <stdio.h>

void get_clean_string(GtkWidget *widget, char *buffer, int size) {
    GtkWidget *temp_data = gtk_label_new("");
    gtk_label_set_text(GTK_LABEL(temp_data), gtk_entry_get_text(GTK_ENTRY(widget)));
    strncpy(buffer, gtk_label_get_text(GTK_LABEL(temp_data)), size - 1); 
    buffer[size - 1] = '\0'; 
}

void get_name_and_password(CredentialsData *credentials_data)
{
    if (credentials_data == NULL)
    {
        fprintf(stderr, "Invalid pointer, credentials_data is undefined in get_name_password.\n");
    }

    char name_buffer[NAME_SIZE];
    char password_buffer[PASSWORD_SIZE];

    get_clean_string(credentials_data->entry_widget, name_buffer, NAME_SIZE);

    get_clean_string(credentials_data->entry2_widget, password_buffer, PASSWORD_SIZE);

    strncpy(credentials_data->name, name_buffer, NAME_SIZE);
    strncpy(credentials_data->password, password_buffer, PASSWORD_SIZE);
}

void login_in_user(GtkWidget *widget, gpointer data)
{
    CredentialsData *credentials_data = (CredentialsData *)data;
    if (credentials_data == NULL)
    {
        fprintf(stderr, "Invalid pointer, credentails_data is undefined in login_in_user.\n");
    }
    get_name_and_password(credentials_data);

    login(credentials_data->credential_service, credentials_data->name, credentials_data->name, credentials_data->password);
}

void register_user(GtkWidget *widget, gpointer data)
{
    CredentialsData *credentials_data = (CredentialsData *)data;
    if (credentials_data == NULL)
    {
        fprintf(stderr, "Invalid pointer, credentials_data is undefined in register_user.\n");
    }
    get_name_and_password(credentials_data);
    
    sign_up(credentials_data->credential_service, credentials_data->name, credentials_data->password);
} 

void check_login_credentials(GtkWidget *widget, gpointer data)
{

    CredentialsData *credentials_data = (CredentialsData *)data;
    if (credentials_data == NULL)
    {
        fprintf(stderr, "Invalid pointer, credentials_data is undefined in check_login_credentials.\n");
    }
    CredentialService *credential_service = credentials_data->credential_service;
    GtkWidget *invalid_label = credentials_data->invalid_label_widget;
    int logged_in_flag = check_credentials(credential_service);
    update_invalid_label(invalid_label, logged_in_flag);
}

void update_invalid_label(GtkWidget *invalid_label, int logged_in_flag)
{
    if (!logged_in_flag)
    {
        gtk_label_set_text(GTK_LABEL(invalid_label), "invalid");
    }
    else
    {
        gtk_label_set_text(GTK_LABEL(invalid_label), "Success!");
    }
}

LoginWindowUI *create_login_window_ui(CredentialService *credential_service)
{
    LoginWindowUI *login_window_ui = (LoginWindowUI*)malloc(sizeof(LoginWindowUI));
    login_window_ui->window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(login_window_ui->window), 300, 350);

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

    CredentialsData *credentials_data = g_new(CredentialsData, 1); 
    credentials_data->credential_service = credential_service;
    credentials_data->entry_widget = login_window_ui->entry;
    credentials_data->entry2_widget = login_window_ui->entry2;
    credentials_data->invalid_label_widget = login_window_ui->invalid_label;

    g_signal_connect(login_window_ui->button, "clicked", G_CALLBACK(login_in_user), credentials_data);

    g_signal_connect(login_window_ui->button, "clicked", G_CALLBACK(check_login_credentials), credentials_data);

    // Button Clicks for Register

    g_signal_connect(login_window_ui->button2, "clicked", G_CALLBACK(register_user), credentials_data);

    g_signal_connect(login_window_ui->button2, "clicked", G_CALLBACK(check_login_credentials), credentials_data);

    gtk_box_pack_start(GTK_BOX(login_window_ui->vbox), login_window_ui->invalid_label, 0, 0, 0);
    gtk_box_pack_start(GTK_BOX(login_window_ui->hbutton_box), login_window_ui->button2, 0, 0, 0);
    gtk_box_pack_start(GTK_BOX(login_window_ui->hbutton_box), login_window_ui->button, 0, 0, 0);
    gtk_box_pack_start(GTK_BOX(login_window_ui->vbox), login_window_ui->hbutton_box, 2, 0, 0);
    gtk_container_add(GTK_CONTAINER(login_window_ui->window), login_window_ui->vbox);

    return login_window_ui;
}

void destroy_login_window_ui(LoginWindowUI *login_window_ui)
{
    gtk_widget_destroy(login_window_ui->window);
    free(login_window_ui);
}

