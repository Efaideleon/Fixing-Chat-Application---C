#ifndef CREDENTIAL_SERVICE_HEADER
#define CREDENTIAL_SERVICE_HEADER

#include <stdlib.h>
#include "gtk/gtk.h"

typedef struct
{
    char username[50];
    char name[50];
    char password[50];
    int LogInFlag;
    int RefFlag;
    int signUpValid;
    int SignUp;
    int RegFlag;
} CredentialService;

typedef struct
{
    GtkWidget *data;
    CredentialService *credential_service;
} CredentialsData;

/**
 * @brief 
 * stores the name and username from data to credentialservice
 * @param widget Must be initialized with gtk_entry_new(); 
 * @param data Must be of type CredentialsData
 */
void button_clicked(GtkWidget *widget, gpointer data);

/**
 * @brief 
 * Stores the password from data to CredentialService
 * and sets the LogInFlag to 1 so that the user can attempt to login
 * @param widget Must be initialized with gtk_entry_new();
 * @param data Must be of type CredentialsData
 */
void button_clicked2(GtkWidget *widget, gpointer data);

/**
 * @brief Void function for signin signup validation
 * 
 */
void check_credentials(void);
void button_clicked_register();
void button_clicked_register2();

#endif