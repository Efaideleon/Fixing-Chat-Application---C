#include "../NetworkService/NetworkService.h"
#include "../LoginWindowUI/LoginWindowUI.h"
#include "../CredentialService/CredentialService.h"
#include <stdio.h>
// #include "../../TestClient.h"

int main(int argc, char *argv[])
{
    gtk_init(&argc, &argv);
    NetworkService network_service;
    CredentialService credential_service;
    LoginWindowUI login_window_ui;
    create_login_window_ui(&login_window_ui, &credential_service);
    // CreateSocket(argc, argv, &network_service->SocketFD, network_service->SendBuf, network_service->RecvBuf);

    gtk_widget_show_all(login_window_ui.window);
    while (1)
    {
        while (gtk_events_pending())
        {
            gtk_main_iteration();
        }
    }
    return 0;
}