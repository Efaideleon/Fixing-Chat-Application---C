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

// void check_credentials(GtkWidget *widget, gpointer data)
// {
//     CredentialsData *credentials_data = (CredentialsData *)data;
// 	if (credentials_data->credential_service->RegFlag != 0 && credentials_data->credential_service->name != NULL)
// 	{

// 		credentials_data->credential_service->signUpvalid = SignUp(credentials_data->credential_service->name, credentials_data->credential_service->network_service->RecvBuf,credentials_data->credential_service->network_service->SocketFD);
// 		credentials_data->credential_service->RegFlag = 0;
// 		if ( signUpvalid == TRUE)
// 		{
// 			signInvalid = TRUE;
// 			update_invalid_label();
// 		}
// 		else if (signInvalid == FALSE)
// 		{
// 			signInvalid = FALSE;
// 			update_invalid_label();
// 		}
// 	}
// 	if (LogInFlag != 0 && name != NULL)
// 	{
// 		signInvalid = SignIn(name, RecvBuf, SocketFD);
// 		fl = malloc(30 * sizeof(char));
// 		fl[0] = '\0';
// 		strcat(fl, FriendList());
// 		if (fl != NULL)
// 		{
// 			printf("fl is %s\n", fl);
// 		}
// 		LogInFlag = 0;
// 		if (signInvalid == TRUE)
// 		{
// 			signUpvalid = TRUE;
// 			update_invalid_label();
// 		}
// 		else if (signInvalid == FALSE)
// 		{
// 			signUpvalid = FALSE;
// 			update_invalid_label();
// 		}
//     }
// }