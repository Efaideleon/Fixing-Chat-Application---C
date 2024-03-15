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
    int logged_in;
    NetworkService *network_service;
} CredentialService;


/**
 * @brief Sets name, username and password in CredentialService and set RegFlag to 1
 * 
 * @param credential_service 
 * @param name 
 * @param password 
 */
void sign_up(CredentialService *credential_service, char* name, char *password);

/**
 * @brief Sets name, username, and passsword in CredentialService and sets LogInFlag to 1
 * 
 * @param credential_service 
 * @param name 
 * @param username 
 * @param password 
 */
void login(CredentialService *credential_service, char *name, char *username, char *password);

/**
 * @brief Set the password attribute in CredentialService
 * 
 * @param credential_service 
 * @param password 
 */
void set_password(CredentialService *credential_service, char *password);

/**
 * @brief Set the username attribute in CredentialService 
 * 
 * @param credential_service 
 * @param username 
 */
void set_username(CredentialService *credential_service, char *username);

/**
 * @brief Set the name attribute in CredentialService 
 * 
 * @param credential_service 
 * @param name 
 */
void set_name(CredentialService* credential_service, char *name);

/**
 * @brief return 1 if the credentials are valid, 0 for invalid
 * 
 * @param credential_service 
 * @return int 
 */
int check_credentials(CredentialService *credential_service);

/**
 * @brief Create a credential service object with malloc()
 * 
 * @param network_service 
 * @return CredentialService* 
 */
CredentialService* create_credential_service(NetworkService *network_service);

/**
 * @brief free memory allocated to credential_service
 * 
 * @param credential_service 
 */
void destroy_credential_service(CredentialService *credential_service);

#endif