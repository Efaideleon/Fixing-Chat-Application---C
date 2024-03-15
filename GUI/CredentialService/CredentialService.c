#include "CredentialService.h"

void set_name(CredentialService* credential_service, char *name)
{
    if (credential_service == NULL || name == NULL) {
        fprintf(stderr, "Invalid pointer provided to set_name function.\n");
        return;
    }

    name[NAME_SIZE - 1] = '\0';
    strncpy(credential_service->name, name, NAME_SIZE - 1);
    credential_service->name[NAME_SIZE - 1] = '\0';
}

void set_username(CredentialService *credential_service, char *username)
{
    if (credential_service == NULL || username == NULL) {
        fprintf(stderr, "Invalid pointer provided to set_username function.\n");
        return;
    }

    username[NAME_SIZE - 1] = '\0';
    strncpy(credential_service->username, username, NAME_SIZE - 1);
    credential_service->username[NAME_SIZE - 1] = '\0';
}

void set_password(CredentialService *credential_service, char *password)
{
    if (credential_service == NULL || password == NULL) 
    {
        fprintf(stderr, "Invalid pointer provided to get_password function.\n");
        return;
    }

    password[PASSWORD_SIZE - 1] = '\0';

    strncpy(credential_service->password, password, PASSWORD_SIZE - 1);
    credential_service->password[PASSWORD_SIZE - 1] = '\0';

    strcat(credential_service->name, " ");
    strcat(credential_service->name, credential_service->password);
}

void login(CredentialService *credential_service, char *name, char *username, char *password)
{
    set_name(credential_service, name);
    set_username(credential_service, username);
    set_password(credential_service, password);
    credential_service->LogInFlag = 1;
}

void sign_up(CredentialService *credential_service, char* name, char *password)
{
    set_name(credential_service, name);
    set_password(credential_service, password);
    credential_service->RegFlag = 1;
}

int check_credentials(CredentialService *credential_service)
{

    int *sign_up_valid = &credential_service->signUpvalid;
    int *sign_in_valid = &credential_service->signInvalid;
    char *name = credential_service->name;
    int *reg_flag = &credential_service->RegFlag;
    int *log_in_flag = &credential_service->LogInFlag;
    NetworkService *network_service = credential_service->network_service;

    if (*reg_flag != 0 && name != NULL)
    {
        *sign_up_valid = SignUp(name, network_service->RecvBuf, network_service->SocketFD);
        *reg_flag = 0;
        if (*sign_up_valid == TRUE)
        {
            *sign_in_valid = TRUE;
            return TRUE;
        }
        else if (*sign_in_valid == FALSE)
        {
            *sign_in_valid = FALSE;
            return FALSE;
        }
    }
    if (*log_in_flag != 0 && name != NULL)
    {
        *sign_in_valid = SignIn(name, network_service->RecvBuf, network_service->SocketFD);

        /* BUG: This code will be called when the user is able to login and the friend list is created
         *       Ideally by the window manager
         */
        // fl = malloc(30 * sizeof(char));
        // fl[0] = '\0';
        // strcat(fl, FriendList());
        // if (fl != NULL)
        // {
        //     printf("fl is %s\n", fl);
        // }
        *log_in_flag = 0;

        if (*sign_in_valid == TRUE)
        {
            *sign_up_valid = TRUE;
            credential_service->logged_in = 1;
            return TRUE;
        }
        else if (*sign_in_valid == FALSE)
        {
            *sign_up_valid = FALSE;
            credential_service->logged_in = 0;
            return FALSE;
        }
    }

    return FALSE;
}

CredentialService *create_credential_service(NetworkService *network_service)
{
    CredentialService *credential_service = (CredentialService*)malloc(sizeof(CredentialService));
    credential_service->LogInFlag = 0;
    credential_service->RegFlag = 0;
    credential_service->signInvalid = 0;
    credential_service->SignUp = 0;
    credential_service->signUpvalid = 0;
    credential_service->logged_in = 0;
    credential_service->network_service = network_service;
    return credential_service;
}

void destroy_credential_service(CredentialService *credential_service)
{
    free(credential_service);
}
