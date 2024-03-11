# include "CredentialService.h"

void button_clicked(GtkWidget *widget, gpointer data)
{
    CredentialsData *credentials_data= (CredentialsData*) data;

    GtkWidget* temp_data = gtk_label_new("");
	gtk_label_set_text(GTK_LABEL(temp_data), gtk_entry_get_text(GTK_ENTRY(credentials_data->data)));

	strncpy(credentials_data->credential_service->name, gtk_label_get_text(GTK_LABEL(temp_data)), sizeof(credentials_data->credential_service->name));
	strncpy(credentials_data->credential_service->username, gtk_label_get_text(GTK_LABEL(temp_data)), sizeof(credentials_data->credential_service->username));
}