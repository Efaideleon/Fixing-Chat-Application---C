#ifndef CREDENTIAL_SERVICE_HEADER
#define CREDENTIAL_SERVICE_HEADER

#include <stdlib.h>
#include "gtk/gtk.h"

typedef struct
{
    char username[50];
    char name[50];
    char *password;
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
 * Stores the name and username from data to CredentialService
 * @param widget 
 * @param data Must be of type CredentialsData
 */
void button_clicked(GtkWidget *widget, gpointer data);
void button_clicked2();
void check_credentials();
void button_clicked_register();
void button_clicked_register2();

#endif