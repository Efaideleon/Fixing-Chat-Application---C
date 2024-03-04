#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "send.h"

// RUNENTRY AND RUNLIST STUFF
RUNENTRY *CreateRunEntry(USER *user, int socketID)
{

	RUNENTRY *entry = malloc(sizeof(RUNENTRY));

	if (!entry)
	{
		perror("Out of memory! Aborting ...");
		exit(10);
	}

	entry->list = NULL;
	entry->next = NULL;
	entry->prev = NULL;
	entry->user = user;
	entry->socketID = socketID;
	entry->msglist = CreateMsgList();

	return entry;
}

RUNLIST *CreateRunList(void)
{

	RUNLIST *list = malloc(sizeof(RUNLIST));

	if (!list)
	{
		perror("Out of memory! Aborting ...");
		exit(10);
	}

	list->length = 0;
	list->first = NULL;
	list->last = NULL;

	return list;
}

void DeleteRunList(RUNLIST *list)
{
	assert(list);
	RUNENTRY *e, *n;

	e = list->first;
	while (e)
	{
		n = e->next;
		DeleteRunEntry(e);
		e = n;
	}

	free(list);
}

void DeleteRunEntry(RUNENTRY *entry)
{

	assert(entry->user);
	assert(entry);
	DeleteUser(entry->user);
	DeleteMsgList(entry->msglist);
	free(entry);
}

void RemoveRunUser(RUNLIST *list, RUNENTRY *findclient)
{

	assert(findclient);
	assert(list);
	RUNENTRY *e, *n, *p;
	e = list->first;
	while (e)
	{
		n = e->next;
		p = e->prev;
		if (e->socketID == findclient->socketID)
		{
			DeleteRunEntry(e);

			if (e == list->first)
			{
				n->prev = NULL;
				list->first = n;
			}
			else if (e == list->last)
			{
				p->next = NULL;
				list->last = p;
			}
			else
			{
				p->next = n;
				n->prev = p;
			}
		}
		e = n;
		list->length--;
	}
}

void AppendRunEntry(RUNENTRY *client, RUNLIST *list)
{
#ifdef DEBUG
	printf("FUNC: AppendRunEntry() is called.\n");
#endif
	assert(client);
	assert(list);

	RUNENTRY *entry = client;
	if (!entry)
	{
		perror("Out of memory! Aborting ...");
		exit(10);
	}

	if (list->last)
	{
		entry->list = list;
		entry->next = NULL;
		entry->prev = list->last;
		list->last->next = entry;
		list->last = entry;
	}
	else
	{
		entry->list = list;
		entry->next = NULL;
		entry->prev = NULL;
		list->last = entry;
		list->first = entry;
	}
	list->length++;
}

// MSGENTRY AND MSGLIST stuff
MSGLIST *CreateMsgList(void)
{

	MSGLIST *list = malloc(sizeof(MSGLIST));
	if (!list)
	{
		perror("Out of memory! Aborting ...");
		exit(10);
	}

	list->length = 0;
	list->first = NULL;
	list->last = NULL;

	return list;
}

MSGENTRY *CreateMsgEntry(int socketID, char *message)
{

	MSGENTRY *entry = malloc(sizeof(MSGENTRY));

	if (!entry)
	{
		perror("Out of memory! Aborting ...");
		exit(10);
	}

	entry->list = NULL;
	entry->next = NULL;
	entry->prev = NULL;
	entry->socketID = socketID;
	entry->message = message;

	return entry;
}

void DeleteMsgList(MSGLIST *list)
{

	assert(list);
	MSGENTRY *e, *n;

	e = list->first;
	while (e)
	{
		n = e->next;
		DeleteMsgEntry(e);
		e = n;
	}

	free(list);
}

void DeleteMsgEntry(MSGENTRY *entry)
{

	assert(entry);
	free(entry->message);
	free(entry);
}

void AppendMsgEntry(int senderID, MSGLIST *list, char *message)
{

	MSGENTRY *entry = CreateMsgEntry(senderID, message);

	if (!entry)
	{
		perror("Out of memory! Aborting ...");
		exit(10);
	}

	if (list->last)
	{
		entry->list = list;
		entry->next = NULL;
		entry->prev = list->last;
		list->last->next = entry;
		list->last = entry;
	}
	else
	{
		entry->list = list;
		entry->next = NULL;
		entry->prev = NULL;
		list->last = entry;
		list->first = entry;
	}
	list->length++;
}

// Send and Receive Helper Functions
int SendToMessage(char *Recvbuf)
{
#ifdef DEBUG
	printf("FUNC: SendToMessage() is called.\n");
#endif
	char *temp = Recvbuf;
	char *check;

	check = strstr(temp, "sendto");

	if (check != NULL)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

int WriteIntendedUser(char *RecvBuf, RUNLIST *list)
{
#ifdef DEBUG
	printf("FUNC: WriteIntendedUser is called.\n");
#endif
	char *check;
	char *temp = RecvBuf;

#ifdef DEBUG
	printf("WRITEINTENDEDUSER: the string is:%s\n", temp);
#endif

	RUNENTRY *next, *findUser;
	findUser = list->first;
	while (findUser)
	{
		next = findUser->next;
		check = strstr(temp, findUser->user->username);
		if (check != NULL)
		{
#ifdef DEBUG
			printf("WRITEINTENDEDUSER: the user is %s\n\n", findUser->user->username);
#endif
			return 1;
		}
		findUser = next;
	}

	return 0;
}

int WriteIntendedFriend(int DataSocketFD, char *RecvBuf, RUNLIST *list)
{
#ifdef DEBUG
	printf("FUNC: WriteIntendedFriend is called.\n");
#endif
	char *check;
	int check2;
	char *temp = RecvBuf;
	int len = strlen(RecvBuf);
	char *temp2 = malloc(len * sizeof(char));
	temp2[0] = '\0';
	strcpy(temp2, RecvBuf);
	char *sender = find_sender(DataSocketFD, list);
	RUNENTRY *next, *findUser, *findSender, *nextFind;
	USER *user;
#ifdef DEBUG
	printf("WRITEINTENDEDFRIEND: the string is:%s\n", temp);
	printf("WRITEINTENDEDFRIEND: the sender name is %s\n", sender);
#endif
	findSender = list->first;
	while (findSender)
	{
		nextFind = findSender->next;
		if (strcmp(sender, findSender->user->username) == 0)
		{
			user = findSender->user;
			break;
		}
		findSender = nextFind;
	}
	char *token = strtok(temp2, " ");
	char *intendedUser;
	int i = 0;
	while (i < 2)
	{
		intendedUser = token;

		token = strtok(NULL, " ");
		i++;
	}
#ifdef DEBUG
	printf("testing: extract name from msg: %s\n", intendedUser);
#endif
	findUser = list->first;

	check2 = FriendExists(user, intendedUser);
	if (check2 == TRUE)
	{
		while (findUser)
		{
			next = findUser->next;
			check = strstr(temp, findUser->user->username);
			if (check != NULL)
			{
#ifdef DEBUG
				printf("WRITEINTENDEDUSER: the user is %s\n\n", findUser->user->username);
#endif
				free(temp2);
				return 1;
			}
			findUser = next;
		}
#ifdef DEBUG
		printf("RETURNING 2 FROM WRITEINTENDED FRIEND\n");
#endif
		free(temp2);
		return 2;
	}
	else
	{
		free(temp2);
		return 0;
	}
	free(temp2);
	return 2;
}

void SendingMessages(char *RecvBuf, RUNLIST *list, int senderID)
{
#ifdef DEBUG
	printf("FUNC: SendingMessages() is called.\n");
#endif
	char *token;
	char *temp = RecvBuf;
	int len = strlen(temp);
	char *temp2[len];
	char *msg;
	int i, r;
#ifdef DEBUG
	printf("SENDINGMESSAGE: the string in sending func is:%s\n", temp);
#endif
	token = strtok(temp, " ");
	i = 0;
	while (token != NULL)
	{
		temp2[i] = token;
#ifdef DEBUG
		printf("%s\n\n", temp2[i]);
#endif
		token = strtok(NULL, " ");
		i++;
	}
	msg = malloc(len * sizeof(char));
	msg[0] = '\0';
	r = 0;

	while (r < (i - 2))
	{
#ifdef DEBUG
		printf("SENDINGMESSAGE: entering strcat loop");
#endif
		strcat(msg, temp2[r + 2]);
		if ((r + 1) != (i - 2))
		{
			strcat(msg, " ");
		}
		r++;
	}

	RUNENTRY *next, *findUser = list->first;
	while (findUser)
	{
		next = findUser->next;
		if (strstr(temp2[1], findUser->user->username) != NULL)
		{
			AppendMsgEntry(senderID, findUser->msglist, msg);
#ifdef DEBUG
			printf("the user is %s\n\n", findUser->user->username);
			printf("\n The message added to user: %s\n", msg);
#endif
			break;
		}
		findUser = next;
	}
}

char *find_sender(int socketID, RUNLIST *list)
{

	RUNENTRY *e, *n;
	e = list->first;

	while (e)
	{
		n = e->next;
		if (socketID == e->socketID)
		{
#ifdef DEBUG
			printf("the username in find_sender func is: %s\n", e->user->username);
#endif
			return e->user->username;
		}
		e = n;
	}

	return NULL;
}

// Note from Justin: there may be some weird struct issues with accept/decline friend request
void RetrieveMessages(int DataSocketFD, char *SendBuf, RUNLIST *list)
{
#ifdef DEBUG
	printf("SEND.C : RetrieveMessages() is called.\n");
#endif
	char *entire_msg;
	MSGENTRY *entry, *next_entry;
	RUNENTRY *nextUser;
	RUNENTRY *findUser = list->first;

#ifdef DEBUG
	printf("SEND.C : RetrieveMessage: findUser is initialized to list->first.\n");
#endif
	while (findUser)
	{
		nextUser = findUser->next;
#ifdef DEBUG
		printf("SEND.C : RetrieveMessage: nextUser is assigned to find->next\n");
#endif
		if (DataSocketFD == findUser->socketID)
		{
			entry = findUser->msglist->first;
#ifdef DEBUG
			printf("SEND.C THE USER FOUND IS : %s\n", findUser->user->username);
#endif
			//		}
			if (entry != NULL)
			{
				next_entry = entry->next;

				if ((findUser->msglist->length != 0) && (strstr(findUser->msglist->first->message, "addto") == NULL))
				{
#ifdef DEBUG
					printf("MESSAGE REQUESTING\n");
					printf("the user is %s\n\n", findUser->user->username);
					printf("the message to the client is: %s\n", entry->message);
#endif
					entire_msg = entry->message;
					//					strcat(entire_msg, "%");
					//					strcat(entire_msg, find_sender(entry->socketID, list));
					strcpy(SendBuf, entire_msg);

#ifdef DEBUG
					printf("the entire mesage will be: %s\n", entire_msg);
#endif
					findUser->msglist->first = next_entry;
					if (next_entry)
					{
						next_entry->prev = NULL;
					}
					else
					{
						findUser->msglist->first = NULL;
						findUser->msglist->last = NULL;
					}
					DeleteMsgEntry(entry);
					findUser->msglist->length--;
				}
				else if ((findUser->msglist->length != 0) && (strstr(findUser->msglist->first->message, "addto") != NULL))
				{
#ifdef DEBUG
					printf("FRIEND REQUESTING\n");
					printf("the user is %s\n", findUser->user->username);
					printf("the message to the client is: %s\n", entry->message);
#endif
					//	entire_msg = entry->message;
					entire_msg = find_sender(entry->socketID, list);
#ifdef DEBUG
					printf("the entire mesage will be: %s\n", entire_msg);
#endif
					strcpy(SendBuf, entire_msg);

#ifdef DEBUG
					printf("the entire mesage will be: %s\n", entire_msg);
#endif
				}
			}
			else
			{
#ifdef DEBUG
				printf("No messages in the msglist\n");
#endif
				entire_msg = "No messages were sent to you\n";
				strcpy(SendBuf, entire_msg);
#ifdef DEBUG
				printf("strcpy was called\n");
#endif
			}
		}
		findUser = nextUser;
	}
}

// checks if the user wants to send friend request
int CheckSendFriend(char *Recvbuf)
{

	char *temp = Recvbuf;
	char *check;

	check = strstr(temp, "addto");

	if (check != NULL)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

void SendFriendRequest(char *RecvBuf, RUNLIST *list, int senderID)
{
#ifdef DEBUG
	printf("SEND.C : SENDFREINDREQUEST is being called\n");
#endif

	RUNENTRY *findUser, *nextUser;
	char *temp = RecvBuf;
	char *token, *msg;
	int i, r;
	int len = strlen(temp);
	char *temp2[len];

	token = strtok(temp, " ");
	i = 0;
	while (token != NULL)
	{
		temp2[i] = token;
#ifdef DEBUG
		printf("%s\n", temp2[i]);
#endif
		token = strtok(NULL, " ");
		i++;
	}

	msg = malloc(len * sizeof(char));
	msg[0] = '\0';
	r = 0;
	while (r < i)
	{
#ifdef DEBUG
		printf("SEND.C : SENDFRIENDREQUEST: entering strcat loop");
#endif
		strcat(msg, temp2[r]);
		strcat(msg, " ");
		r++;
	}

	findUser = list->first;
	while (findUser)
	{
		nextUser = findUser->next;
		if (strcmp(temp2[1], findUser->user->username) == 0)
		{
			AppendMsgEntry(senderID, findUser->msglist, msg);
#ifdef DEBUG
			printf("SEND.C : SENDFRIENDREQUEST: the user is %s\n", findUser->user->username);
			printf("SEND.C : SENDFRIENDREQUEST: The message added to user: %s\n", msg);
#endif
			break;
		}
		findUser = nextUser;
	}
}

void AcceptFriendRequest(int DataSocketFD, char *RecvBuf, RUNLIST *list)
{
#ifdef DEBUG
	printf("SEND.C : ACCEPTFRIENDREQUEST is being called.\n");
#endif
	RUNENTRY *findUser = NULL;
	RUNENTRY *nextUser = NULL;
	MSGENTRY *msgEntry = NULL;
	MSGENTRY *nextEntry = NULL;
	char *sender = NULL;
	int senderID = 0;

	findUser = list->first;
	while (findUser)
	{
		nextUser = findUser->next;
		if (DataSocketFD == findUser->socketID)
		{
			msgEntry = findUser->msglist->first;
		}
		if (msgEntry != NULL)
		{
			nextEntry = msgEntry->next;

			if ((strstr(msgEntry->message, "addto") != NULL))
			{
				senderID = msgEntry->socketID;
#ifdef DEBUG
				printf("sender ID is : %d\n", senderID);
#endif
				int len = strlen(find_sender(senderID, list));
				sender = malloc(len * sizeof(char));
				sender[0] = '\0';
				strcpy(sender, find_sender(senderID, list));

				findUser->user->friendlist = add_friend(findUser->user, sender);

#ifdef DEBUG
				printf("the user is: %s\n", findUser->user->username);
				printf("the friendlist is: %s\n", findUser->user->friendlist);
#endif

				writing_userInfo(findUser->user);

				findUser->msglist->first = nextEntry;
				if (nextEntry)
				{
#ifdef DEBUG
					printf("SEND.C : ACCEPTFRIENDREQUEST: if(nextEntry) ifstatement is true.\n");
#endif
					nextEntry->prev = NULL;
#ifdef DEBUG
					printf("SEND.C : ACCEPTFRIENDREQUEST: if(nextEntry) ifstatement finshed.\n");
#endif
				}
				else
				{
#ifdef DEBUG
					printf("SEND.C : ACCEPTFRIENDREQUEST: if(nextEntry) ifstatement is false.\n");
#endif
					findUser->msglist->first = NULL;
					findUser->msglist->last = NULL;
#ifdef DEBUG
					printf("SEND.C : ACCEPTFRIENDREQUEST: if(nextEntry) ifstatement false finished\n");
#endif
				}
				findUser->msglist->length--;
				DeleteMsgEntry(msgEntry);
#ifdef DEBUG
				printf("SEND.C : ACCEPTRIENDREQUEST: Deleted MsgEntry.\n");
#endif
				strcpy(sender, findUser->user->username);
			}
		}
		findUser = nextUser;
	}

#ifdef DEBUG
	printf("\nthe sender id is: %d\n", senderID);
#endif

	findUser = list->first;
#ifdef DEBUG
	printf("SEND.C : ACCEPTFRIENDREQUEST: while(findUser) is about to start\n");
#endif
	if (sender != NULL)
	{
		while (findUser)
		{
			nextUser = findUser->next;
			if (findUser->socketID == senderID)
			{
				findUser->user->friendlist = add_friend(findUser->user, sender);
#ifdef DEBUG
				printf("the user is: %s\n", findUser->user->username);
				printf("the friendlist is: %s\n", findUser->user->friendlist);
#endif
			}
			findUser = nextUser;
		}
	}
}

void DeclineFriendRequest(int DataSocketFD, char *RecvBuf, RUNLIST *list)
{
#ifdef DEBUG
	printf("SEND.C : DECLINEFRIENDREQUEST is being called. \n");
#endif
	RUNENTRY *findUser, *nextUser;
	MSGENTRY *msgEntry, *nextEntry;

	findUser = list->first;
#ifdef DEBUG
	printf("SEND.C : DECLINEFRIENDREQUEST: About to enter while loop.\n");
#endif
	while (findUser)
	{
		nextUser = findUser->next;
		if (DataSocketFD == findUser->socketID)
		{
			msgEntry = findUser->msglist->first;
		}
		if (msgEntry != NULL)
		{
			nextEntry = msgEntry->next;
			if ((strstr(msgEntry->message, "addto") != NULL))
			{

#ifdef DEBUG
				printf("SEND.C : DECLINEFRIENDREQUEST: Deleted MsgEntry.\n");
#endif
				if (nextEntry)
				{
					nextEntry->prev = NULL;
					findUser->msglist->first = nextEntry;
				}
				else
				{
					findUser->msglist->first = NULL;
					findUser->msglist->last = NULL;
				}
				findUser->msglist->length--;
				DeleteMsgEntry(msgEntry);
			}
		}
		findUser = nextUser;
	}
}

void RemoveFriendRequest(int DataSocketFD, char *Recvbuf, RUNLIST *list)
{
	RUNENTRY *findUser, *nextUser;
	findUser = list->first;
	int l = strlen(Recvbuf);

	char *temp2 = malloc(l * sizeof(char));
	temp2[0] = '\0';
	strcpy(temp2, Recvbuf);

	char *token = strtok(temp2, " ");
	char *intendedUser;
	token = strtok(NULL, " ");

	intendedUser = token;

#ifdef DEBUG
	printf("\nthe user that is removed will be: %s ", intendedUser);
#endif
	while (findUser)
	{
		nextUser = findUser->next;
		if (DataSocketFD == findUser->socketID)
		{
			removeFriend(findUser->user, intendedUser);
			writing_userInfo(findUser->user);
			break;
		}
	}
	free(temp2);
}

// helper method
void removeFriend(USER *user, char *friendname)
{
#ifdef DEBUG
	printf("ENTERING REMOVE FRIEND REQUEST ======= \n");
#endif
	char *token, *initialList, *finalList;
	int l = strlen(user->friendlist);

	initialList = malloc(l * sizeof(char));
	initialList[0] = '\0';
	finalList = malloc(l * sizeof(char));
	finalList[0] = '\0';

	strcpy(initialList, user->friendlist);

	token = strtok(initialList, " ");

#ifdef DEBUG
	printf("checking\n");
#endif

	while (token != NULL)
	{
		if (strcmp(friendname, token) != 0 && (finalList != NULL))
		{
#ifdef DEBUG
			printf("string catting to fina list\n");
#endif
			strcat(finalList, token);
			strcat(finalList, " ");
		}
		else if ((strcmp(friendname, token) != 0) && (finalList == NULL))
		{
#ifdef DEBUG
			printf("string copying to final list\n");
#endif
			strcpy(finalList, token);
			strcat(finalList, " ");
		}
		token = strtok(NULL, " ");
#ifdef DEBUG
		printf("\n%s\n", finalList);
#endif
	}
	strcpy(user->friendlist, finalList);
	free(finalList);
	free(initialList);
}

int checkRemoveRequest(char *RecvBuf)
{
#ifdef DEBUG
	printf("REMOVE REQUEST ======= \n");
#endif
	char *check;
	check = strstr(RecvBuf, "removefriend");
	if (check != NULL)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void LoggingOut(int DataSocketFD, RUNLIST *list)
{

	RUNENTRY *findUser, *nextUser;

	findUser = list->first;
	while (findUser)
	{
		nextUser = findUser->next;
		if (findUser->socketID == DataSocketFD)
		{

			findUser->user->password = GetNamePassFriend(reading_userInfo(findUser->user->username), 1);
#ifdef DEBUG
			printf("LOGGING OUT FUNCTION: THE PASSWORD IS: %s\n", findUser->user->password);
			printf("LOGGING OUT FUNCTION: THE FRIENDLIST IS: %s\n", findUser->user->friendlist);
#endif
			writing_userInfo(findUser->user);
			DeleteRunEntry(findUser);
		}
		findUser = nextUser;
	}
}
