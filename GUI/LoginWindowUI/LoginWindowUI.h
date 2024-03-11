#ifndef LOGIN_WINDOW_UI_HEADER
#define LOGIN_WINDOW_UI_HEADER

#include <stdlib.h>
#include "gtk/gtk.h"
#include "../CredentialService/CredentialService.h"
typedef struct
{
    GtkWidget *window;
    GtkWidget *vbox;
    GtkWidget *label;
    GtkWidget *label2;
    GtkWidget *label3;
    GtkWidget *button;
    GtkWidget *button2;
    GtkWidget *button3;
    GtkWidget *hbutton_box;
    GtkWidget *hpaned;
    GtkEntryBuffer *buffer;
    GtkEntryBuffer *buffer2;
    GtkWidget *table;
    GtkWidget *invalid_label;
    GtkWidget *entry;
    GtkWidget *entry2;

} LoginWindowUI;

/**
 * @brief Create a login window ui object
 *
 * @return LoginWindowUI
 */
void create_login_window_ui(LoginWindowUI *login_window_ui, CredentialService *credential_service);
void update_invalid_label();

#endif