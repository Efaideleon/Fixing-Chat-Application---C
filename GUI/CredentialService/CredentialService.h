#ifndef CREDENTIAL_SERVICE_HEADER
#define CREDENTIAL_SERVICE_HEADER

#include <stdlib.h>
#include "gtk/gtk.h"

typedef struct
{
    char username;
    char *name;
    char *password;
    int LogInFlag;
    int RefFlag;
    int signUpValid;
    int SignUp;
    int RegFlag;
} CredentialService;

void button_clicked();
void button_clicked2();
void check_credentials();
void button_clicked_register();
void button_clicked_register2();

#endif