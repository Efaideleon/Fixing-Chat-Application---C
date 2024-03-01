#ifndef SEND_H
#define SEND_H

#include "user.h"
#include "GlobalDefs.h"

//typedef struct RunUser RUNUSER;
typedef struct RunList RUNLIST;
typedef struct RunEntry RUNENTRY;
typedef struct MessageList MSGLIST;
typedef struct MessageEntry MSGENTRY;

struct RunList {
	int length;
	RUNENTRY *first;
	RUNENTRY *last;
};

struct RunEntry {
	RUNLIST *list;
	RUNENTRY *prev;
	RUNENTRY *next;
	USER *user;
	int socketID;
	MSGLIST *msglist;
};

struct MessageList{
	int length;
	MSGENTRY *first;
	MSGENTRY *last;
};

struct MessageEntry{
	MSGLIST *list;
	int socketID;
	char *message;
	MSGENTRY *prev;
	MSGENTRY *next;
};

RUNENTRY *CreateRunEntry(USER *user, int socketID);

RUNLIST *CreateRunList(void);

void DeleteRunEntry(RUNENTRY *entry);

void DeleteRunList(RUNLIST *list);

void RemoveRunUser(RUNLIST *list, RUNENTRY *findclient);

void AppendRunEntry(RUNENTRY *client, RUNLIST *list);


//MSGLIST and MSGENTRY functions
MSGLIST *CreateMsgList(void);

MSGENTRY *CreateMsgEntry(int socketID, char *message);

void DeleteMsgList(MSGLIST *list);

void DeleteMsgEntry(MSGENTRY *entry);

void AppendMsgEntry(int senderID, MSGLIST *list, char *message);

//Send and Recieve Helper Functions
int SendToMessage(char *RecvBuf);

int WriteIntendedUser(char *RecvBuf, RUNLIST *list);

int WriteIntendedFriend(int DataSocketFD, char *RecvBuf, RUNLIST *list);

void SendingMessages(char *RecvBuf, RUNLIST *list, int senderID);

char *find_sender(int socketID, RUNLIST *list);

void RetrieveMessages(int DataSocketFD, char *SendBuf, RUNLIST *list); 

int CheckSendFriend(char *Recvbuf);

void SendFriendRequest(char *RecvBuf, RUNLIST *list, int senderID);

//int YesorNoRequest(int DataSocketFD, char *SendBuf, RUNLIST *list);

//int FriendRequestExists(int DataSocketFD, char *SendBuf, RUNLIST *list);

void AcceptFriendRequest(int DataSocketFD, char *RecvBuf, RUNLIST *list);

void DeclineFriendRequest(int DataSocketFD, char *RecvBuf, RUNLIST *list);

void LoggingOut(int DataSocketFD, RUNLIST *list);

int checkRemoveRequest(char *RecvBuf);

void removeFriend(USER *user, char *friendname);

void RemoveFriendRequest(int DataSocketFD, char *Recvbuf, RUNLIST *list);
#endif

