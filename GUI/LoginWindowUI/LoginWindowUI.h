#ifndef LOGIN_WINDOW_UI_HEADER
#define LOGIN_WINDOW_UI_HEADER

#include <stdlib.h>
#include "gtk/gtk.h"
#include "../CredentialService/CredentialService.h"
typedef struct
{
    GtkWidget *window;
    GtkWidget *vbox;
    GtkWidget *label;
    GtkWidget *label2;
    GtkWidget *label3;
    GtkWidget *button;
    GtkWidget *button2;
    GtkWidget *button3;
    GtkWidget *hbutton_box;
    GtkWidget *hpaned;
    GtkEntryBuffer *buffer;
    GtkEntryBuffer *buffer2;
    GtkWidget *table;
    GtkWidget *invalid_label;
    GtkWidget *entry;
    GtkWidget *entry2;

} LoginWindowUI;

typedef struct
{
    GtkWidget *entry_widget; // Entry widget where the user types username
    GtkWidget *entry2_widget; // Entry widget where the user types password
    GtkWidget *invalid_label_widget; // Label that indicates if the credentials are valid
    CredentialService *credential_service; // Reference to CredentialService
    char name[NAME_SIZE]; // Cleaned username in char[] form
    char password[PASSWORD_SIZE]; // Cleaned passowrd in char[] form
} CredentialsData;

/**
 * @brief Create a login window ui object that denpends on credential service
 * 
 * @param credential_service `CredentialService` instance
 */
LoginWindowUI* create_login_window_ui(CredentialService *credential_service);

/**
 * @brief Destroys the LoginWindowUI->window by calling `gtk_widget_destroy()`
 * frees the memory allocated to login_window_ui
 * 
 * @param login_window_ui 
 */
void destroy_login_window_ui(LoginWindowUI *login_window_ui);

/**
 * @brief Changes the gui label to show if credentials are valid or not
 * 
 * @param invalid_label
 * @param logged_in_flag
 */
void update_invalid_label(GtkWidget *invalid_label, int logged_in_flag);

/**
 * @brief Proxy for the check_credentials function in CredentialService
 * Calls `update_invalid_label()`
 * 
 * @param widget NULL
 * @param data Must be of type CredentialsData initiazlied with g_new()
 */
void check_login_credentials(GtkWidget *widget, gpointer data);

/**
 * @brief Get the clean string from an entry widget 
 * 
 * @param widget 
 * @param size Size of the expected string
 * @return char* 
 */
void get_clean_string(GtkWidget *widget, char *buffer, int size);

/**
 * @brief Get the name and password and load it into the CredentialsData
 * 
 * @param credentials_data 
 */
void get_name_and_password(CredentialsData* credentials_data);

/**
 * @brief Proxy to call `button_clicked()` and `button_clicked` from `CredentialService`
 * 
 * @param widget 
 * @param data `CredentialsData*`
 */
void login_in_user(GtkWidget *widget, gpointer data);

/**
 * @brief Proxy to call `button_clicked_register()` and `button_clicked_register2` from `CredentialService`
 * 
 * @param widget 
 * @param data `CredentialsData*`
 */
void register_user(GtkWidget *widget, gpointer data);

#endif