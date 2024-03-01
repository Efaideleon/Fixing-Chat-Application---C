#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <assert.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <gtk/gtk.h> 
#include <time.h>
#include <math.h>
#include "user.h"
#include <stdint.h>
#include "send.h"
int MakeServerSocket(uint16_t PortNo);

void FatalError(const char *ErrorMsg);

void ProcessRequest(int DataSocketFD, fd_set ReadFDs, RUNLIST *list);

