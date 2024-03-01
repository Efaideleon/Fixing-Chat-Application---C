#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <netdb.h>
// #include <gtk/gtk.h>
#include <assert.h>
#include "TestClient.h"

#define BUFFSIZE 512

/*** global variables ****************************************************/

const char *Program = NULL;
struct sockaddr_in ServerAddress;
int Shutdown = 0;

void FatalError(const char *ErrorMsg)
{
	//	fputs(Program, stderr);
	fputs(": ", stderr);
	perror(ErrorMsg);
	//	fputs(Program, stderr);
	fputs(": Exiting!\n", stderr);
	exit(20);
}
char *Answer;
void PingServer(const char *Message, char *RecvBuf, int SocketFD)
{
	int n;

	n = write(SocketFD, Message, strlen(Message));
	if (n < 0)
	{
		FatalError("writing to socket failed");
	}
#ifdef DEBUG
	printf("Waiting for response...\n");
#endif
	n = read(SocketFD, RecvBuf, BUFFSIZE - 1);
	if (n < 0)
	{
		FatalError("reading from socket failed");
	}
	RecvBuf[n] = 0;
#ifdef DEBUG
	printf("Received response: %s\n", RecvBuf);
//	printf("%s: Closing the connection...\n", Program);
#endif
	//	close(SocketFD);
	//	return(RecvBuf);
}

void ReturnFriendList(char *SendBuf, char *RecvBuf, int SocketFD)
{
	char *Message = "ReturnFriendList ";
	strcat(Message, SendBuf);
	PingServer(Message, RecvBuf, SocketFD);
}

int SignUp(char *SendBuf, char *RecvBuf, int SocketFD)
{
	int valid = 0;
	printf("inside SignUp function\n");
	char TempBuf[256];
	strcpy(TempBuf, "SignUp ");
	strcat(TempBuf, SendBuf);
	printf("%s\n", TempBuf);
	PingServer(TempBuf, RecvBuf, SocketFD);
	printf("%s\n", RecvBuf);
	if (strcmp(RecvBuf, "failed") == 0)
	{
		valid = FALSE;
	}
	else
	{
		valid = TRUE;
	}
	return valid;
}
char *FL = NULL;
int SignIn(char *SendBuf, char *RecvBuf, int SocketFD)
{
	int valid = 0;
	printf("SengBuf stage 1 is %s\n", SendBuf);
	char TempBuf[256];
	strcpy(TempBuf, "SignIn ");
	strcat(TempBuf, SendBuf);
	printf("%s\n", TempBuf);
	PingServer(TempBuf, RecvBuf, SocketFD);
	printf("%s\n", RecvBuf);
	int i = 0;
	char *Sep[11];
	char *list = strtok(RecvBuf, " ");
	while (i < 10)
	{
		Sep[i] = list;
		list = strtok(NULL, " ");
		if (Sep[i] == NULL)
		{
			break;
		}
		printf("Signin seperation is %s at %d\n", Sep[i], i);
		i++;
	}
	char *Op = Sep[0];
	i = 1;

	// FIX: new fix
	if (FL != NULL)
	{
		free(FL);
	}

	FL = malloc(30 * sizeof(char));
	FL[0] = '\0';
	while (Sep[i] != NULL)
	{
		strcat(FL, Sep[i]);
		strcat(FL, " ");
		i++;
	}
	printf("friendlist is this inside signin function in testclient %s\n", FL);
	if (strcmp(Op, "failed") == 0)
	{
		valid = FALSE;
	}
	else if (strcmp(Op, "success") == 0)
	{
		valid = TRUE;
	}
	return valid;
}

char *FriendList()
{
	printf("insdie friendlist fucntion\n");
	/*	char templist[BUFFSIZE];
				printf("insdie friendlist fucntion\n");
		templist = FL;
		printf("friendlist is this inside FriendList function in testclient %s\n", templist);
		if (FL!=NULL)
		{
			free(FL);
		}
		return templist;*/
	printf("friendlist is this inside FriendList function in testclient %s\n", FL);
	// FIX: new Fix
	char *friendListCopy = malloc(strlen(FL) + 1);
	strcpy(friendListCopy, FL);
	return friendListCopy;
}

void FreeFL()
{
	printf("FL is %s\n", FL);
	if (FL != NULL)
	{
		free(FL);
		// FIX: new Fix
		FL = NULL;
	}
}
void SendMessage(char *SendBuf, char *RecvBuf, int SocketFD)
{

	PingServer(SendBuf, RecvBuf, SocketFD);
}

char *RequestMessage(char *SendBUf, char *RecvBuf, int SocketFD)
{
	const char *Message = "request";
	PingServer(Message, RecvBuf, SocketFD);
	char *mess = NULL;
	strcpy(mess, RecvBuf);
	return mess;
}

void CloseClient(char *SendBuf, char *RecvBuf, int SocketFD)
{
	const char *Message = "Client has requested to shutdown.\n";
	PingServer(Message, RecvBuf, SocketFD);
}

void CloseServer(char *SendBuf, char *RecvBuf, int SocketFD)
{
	const char *Message = "server shutdown";
	PingServer(Message, RecvBuf, SocketFD);
}

// int main(int argc, char *argv[]) {
//	return 0;
// }
void CreateSocket(int argc, char *argv[], int *SocketFD, char *RecvBuf, char *SendBuf)
{
	int PortNo;
	struct hostent *Server;
	Program = argv[0];
#ifdef DEBUG
	printf("%s: Starting...\n", argv[0]);
#endif
	if (argc < 3)
	{
		fprintf(stderr, "Usage: %s hostname port\n", Program);
		exit(10);
	}
	Server = gethostbyname(argv[1]);
	if (Server == NULL)
	{
		fprintf(stderr, "%s: no such host named '%s'\n", Program, argv[1]);
		exit(10);
	}
	PortNo = atoi(argv[2]);
	if (PortNo <= 2000)
	{
		fprintf(stderr, "%s: invalid port number %d, should be >2000\n",
				Program, PortNo);
		exit(10);
	}
	ServerAddress.sin_family = AF_INET;
	ServerAddress.sin_port = htons(PortNo);
	ServerAddress.sin_addr = *(struct in_addr *)Server->h_addr_list[0];

	*SocketFD = socket(AF_INET, SOCK_STREAM, 0);
	if (*SocketFD < 0)
	{
		FatalError("socket creation failed");
	}

#ifdef DEBUG
	printf("%s: Connecting to the server at port %d...\n",
		   Program, ntohs(ServerAddress.sin_port));
#endif
	if (connect(*SocketFD, (struct sockaddr *)&ServerAddress,
				sizeof(struct sockaddr_in)) < 0)
	{
		FatalError("connecting to server failed");
	}
#ifdef DEBUG
	printf("socket creation completed inside testclient\n");
#endif
}

/*
********** Client Loop **********
	do {
		printf("%s: enter a message to send to the server,\n"
			"         or 'bye' to quit this client,\n"
			"         or 'shutdown' to quit both server and client,\n"
			"	  or 'SignUp' to sign up a new user,\n"
			"	  or 'SignIn' if you already have an account and wish to sign in,\n"
			"message: ", argv[0]);
		fgets(SendBuf, sizeof(SendBuf), stdin);

		l = strlen(SendBuf);
		if (SendBuf[l - 1] == '\n')
		{
			SendBuf[--l] = 0;
		}
		if (strcmp ("SignUp", SendBuf) == 0)
		{
			PingServer (SendBuf, RecvBuf, SocketFD);
		}
		else if (strcmp("bye", SendBuf) == 0) {
			CloseClient(SendBuf, RecvBuf, SocketFD);
			Shutdown = 1;
		}
		else if (strcmp("shutdown", SendBuf) == 0) {
			CloseServer(SendBuf, RecvBuf, SocketFD);
			Shutdown = 0;
		}
		else {
			SendMessage(SendBuf, RecvBuf, SocketFD);
		}

	} while (Shutdown == 0);
`	printf("%s: Exiting...\n", argv[0]);
	close(SocketFD);
	return 0;
}*/
