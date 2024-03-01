#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "user.h"
#include "GlobalDefs.h"


USER *CreateReturnUser(char *username) {

	USER *user = (USER *)malloc(sizeof(USER));
	if (user == NULL) {
		return NULL;
	}

	user->username = GetNamePassFriend(reading_userInfo(username), 0);
	user->password = GetNamePassFriend(reading_userInfo(username), 1);
	user->friendlist = GetNamePassFriend(reading_userInfo(username), 2);

	return user;
}

void DeleteUser(USER *user) {

	assert(user);
	free(user);
	user->username = NULL;
	user->password = NULL;
	user->friendlist = NULL;

}

void writing_newuser(char *username, char *password) {

	FILE *outfile;
	outfile = fopen(username, "w");

	fprintf(outfile, "%s\n", username);
	fprintf(outfile, "%s\n", password);
	fprintf(outfile, "n0ne\n");
	fclose(outfile);
}

char *add_friend(USER *user, char *friend) {
#ifdef DEBUG
	printf("ADDING FRIEND INTO FRIEND LIST FUNC: =====\n");
#endif
	if(strcmp(user->friendlist,"n0ne") == 0){
		strcpy(user->friendlist,friend);
		strcat(user->friendlist," ");
		printf("%s\n", user->friendlist);
	}
	else{
		strcat(user->friendlist, friend);
		strcat(user->friendlist," ");
	}
	
	return user->friendlist;
}

//Creates new UserList file
void create_userlist(void) {
	if (access("UserList", F_OK) != -1) {
#ifdef DEBUG
		printf("CreateUserList: file exists\n");
#endif
	}
	
	else{
		FILE *outfile;
		printf("CreateUserList: file exists");
        outfile = fopen("UserList", "w");
		fclose(outfile);
#ifdef DEBUG
		printf("CreateUserList: File Doesn't Exist, Successfully Created File\n");
#endif
	}
}

void writing_userList(char *username){

	FILE *outfile;
	outfile = fopen("UserList", "a");
	fprintf(outfile, "%s\n", username);
	
	fclose(outfile);
}

void writing_userInfo(USER *user){
	
	FILE *outfile;
	outfile = fopen(user->username, "w");
	fprintf(outfile, "%s\n", user->username);
	fprintf(outfile, "%s\n", user->password);
	fprintf(outfile, "%s\n", user->friendlist);

	fclose(outfile);
}

char *reading_userlist(){
	
	printf("reading now \n");

	FILE *outfile;
	int length = 0;
	outfile = fopen("UserList", "r");	

	if (!outfile){
		printf("Cannot open file!\n");
		exit(10);
	}

	char ch;	
	while((ch = fgetc(outfile)) != EOF){
        	length++;
        }

	printf("\n checking length %d\n", length);
	char *userlist = malloc(length*sizeof(char));
	rewind(outfile);
	int i=0;
        while ((ch = fgetc(outfile)) != EOF){
  		userlist[i] = ch;
                i++;            
        }
	userlist[i] = '\0';
#ifdef DEBUG
      printf("checking if appending: %s", userlist);          
#endif	

	fclose(outfile);
	return userlist;
}

//reads userinfo and puts into an array length of 3
//for username, password, and friendlists
char *reading_userInfo(char *username){

	FILE *outfile;
	char ch;
	int length, i;
	outfile = fopen(username, "r");	

	if (!outfile){
		printf("Cannot open file!\n");
                exit(10);
	}
	
	while((ch = fgetc(outfile)) != EOF){
		length++;
	}

	rewind(outfile);
	char *Info = malloc(length*sizeof(char));	
	Info[0] = '\0';
	while ((ch = fgetc(outfile)) != EOF){
 		Info[i] = ch;
                i++;               
        }

#ifndef DEBUG
      printf("checking if appending: %s", Info);
#endif

	fclose(outfile);
	return Info;
}

// returns string of username, password, or friendlist
char *GetNamePassFriend(char *userInfo, int x){

	char *Info[3] = {'\0', '\0', '\0'};
	int i=0;
	int l = strlen(userInfo);
	char *split = malloc(l*sizeof(char));
 	split[0] = '\0';
	strcpy(split,userInfo);
	char *token = strtok(split,"\n");
#ifdef DEBUG
        printf("THE USER INFO IS: %s\n", userInfo);
#endif
	while (token != NULL){
		Info[i] = token;
#ifdef DEBUG
		printf("check if GetNamePassFriend: %s\n", Info[i]);
#endif		
		token= strtok(NULL, "\n");
		i++;
		Info[i] ='\0';
	}
	
	FILE *outfile;
	outfile = fopen(Info[0], "w");
	
	fprintf(outfile, "%s\n", Info[0]);
        fprintf(outfile, "%s\n", Info[1]);
        fprintf(outfile, "%s\n", Info[2]);

	if (x == 0){
		strcpy(userInfo,Info[0]);
	}
	else if (x==1){
		strcpy(userInfo,Info[1]);
	}
	else if (x==2){
		strcpy(userInfo,Info[2]);
	}

        fclose(outfile);
	free(split);
	return userInfo;
}


int FriendExists(USER *user, char *friend){

	char *existingName = strstr(user->friendlist, friend);
#ifdef DEBUG
	printf("FriendExists: the found friend name is: %s \n", existingName);
#endif 
	//returns true if anem exist
	//retusn false if it doesnt exist
	if (existingName != NULL){
                return TRUE;
        }
        else{
                return FALSE;
        }

}

int UsernameExists(char *username, char *userlist){
	 
	char *existingName = strstr(userlist,username);

	//returns true if name exist
	//returns false if it doesn't exist	
	if (existingName != NULL){
		return TRUE;
	}
	else{
		return FALSE;
	}

}

//creates new account
void CreateNewAcc(char *username, char *password){
	

	//USER *user;
	//user = CreateNewUser(username, password);
	writing_userList(username);
	writing_newuser(username, password);	
}

//check if the username/password exists, so that user can login
//return TRUE to enable login
//return FALSE for wrong username or password
int AbleLogin(char *username, char *password){
#ifdef DEBUG
	printf("LOGIN: AbleLogin is being called.\n");
#endif
	int login;
	char *userInfo, *passInfo;
	char *userList = reading_userlist();
	if (UsernameExists(username, userList) == TRUE){
		userInfo = reading_userInfo(username);
		passInfo = GetNamePassFriend(userInfo, 1);
		printf("password is %s\n", passInfo);
		if (strcmp(password,passInfo)==0){
			login = TRUE;	
		}		
		else{
			login = FALSE;	
		}
		free(userInfo);

	}
	else{
		login = FALSE;
	}
	free(userList);
#ifdef DEBUG
	printf("LOGIN: Free is successful");
#endif
	return login;
}


