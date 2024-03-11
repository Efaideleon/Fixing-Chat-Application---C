#include "CredentialService.h"

void button_clicked(GtkWidget *widget, gpointer data)
{
    CredentialsData *credentials_data = (CredentialsData *)data;

    GtkWidget *temp_data = gtk_label_new("");
    gtk_label_set_text(GTK_LABEL(temp_data), gtk_entry_get_text(GTK_ENTRY(credentials_data->data)));

    strncpy(credentials_data->credential_service->name, gtk_label_get_text(GTK_LABEL(temp_data)), sizeof(credentials_data->credential_service->name));
    strncpy(credentials_data->credential_service->username, gtk_label_get_text(GTK_LABEL(temp_data)), sizeof(credentials_data->credential_service->username));
}

void button_clicked2(GtkWidget *widget, gpointer data)
{
    CredentialsData *credentials_data = (CredentialsData *)data;

    GtkWidget *temp_data = gtk_label_new("");
    gtk_label_set_text(GTK_LABEL(temp_data), gtk_entry_get_text(GTK_ENTRY(credentials_data->data)));

    strncpy(credentials_data->credential_service->password, gtk_label_get_text(GTK_LABEL(temp_data)), sizeof(credentials_data->credential_service->password));
    strcat(credentials_data->credential_service->name, " ");
    strcat(credentials_data->credential_service->name,credentials_data->credential_service->password);

    credentials_data->credential_service->LogInFlag = 1;
}

void check_credentials(void)
{
	if (RegFlag != 0 && name != NULL)
	{

		signUpvalid = SignUp(name, RecvBuf, SocketFD);
		RegFlag = 0;
		if (signUpvalid == TRUE)
		{
			signInvalid = TRUE;
			update_invalid_label();
		}
		else if (signInvalid == FALSE)
		{
			signInvalid = FALSE;
			update_invalid_label();
		}
	}
	if (LogInFlag != 0 && name != NULL)
	{
		signInvalid = SignIn(name, RecvBuf, SocketFD);
		fl = malloc(30 * sizeof(char));
		fl[0] = '\0';
		strcat(fl, FriendList());
		if (fl != NULL)
		{
			printf("fl is %s\n", fl);
		}
		LogInFlag = 0;
		if (signInvalid == TRUE)
		{
			signUpvalid = TRUE;
			update_invalid_label();
		}
		else if (signInvalid == FALSE)
		{
			signUpvalid = FALSE;
			update_invalid_label();
		}
}