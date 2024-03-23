#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <netdb.h>

#include <assert.h>
#include "user.h"


//const char *Program = NULL;
struct sockaddr_in ServerAddress;
//int Shutdown = 0;

void FatalError(const char *ErrorMsg);

int SignIn(char *SendBuf, char *RecvBuf, int SocketFD);

int SignUp(char *SendBuf, char *RecvBuf, int SocketFD);

char *FriendList();

void PingServer(const char *Message, char *RecvBuf, int SocketFD);

void SendMessage (char *SendBuf, char *RecvBuf, int SocketFD);

void CloseClient(char *SendBuf, char *RecvBuf, int SocketFD);
	
void CloseServer(char *SendBuf, char *RecvBuf, int SocketFD);

void CreateSocket(int argc, char *argv[], int *SocketFD, char *RecvBuf, char *SendBuf);

void get_friend_list(char *SendBuf, char *RecvBuf, int SocketFD);