#include "CredentialService.h"

void button_clicked(CredentialService *credential_service, char *name, char *username)
{
    strncpy(credential_service->name, name, sizeof(credential_service->name));
    strncpy(credential_service->username, username, sizeof(username));
}

void button_clicked2(CredentialService *credential_service, char *password)
{
    strncpy(credential_service->password, password, sizeof(credential_service->password));
    strcat(credential_service->name, " ");
    strcat(credential_service->name, credential_service->password);

    credential_service->LogInFlag = 1;
}

int check_credentials(CredentialService *credential_service)
{

    int *sign_up_valid = &credential_service->signUpvalid;
    int *sign_in_valid = &credential_service->signInvalid;
    char *name = &credential_service->name;
    int *reg_flag = &credential_service->RegFlag;
    int *log_in_flag = &credential_service->LogInFlag;
    NetworkService *network_service = &credential_service->network_service;

    if (*reg_flag != 0 && *name != NULL)
    {
        *sign_up_valid = SignUp(*name, network_service->RecvBuf, network_service->SocketFD);
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
    if (*log_in_flag != 0 && *name != NULL)
    {
        *sign_in_valid = SignIn(*name, network_service->RecvBuf, network_service->SocketFD);

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
            return TRUE;
        }
        else if (*sign_in_valid == FALSE)
        {
            *sign_up_valid = FALSE;
            return FALSE;
        }
    }
}
