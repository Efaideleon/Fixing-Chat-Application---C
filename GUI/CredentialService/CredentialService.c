#include "CredentialService.h"

#define TRUE = 1; // BUG: This is supposed to be TRUE, Need to load globals
#define FALSE = 0;

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

void check_credentials(CredentialService *credential_service)
{
    if (credential_service->RegFlag != 0 && credential_service->name != NULL)
    {
        credential_service->signUpvalid = SignUp(credential_service->name,credential_service->network_service->RecvBuf, credential_service->network_service->SocketFD);
        credential_service->RegFlag = 0;

    }
    if ( credential_service->LogInFlag != 0 && credential_service->name != NULL)
    {
        credential_service->signInvalid = SignIn(credential_service->name, credential_service->network_service->RecvBuf,credential_service->network_service->SocketFD);

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
        credential_service->LogInFlag = 0;
    }
}