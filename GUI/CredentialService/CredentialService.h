#ifndef CREDENTIAL_SERVICE_HEADER
#define CREDENTIAL_SERVICE_HEADER

#include <stdlib.h>
#include "../NetworkService/NetworkService.h"
#include "../../TestClient.h"

#define NAME_SIZE 50 // Size for char name/username array
#define PASSWORD_SIZE 50 // Size for char password array
typedef struct
{
    char username[NAME_SIZE];
    char name[NAME_SIZE];
    char password[PASSWORD_SIZE];
    int LogInFlag;
    int signUpvalid;
    int SignUp;
    int RegFlag;
    int signInvalid;
    NetworkService *network_service;
} CredentialService;

/**
 * @brief stores the name and username from data to credentialservice
 * 
 * @param credential_serivce
 */
void button_clicked(CredentialService *credential_serivce, char *name, char *username);

/**
 * @brief Stores the password from data to CredentialService
 * and sets the LogInFlag to 1 so that the user can attempt to login
 * 
 * @param credential_service
 */
void button_clicked2(CredentialService *credential_service, char *password);

/**
 * @brief Void function for signin signup validation
 *
 * @param credential_service `CredentialService*`
 */
int check_credentials(CredentialService *credential_service);

/**
 * @brief Stores the name from the entry box to the credential_service instance
 * 
 * @param credential_service 
 * @param name name to be stored
 */
void button_clicked_register(CredentialService *credential_service, char *name);

/**
 * @brief  Stores the password from the entry box to the credential_service instace
 * 
 * @param credential_service
 * @param password password to be stored
 */
void button_clicked_register2(CredentialService *credential_service, char *password);

/**
 * @brief Create a credential service object
 * 
 * @param credential_service 
 * @param network_service 
 */
void create_credential_service(CredentialService *credential_service, NetworkService *network_service);

#endif