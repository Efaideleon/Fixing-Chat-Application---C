#ifndef CREDENTIAL_SERVICE_HEADER
#define CREDENTIAL_SERVICE_HEADER

#include <stdlib.h>
#include "../NetworkService/NetworkService.h"

// #include "gtk/gtk.h"

typedef struct
{
    char username[50];
    char name[50];
    char password[50];
    int LogInFlag;
    int signUpvalid;
    int SignUp;
    int RegFlag;
    int signInvalid;
    NetworkService *network_service;
} CredentialService;

/**
 * @brief
 * stores the name and username from data to credentialservice
 * @param credential_serivce
 */
void button_clicked(CredentialService *credential_serivce, char *name, char *username);

/**
 * @brief
 * Stores the password from data to CredentialService
 * and sets the LogInFlag to 1 so that the user can attempt to login
 * @param credential_service
 */
void button_clicked2(CredentialService *credential_service, char *password);

/**
 * @brief Void function for signin signup validation
 *
 * @param credential_service `CredentialService*`
 */
void check_credentials(CredentialService *credential_service);

void button_clicked_register();
void button_clicked_register2();

#endif