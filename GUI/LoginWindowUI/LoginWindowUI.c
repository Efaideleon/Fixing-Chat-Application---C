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
    credentials_data->entry_widget = login_window_ui->entry;
    credentials_data->entry2_widget = login_window_ui->entry2;
    credentials_data->invalid_label_widget = login_window_ui->invalid_label;

    g_signal_connect(login_window_ui->button, "clicked", G_CALLBACK(get_name_and_password), credentials_data);
    g_signal_connect(login_window_ui->button, "clicked", G_CALLBACK(login_in_user), credentials_data);

    // g_signal_connect(login_window_ui.button, "clicked", G_CALLBACK(create_friend_window), NULL);

    g_signal_connect(login_window_ui->button, "clicked", G_CALLBACK(check_login_credentials), NULL);

    // g_signal_connect(login_window_ui.button, "clicked", G_CALLBACK(CreateWindow), NULL);

    // Button Clicks for Register

    g_signal_connect(login_window_ui->button2, "clicked", G_CALLBACK(get_name_and_password), credentials_data);
    g_signal_connect(login_window_ui->button2, "clicked", G_CALLBACK(register_user), credentials_data);

    // g_signal_connect(login_window_ui.button2, "clicked", G_CALLBACK(create_friend_window), NULL);

    g_signal_connect(login_window_ui->button2, "clicked", G_CALLBACK(check_login_credentials), NULL);
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
    GtkWidget *entry_widget; // Entry widget where the user types username
    GtkWidget *entry2_widget; // Entry widget where the user types password
    GtkWidget *invalid_label_widget; // Label that indicates if the credentials are valid
    CredentialService *credential_service; // Reference to CredentialService
    char *name; // Cleaned username in char* form
    char *password; // Cleaned passowrd in char* form
} CredentialsData;

// Helper Functions

/**
 * @brief Get the clean string from an entry widget 
 * @param widget 
 * @param size Size of the expect string
 * @return char* 
 */
char *get_clean_string(GtkWidget *widget, int size)
{
    GtkWidget *temp_data = gtk_labe_new("");
    char string[size];
    gtk_label_set_text(GTK_LABEL(temp_data), gtk_entry_get_text(GTK_ENTRY(widget)));
    strncpy(string, gtk_label_get_text(GTK_LABEL(temp_data)), sizeof(string));
    return string;
}

/**
 * @brief Get the name and password and load it into the CredentialsData
 * @param widget 
 * @param data `CredentialsData*`
 */
void get_name_and_password(GtkWidget *widget, gpointer data)
{
    CredentialsData *credentials_data = (CredentialsData *)data;
    credentials_data->name = get_clean_string(credentials_data->entry_widget, sizeof(credentials_data->credential_service->name));

    credentials_data->password = get_clean_string(credentials_data->entry2_widget, sizeof(credentials_data->credential_service->password));
}

/**
 * @brief Proxy to call `button_clicked()` and `button_clicked` from `CredentialService`
 * @param widget 
 * @param data `CredentialsData*`
 */
void login_in_user(GtkWidget *widget, gpointer data)
{
    CredentialsData *credentials_data = (CredentialsData *)data;
    button_clicked(credentials_data->credential_service, credentials_data->name, credentials_data->name);
    button_clicked2(credentials_data->credential_service, credentials_data->password);
}

/**
 * @brief Proxy to call `button_clicked_register()` and `button_clicked_register2` from `CredentialService`
 * @param widget 
 * @param data `CredentialsData*`
 */
void register_user(GtkWidget *widget, gpointer data)
{
    CredentialsData *credentials_data = (CredentialsData *)data;
    button_clicked_register(credentials_data->credential_service, credentials_data->name);
    button_clicked_register2(credentials_data->credential_service, credentials_data->password);
} 

/**
 * @brief Proxy for the check_credentials function in CredentialService
 * Calls `update_invalid_label()`
 * @param widget NULL
 * @param data Must be of type CredentialsData initiazlied with g_new()
 */
int check_login_credentials(GtkWidget *widget, gpointer data)
{

    CredentialsData *credentials_data = (CredentialsData *)data;
    CredentialService *credential_service = credentials_data->credential_service;
    GtkWidget *invalid_label = credentials_data->invalid_label_widget;
    int logged_in_flag = check_credentials(credential_service);
    update_invalid_label(invalid_label, logged_in_flag);
}

/**
 * @brief Changes the gui label to show if credentials are valid or not
 * @param invalid_label
 * @param logged_in_flag
 */
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