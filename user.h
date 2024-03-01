#ifndef USER_H
#define USER_H

#include "GlobalDefs.h"

typedef struct user USER;

struct user{
	char *username;
	char *password;
	char *friendlist;
};

USER *CreateReturnUser(char *username);

void DeleteUser(USER *user);

void writing_newuser(char *username, char *password);

char *add_friend(USER *user, char *friend);

void create_userlist(void);

void writing_userList(char *username);

void writing_userInfo(USER *user);

char *reading_userlist();

char *reading_userInfo(char *username);

char *GetNamePassFriend(char *userInfo, int x);

char *remove_friend(USER *user, char *friend);

int FriendExists(USER *user, char *friend);

int UsernameExists(char *username, char *userlist);

void CreateNewAcc(char *username, char *password);

int AbleLogin(char *username, char *password);

#endif
