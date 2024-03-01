//Headers
#include <gtk/gtk.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "TestClient.h"
#include "GlobalDefs.h"
#include <sys/time.h>
//#include "user.h"
/*******************    MAIN PROGRAM    ******************************/
//Variables
//GTK Widget
// Creating a window functions
GtkWidget *Login_Window();
GtkWidget *Chat_Window();
GtkWidget *Add_Friend_Window();
GtkWidget *Remove_Friend_Window();
GtkWidget *invalid_label;
GtkWidget *Register_window, *login_window, *chat_window, *friend_list, *message[10];
GtkWidget *Friend_List(), *notebook;
GtkWidget *window_dialog;
//entries
GtkWidget *add_f_entry, *rm_f_entry;
GtkWidget *entry, *entry2;
// Pointers to windows
GtkWidget *Window = NULL;
GtkWidget *FriendWindow = NULL;
GtkWidget *ChatWindow = NULL;
GtkWidget *AddFriendWindow = NULL;
GtkWidget *RemoveFriendWindow = NULL;
GtkWidget *dialog =NULL;
//TextBuffer
GtkTextBuffer *message_buffer[10];
//global label
GtkWidget *friend_invalid_label;
//commands to connect with the server
char st[500];
char add_to[40];
//Function Prototypes
static void button_clicked2(GtkWidget *widget, gpointer data);
static void button_clicked(GtkWidget *widget, gpointer data);
static void button_clicked_register(GtkWidget *widget, gpointer data);
static void button_clicked_register2(GtkWidget *widget, gpointer data);
void CreateWindow();
void currenttime(void);
void UpdateWindow(void);
static void update_invalid_label();
static void check_credentials(void);
static void send_message(GtkWidget *widget, gpointer data);
static void request_message(void);
void accept_friend(void);
static void button_clicked_add(GtkWidget *widget, gpointer data);
static void open_dialog(void);
int read_compare(char response2[400]);
//Flags
int RegFlag = 0;
int LogInFlag = 0;
int ChatFlag = 0;
int FriendFlag = 0;
int F_EntryWindow = 0;
int loop = 1;
int valid =0;
int signInvalid;
int signUpvalid;
int OpenDialog = 0;
//Username/Password Buffers
char username[50];
char *name=NULL;
char *password=NULL;
char *fl=NULL;
char sent_message[300];
char contacts[10][30];
char friendname[50];
char *FriendL [11];
//File Pointer
FILE *outfile;
//TestClient Necessities
//int SocketFD;
char RecvBuf[BUFFSIZE];
char SendBuf[BUFFSIZE];
int SocketFD;
int Signin;
int Signup;
//char *answer;
char friend_response[20]= "LABEL FOR INVALID";
int seconds_rn;
//-------------------WINDOW CONTROL-------------------------
static void close_program(GtkWidget *widget, gpointer data)
{
	loop = 0;
}
static void create_chat_window(GtkWidget *widget, gpointer data)
{
	ChatFlag = 1;
}
static void delete_chat_window(GtkWidget *widget, gpointer data)
{
	ChatFlag = 0;
}
static void create_friend_window(GtkWidget *widget, gpointer data)
{
#ifdef DEBUG
	printf("friend flag turning into 1\n");
#endif	
	FriendFlag = 1;
}
static void close_friend_window(GtkWidget *widget, gpointer data)
{
	FriendFlag = 0;
}
static void delete_friend_window(GtkWidget *widget, gpointer data)
{
	FriendFlag = 0;
}

static void Delete_Friend_Entry(GtkWidget *widget, gpointer data)
{
	gtk_widget_destroy((AddFriendWindow) );
        AddFriendWindow =NULL;	
}		
static void Delete_Friend_Entry2(GtkWidget *widget, gpointer data)
{
	gtk_widget_destroy((RemoveFriendWindow) );
        RemoveFriendWindow =NULL;
}

static void destroy_popup(void)
{
	gtk_widget_destroy(window_dialog);
}

//---------------------------------CLICK FUNCTIONS-------------------------------------------
static void check_credentials(void)
{
/*
 *Function: check_credentials
 *---------------------------
 *  Void function for signin signup validation
 *
 */
	if (RegFlag!=0 && name != NULL)
                {
      
#ifdef DEBUG
	                printf("SignUp function is called\n");
#endif
	                signUpvalid = SignUp(name, RecvBuf, SocketFD);
#ifdef DEBUG
	        	printf("SignUp function finished\n");
#endif 
			RegFlag = 0;
                        if (signUpvalid == TRUE)
                        {
                                signInvalid = TRUE;
#ifdef DEBUG       
                                printf("SignUp function is called\n");
#endif 
                                update_invalid_label();
#ifdef DEBUG
                                printf("signInvalid is1 %d\n", signInvalid);
                                printf("signUpValid is2 :%d\n", signUpvalid);
#endif
	                }
                        else if (signInvalid == FALSE)
                        {
                                signInvalid = FALSE;
                                update_invalid_label();
#ifdef DEBUG
	                        printf("signInvalid is3 %d\n", signInvalid);
                                printf("signUpValid is4 :%d\n", signUpvalid);
#endif 
	               }
                }
                if (LogInFlag!= 0 && name != NULL)
                {
                        signInvalid = SignIn(name, RecvBuf, SocketFD);
#ifdef DEBUG
                        printf("SignIn function finished\n");
#endif
			fl = malloc(30*sizeof(char));
                        fl[0] = '\0';
                        strcat(fl,FriendList());
#ifdef DEBUG
                        printf("Friendlist is %s inside loginFlag\n", fl);
#endif
                        if (fl!=NULL)
			{
	                      printf("fl is %s\n",fl); 
			}
			LogInFlag = 0;
#ifdef DEBUG
                        printf("chekc point 1\n");
#endif
                        if (signInvalid == TRUE)
                        {
                                signUpvalid = TRUE;
#ifdef DEBUG
                                printf("signInvalid is5 %d\n", signInvalid);
                                printf("signUpValid is6 :%d\n", signUpvalid);
#endif
                                update_invalid_label();
#ifdef DEBUG
                                printf("signInvalid is5 %d\n", signInvalid);
                                printf("signUpValid is6 :%d\n", signUpvalid);
#endif
                        }
                        else if(signInvalid == FALSE)
                        {       
                                signUpvalid = FALSE;
#ifdef DEBUG
			        printf("signInvalid is7 %d\n", signInvalid);
                                printf("signUpValid is8 :%d\n", signUpvalid);
#endif
		                update_invalid_label();
                        }
#ifdef DEBUG
                        printf("signInvalid9 is %d\n", signInvalid);
                        printf("signUpValid is10 :%d\n", signUpvalid);
                        printf("Friendlist flag is: %d\n", FriendFlag);
#endif 
               }
}
//Update Contact List
static void update_contact_list(GtkWidget *widget, gpointer data)
{
	int j=0;
        char *tempf = strtok(fl, " ");
	while (j < 10)
	{
		FriendL[j] = tempf;
		tempf = strtok(NULL, " ");
                j++;
	}
        char *MessageFF=NULL;
	for (int i = 0; i<10; i++){
	
		if (FriendL[i]!=NULL)
		{
			MessageFF = FriendL[i];
		}
		else
		{
			MessageFF = "No Friend";

		}

	strcpy(contacts[i],MessageFF);
	}
}

//Send Message
static void send_message(GtkWidget *widget, gpointer data)
{
/* Function: send_message
 * ----------------------
 * Sends what you type in the entry to the server
 *
 * Calls function: SendMessage
 * 
 */
	char recieved[300];
	int i;

	i = gtk_notebook_get_current_page(GTK_NOTEBOOK(notebook));
	gtk_label_set_text(GTK_LABEL(data), gtk_entry_get_text(GTK_ENTRY(message[i])));	
	strncpy(sent_message, gtk_label_get_text(GTK_LABEL(data)),sizeof(sent_message));

	gtk_label_set_text(GTK_LABEL(data), NULL);
	gtk_text_buffer_insert_at_cursor(message_buffer[i],"\n", -1);
	gtk_text_buffer_insert_at_cursor(message_buffer[i],"You: ", -1);
	gtk_text_buffer_insert_at_cursor(message_buffer[i],sent_message, -1);

	strcat(st, "sendto ");
	strcat(st , contacts[i]);
	strcat(st , " ");
	strcat(st , sent_message);
#ifdef DEBUG
	printf("SendBuf: %s\n", st);
#endif
	SendMessage(st, recieved, SocketFD);

	strncpy(sent_message, "",sizeof(sent_message)); /* clear sent_message buffer */
	strncpy(st,"",sizeof(st)); /* clear st buffer */
	strncpy(st,"",sizeof(st));
}

static void request_message(void)
{
/* Function: request_message
 * -------------------------
 *
 * Retrieves the message from the server
 * 
 * Calls function: SendMessage
 * SendMessage parameter 1 is "request"
 *
 */
	int i;
	int match=0;
	char response[300];
        i = gtk_notebook_get_current_page(GTK_NOTEBOOK(notebook));

        if((ChatWindow!=NULL)&&(strcmp(contacts[i],username)!=0)) /* only request for message when chat window is open */
        {							  /* and the current chat window is not yours */	



		SendMessage("request",response ,SocketFD);	
		match = read_compare(response);
		if((match == 1)&&(strcmp(contacts[i],response)!=0)&&(strcmp(response,username)!=0)){	
			OpenDialog = 1;
			open_dialog();
		strncpy(response, "",sizeof(response));
		}
		if(strcmp(response,"No messages were sent to you\n")!=0){
        	gtk_text_buffer_insert_at_cursor(message_buffer[i],"\n", -1);
        	gtk_text_buffer_insert_at_cursor(message_buffer[i],contacts[i], -1);
        	gtk_text_buffer_insert_at_cursor(message_buffer[i],": ",-1);
		gtk_text_buffer_insert_at_cursor(message_buffer[i],response, -1);
		strncpy(response, "",sizeof(response));	
		}	
	}	
}
int read_compare(char response2[400])
{
	FILE *fp;
	char content[100];

	if((fp=fopen("UserList","r"))==NULL)
	{
		printf("couldn't open file\n");
	}

	while(fgets(content,sizeof(content),fp))
	{
		if(strstr(content,response2))
		{
			strncpy(content, "",sizeof(content));
			return 1;
		}
	}
	

	return 0;
}


void accept_friend(void)
{
/* Function: accept_friend
 * ----------------------
 *
 * Call function: SendMessage
 * SendMessage parameter 1 is "acceptrequest"
 */

#ifdef DEBUG
	printf("SendMessage('acceptrequest',temp, SocketFP)");
#endif
	 char G_temp[20];
	 SendMessage("acceptrequest",G_temp ,SocketFD);
#ifdef DEBUG
	 printf("Response from the server after acceptrequest %s\n", G_temp);
#endif
	strncpy(G_temp, "",sizeof(G_temp));
	OpenDialog =0;
}	



static void button_clicked_add(GtkWidget *widget, gpointer data)
{
/* Function: button_clicked_add
 * ----------------------------
 * 
 * When Accept Friend button is pressed send: addto 'friendname'
 *
 */         
        char response_add[40];
        gtk_label_set_text(GTK_LABEL(data),gtk_entry_get_text(GTK_ENTRY(add_f_entry)));
        strncpy(friendname, gtk_label_get_text(GTK_LABEL(data)),sizeof(friendname));
        
	strcat(add_to, "addto ");
        strcat(add_to, friendname);
#ifdef DEBUG
	printf("calling SendMessage, sending to server  = %s\n ",add_to);
#endif	
	SendMessage(add_to ,response_add ,SocketFD);
	printf("response from server = %s\n",response_add);

	strncpy(add_to,"", sizeof(add_to));
#ifdef DEBUG
	printf("friend name to be added %s\n",friendname);
#endif
	strncpy(response_add, "",sizeof(response_add));
}

static void button_clicked_remove(GtkWidget *widget, gpointer data)
{

        gtk_label_set_text(GTK_LABEL(data),gtk_entry_get_text(GTK_ENTRY(rm_f_entry)));
        strncpy(friendname, gtk_label_get_text(GTK_LABEL(data)),sizeof(friendname));
#ifdef DEBUG
        printf("Friend name to be removed: %s\n",friendname);
#endif
}

static void button_clicked(GtkWidget *widget, gpointer data)
{       
	name = malloc(30*sizeof(char));
	name[0] = '\0';
        gtk_label_set_text(GTK_LABEL(data),gtk_entry_get_text(GTK_ENTRY(entry)));       
        strncpy(name, gtk_label_get_text(GTK_LABEL(data)),sizeof(name));       
	strncpy(username, gtk_label_get_text(GTK_LABEL(data)),sizeof(username));
#ifdef DEBUG
	printf("Your New Username is: %s\n",name);
#endif
}

static void button_clicked2(GtkWidget *widget, gpointer data)
{       
	password = malloc(30*sizeof(char));
	password[0] = '\0';	
        gtk_label_set_text(GTK_LABEL(data),gtk_entry_get_text(GTK_ENTRY(entry2)));      
        strncpy(password, gtk_label_get_text(GTK_LABEL(data)),sizeof(password));
#ifdef DEBUG
	printf("Inside button click 2 password function: \n");
#endif
	strcat(name, " ");
        strcat(name, password);
	LogInFlag = 1;

#ifdef DEBUG
        printf("Inside LogIn button, LogInflag is : %d\n", LogInFlag);
#endif
}
static void button_clicked_register(GtkWidget *widget, gpointer data)
{
	name = malloc(30*sizeof(char));
        name[0] = '\0';
	gtk_label_set_text(GTK_LABEL(data),gtk_entry_get_text(GTK_ENTRY(entry)));
        strncpy(name, gtk_label_get_text(GTK_LABEL(data)),sizeof(name));
#ifdef DEBUG 
       printf("Your New Username is: %s\n",name);
#endif
}

static void button_clicked_register2(GtkWidget *widget, gpointer data)
{
	password = malloc(30*sizeof(char));
        password[0] = '\0';
        gtk_label_set_text(GTK_LABEL(data),gtk_entry_get_text(GTK_ENTRY(entry2)));
        strncpy(password, gtk_label_get_text(GTK_LABEL(data)),sizeof(password));
#ifdef DEBUG
	printf("Your New Password is: %s\n",password);
#endif
	strcat(name, " ");
	strcat(name, password);
	RegFlag = 1;
#ifdef DEBUG
	printf("Inside Reg button, regflag is : %d\n", RegFlag);
#endif
}

void UpdateWindow(void)
{

	while(gtk_events_pending())
	{
		currenttime();	
		if((ChatWindow!=NULL)&&(OpenDialog==0)){
		if((seconds_rn%2)==0)
		{
			request_message();
		}
		}
		gtk_main_iteration();
	}
}


static void update_invalid_label()
{
	if (signInvalid==0 || signUpvalid==0)
        {
	      gtk_label_set_text(GTK_LABEL(invalid_label),"invalid");
              FriendFlag = 0;
	}

	else
	{
	      gtk_label_set_text(GTK_LABEL(invalid_label),"Success!");
              FriendFlag = 1;
	}
#ifdef DEBUG
	                printf("friendflag is %d\n", FriendFlag);
#endif
}


//Notebook Functions
static void remove_book( GtkButton   *button,
                         GtkNotebook *notebook )
{
    gint page;

    page = gtk_notebook_get_current_page (notebook);
    gtk_notebook_remove_page (notebook, page);
    /* Need to refresh the widget --
 *  *      This forces the widget to redraw itself. */
    gtk_widget_queue_draw (GTK_WIDGET (notebook));
}


void currenttime(void)
{
	time_t CurrentTime;
	CurrentTime = time(NULL);
	struct tm *myTime = localtime(&CurrentTime);
	seconds_rn = myTime->tm_sec;

}
//---------------------WINDOWS-------------------------------

/*This */
void CreateWindow()
{	
#ifdef DEBUG
	printf("inside update window: SignINvalid is %d SignUPvalid is %d\n", signInvalid, signUpvalid);
	printf("friend flag inside create window is %d\n", FriendFlag);
#endif
        if ( (ChatFlag == 0) && (FriendFlag == 0) && (Window == NULL) )
                {
#ifdef DEBUG       
                        printf("LOGIN\n");
			printf("Inside createWindow fucntion checkpoint\n");
                        printf("username: %s, password: %s\n", name, password);
#endif
		if(FriendWindow!=NULL)
			{
                        	gtk_widget_destroy( (FriendWindow) );
				FriendWindow =NULL;
			}
			Window = Login_Window();
			gtk_widget_show_all(Window);

                }
        if ( (ChatFlag == 1) && (ChatWindow == NULL))
                {
                        gtk_widget_destroy((FriendWindow) );
                	FriendWindow =NULL;
        		ChatWindow =  Chat_Window();
			gtk_widget_show_all(ChatWindow);
                }

        if ( (FriendFlag == 1) &&(FriendWindow == NULL))
                {       
                        if(Window!=NULL)
			{
				gtk_widget_destroy((Window));
                		Window =NULL;
			}
			if(ChatWindow!=NULL)
			{
				gtk_widget_destroy( (ChatWindow) );
        			ChatWindow =NULL;
			}
#ifdef DEBUG
			printf("F_EntryWindow = %d\n", F_EntryWindow);
#endif
			FriendWindow = Friend_List();
                        gtk_widget_show_all(FriendWindow);
			
			
                }
}


//Login Window
GtkWidget *Login_Window()
{
	//gtk_init(argc, argv);
	GtkWidget *window, *vbox, *label, *label2, *label3;
	GtkWidget *button, *button2, *button3, *hbutton_box, *hpaned;
	GtkEntryBuffer *buffer;	
	GtkEntryBuffer *buffer2;
	GtkWidget *table;
	
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
        gtk_window_set_default_size(GTK_WINDOW(window),300,350);

	//Button Click To End Program
	g_signal_connect(window,"delete_event",G_CALLBACK(close_program),NULL);
	
	label2 = gtk_label_new("");
	label3 = gtk_label_new("");
	invalid_label = gtk_label_new("");	
	table = gtk_table_new(2,2,0);
	vbox = gtk_vbox_new(0,0);
	hpaned = gtk_hpaned_new();

	hbutton_box= gtk_hbutton_box_new();
	buffer = gtk_entry_buffer_new("Empty",-1);
	buffer2= gtk_entry_buffer_new("Empty",-1);
        label = gtk_label_new("Login");
        gtk_box_pack_start(GTK_BOX(vbox),label,1,0,0);
	label = gtk_label_new("Username:");
	gtk_table_attach(GTK_TABLE(table), label,0,1,0,1,GTK_FILL,GTK_FILL,0,0);
	label = gtk_label_new("Password:");

	gtk_table_attach(GTK_TABLE(table), label,0,1,1,2, GTK_FILL,GTK_FILL,0,0);

	entry = gtk_entry_new();
        gtk_entry_set_buffer(GTK_ENTRY(entry),(buffer));
	gtk_table_attach(GTK_TABLE(table), entry,2,6,0,1,GTK_FILL,GTK_FILL,0,0);

	entry2 = gtk_entry_new();
	gtk_entry_set_buffer(GTK_ENTRY(entry2),(buffer2));
	gtk_table_attach(GTK_TABLE(table), entry2,2,6,1,2,GTK_FILL,GTK_FILL,0,0);


	gtk_box_pack_start(GTK_BOX(vbox),table,0,0,0);
        button = gtk_button_new_with_label("Login");
        button2 = gtk_button_new_with_label("Register");
	button3 = gtk_button_new_with_label("Quit");

	//Button Clicks For Login
	g_signal_connect(button, "clicked", G_CALLBACK(button_clicked), label3);
	g_signal_connect(button, "clicked", G_CALLBACK(button_clicked2), label2);
	g_signal_connect(button, "clicked", G_CALLBACK(create_friend_window), NULL);
	g_signal_connect(button, "clicked", G_CALLBACK(check_credentials), NULL);
	g_signal_connect(button, "clicked", G_CALLBACK(CreateWindow), NULL);

	//Button Clicks for Register
	g_signal_connect(button2, "clicked", G_CALLBACK(button_clicked_register), label3);
	g_signal_connect(button2, "clicked", G_CALLBACK(button_clicked_register2), label2);
	g_signal_connect(button2, "clicked", G_CALLBACK(create_friend_window), NULL);
	g_signal_connect(button2, "clicked", G_CALLBACK(check_credentials), NULL);
	g_signal_connect(button2, "clicked", G_CALLBACK(CreateWindow), NULL);
	
	//Button Clicks for Quit
	g_signal_connect(button3, "clicked", G_CALLBACK(gtk_main_quit), NULL);
	g_signal_connect(button3, "clicked", G_CALLBACK(close_program), NULL);

	gtk_box_pack_start(GTK_BOX(vbox), invalid_label,0,0,0);	
	gtk_box_pack_start(GTK_BOX(hbutton_box),button2,0,0,0);
        gtk_box_pack_start(GTK_BOX(hbutton_box),button,0,0,0);
        gtk_box_pack_start(GTK_BOX(vbox),hbutton_box,2,0,0);
        gtk_container_add(GTK_CONTAINER(window),vbox);
	
 
#ifdef DEBUG
	printf("inside log=in window function\n");
#endif            
	return(window);

}

//Chat Window
GtkWidget *Chat_Window( )
{	   
    GtkWidget *window, *scrolled_window;
    GtkWidget *button;
    GtkWidget *table;
    GtkWidget *label;    
    GtkWidget *Text_Area[10];
    GtkEntryBuffer *buffer[10];
    GtkWidget *messagelabel;   

    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(window),300,350);

    //Button To End Program
    g_signal_connect( window, "delete_event", G_CALLBACK(close_program), NULL);

    gtk_container_set_border_width (GTK_CONTAINER (window), 10);

    // message label not to be displayed
    messagelabel = gtk_label_new(" ");

    //Table Container Created
    table = gtk_table_new (3, 6, FALSE);
    gtk_container_add (GTK_CONTAINER (window), table);

    //Create a New notebook, Set Tab
    notebook = gtk_notebook_new ();
    gtk_notebook_set_tab_pos (GTK_NOTEBOOK (notebook), GTK_POS_TOP);
    gtk_table_attach_defaults (GTK_TABLE (table), notebook, 0, 6, 0, 1);
    gtk_widget_show(notebook);

    //Scrolled Window with Text Box
    for( int i = 9; i>-1; i-- )
    {
	if(contacts[i]!=NULL)
	{

    	Text_Area[i] = gtk_text_view_new();

    	message_buffer[i] = gtk_text_view_get_buffer(GTK_TEXT_VIEW(Text_Area[i]));
    	gtk_text_buffer_set_text(message_buffer[i],"Hello!",-1);

    	GtkWidget *console = gtk_table_new(3,2,FALSE);

    	scrolled_window = gtk_vscrollbar_new(gtk_text_view_get_vadjustment(GTK_TEXT_VIEW(Text_Area[i])));

    	gtk_table_attach_defaults(GTK_TABLE(console),Text_Area[i],0,5,0,1);
    	gtk_table_attach_defaults(GTK_TABLE(console),scrolled_window,5,6,0,1);

    	gtk_widget_set_size_request(Text_Area[i],200,200);
    	gtk_text_view_set_buffer(GTK_TEXT_VIEW(Text_Area[i]),message_buffer[i]);
    
    	//Create Entry
    	message[i] = gtk_entry_new();
    	buffer[i] = gtk_entry_buffer_new("Enter Message",-1);
    	gtk_entry_set_buffer(GTK_ENTRY(message[i]),(buffer[i]));	

    	gtk_table_attach_defaults(GTK_TABLE(console),message[i],0,4,1,2);
    	gtk_widget_show(message[i]);

    	//Create Buttons
    	button = gtk_button_new_with_label("Send");
    	gtk_table_attach_defaults (GTK_TABLE (console), button, 5, 6, 1, 2);
    	g_signal_connect(button, "clicked", G_CALLBACK (send_message), messagelabel);
    	gtk_widget_show (button);

    	button = gtk_button_new_with_label ("Close");
    	g_signal_connect(button, "clicked", G_CALLBACK (delete_chat_window), NULL);
    	g_signal_connect(button, "clicked", G_CALLBACK (create_friend_window), NULL);
    	g_signal_connect(button, "clicked", G_CALLBACK(CreateWindow), NULL);

    	gtk_table_attach_defaults (GTK_TABLE (console), button, 0, 1, 2, 3);
    	gtk_widget_show (button);
    
    	button = gtk_button_new_with_label ("Request Message");
    	g_signal_connect(button,"clicked",G_CALLBACK(request_message),NULL);
    	gtk_table_attach_defaults (GTK_TABLE (console), button, 1, 2, 2, 3);
    	gtk_widget_show (button);
    

    	button = gtk_button_new_with_label ("Accept Friend");
   
    	g_signal_connect(button,"clicked",G_CALLBACK(accept_friend),NULL);
    	gtk_table_attach_defaults (GTK_TABLE (console), button, 2, 3, 2, 3);
    	gtk_widget_show (button);

    	button = gtk_button_new_with_label("Remove Friend");
    	g_signal_connect(button,"clicked",G_CALLBACK(remove_book),notebook);
    	g_signal_connect(button, "clicked", G_CALLBACK(CreateWindow), NULL);
    	gtk_table_attach_defaults(GTK_TABLE(console),button,5,6,2,3);
    	gtk_widget_show(button);

      
    	//Add Page
    	label = gtk_label_new(contacts[i]);
    	gtk_notebook_insert_page(GTK_NOTEBOOK(notebook),console,label,0);

	}
    }

    //Set what page to start at (page 1)  
    gtk_notebook_set_current_page(GTK_NOTEBOOK(notebook),0);

    return (window);	
}


GtkWidget *Friend_List( )
{
	//gtk_init(argc, argv);
#ifdef DEBUG
	printf("inside friendlist function\n");
#endif
	GtkWidget *window, *button, *label, *scroll_window,*vbox, *table;
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_default_size(GTK_WINDOW(window),260,300);
        g_signal_connect(window,"delete_event",G_CALLBACK(close_program),NULL);

//initialization of vbox
	table = gtk_table_new(3,10,0);

//vbox inside the scroll window


	vbox = gtk_vbox_new(0,0);
	
	int j=0;
	char *tempf = strtok(fl, " ");
	while (j < 10)
	{
#ifdef DEBUG
		printf("friendlist is this inside gtk: %s\n", tempf);
#endif
		FriendL[j] = tempf;
		tempf = strtok(NULL, " ");
#ifdef DEBUG
                printf("Friend name is %s at %d\n", FriendL[j], j);
#endif
                j++;
	}
        char *MessageFF=NULL;
	for (int i = 0; i<10; i++){
	
		if (FriendL[i]!=NULL)
		{
			MessageFF = FriendL[i];
		}
		else 
		{
			MessageFF = "No Friend";
		}
#ifdef DEBUG	
                        printf("Friend name is %s at %d\n", FriendL[i], i);
#endif	
	//Fills Buttons With Friend List
	button = gtk_button_new_with_label(MessageFF);
	strcpy(contacts[i],MessageFF);
	gtk_box_pack_start(GTK_BOX(vbox), button ,0,1,1);
	g_signal_connect(button,"clicked",G_CALLBACK(close_friend_window),NULL);
	g_signal_connect(button,"clicked",G_CALLBACK(create_chat_window),NULL);
	g_signal_connect(button, "clicked", G_CALLBACK(update_contact_list), NULL);
	g_signal_connect(button, "clicked", G_CALLBACK(CreateWindow), NULL);

	}

	scroll_window = gtk_scrolled_window_new(NULL,NULL);
	gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scroll_window), vbox);
	vbox = gtk_vbox_new(0,0);
	button = gtk_button_new_with_label("  X  ");
	gtk_table_attach(GTK_TABLE(table), button ,0,1,0,1,GTK_FILL,GTK_FILL,40,0);
	g_signal_connect(button, "clicked", G_CALLBACK(Remove_Friend_Window), NULL);
	label= gtk_label_new(username);
	gtk_table_attach(GTK_TABLE(table), label,4,6,0,1,GTK_FILL,GTK_FILL,0,0);
	button = gtk_button_new_with_label("  +  ");	
	g_signal_connect(button, "clicked", G_CALLBACK(Add_Friend_Window), NULL);
	gtk_table_attach(GTK_TABLE(table), button ,9,10,0,1,GTK_FILL,GTK_FILL,40,0);
	gtk_box_pack_start(GTK_BOX(vbox), table,0,1,1);
	gtk_box_pack_start(GTK_BOX(vbox), scroll_window,1,1,0);
	table = gtk_table_new(3,10,0); 
	button= gtk_button_new_with_label("Next");
	gtk_table_attach(GTK_TABLE(table), button,9,10,0,1,GTK_FILL,GTK_FILL,35,0);
	g_signal_connect(button,"clicked",G_CALLBACK(close_friend_window),NULL);
	g_signal_connect(button,"clicked",G_CALLBACK(create_chat_window),NULL);
	g_signal_connect(button, "clicked", G_CALLBACK(update_contact_list), NULL);
	g_signal_connect(button, "clicked", G_CALLBACK(CreateWindow), NULL);
	button= gtk_button_new_with_label("Previous");
        gtk_table_attach(GTK_TABLE(table), button,0,1,0,1,GTK_FILL,GTK_FILL,35,0);
	g_signal_connect(button,"clicked",G_CALLBACK(delete_friend_window),NULL);
	g_signal_connect(button, "clicked", G_CALLBACK(CreateWindow), NULL);
	gtk_box_pack_start(GTK_BOX(vbox), table,0,1,1);
	gtk_container_add(GTK_CONTAINER(window), vbox);
	return(window);
}

static void open_dialog(void)
{
	if(ChatWindow!=NULL){
	GtkWidget *label, *button, *vbox;
	window_dialog = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	vbox = gtk_vbox_new(0,0);
	label= gtk_label_new("Accept New Friend Request!");
	gtk_box_pack_start(GTK_BOX(vbox),label,0,0,0);
	button= gtk_button_new_with_label("ACCEPT");
	g_signal_connect(button,"clicked",G_CALLBACK(accept_friend),NULL);
	g_signal_connect(button,"clicked",G_CALLBACK(destroy_popup),NULL);
	gtk_box_pack_start(GTK_BOX(vbox),button,0,0,0);		
	button= gtk_button_new_with_label("CLOSE");
	g_signal_connect(button,"clicked",G_CALLBACK(destroy_popup),NULL);
	gtk_box_pack_start(GTK_BOX(vbox),button,0,0,0);
	gtk_container_add(GTK_CONTAINER(window_dialog),vbox);
	gtk_widget_show_all(window_dialog);}
}

GtkWidget *Add_Friend_Window()
{
	GtkWidget *button, *label, *vbox, *label2;	
	AddFriendWindow	 = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_default_size(GTK_WINDOW(AddFriendWindow),80,80);
	g_signal_connect(AddFriendWindow,"delete_event",G_CALLBACK(Delete_Friend_Entry),NULL);

	vbox = gtk_vbox_new(0,0);
	add_f_entry = gtk_entry_new();
	label = gtk_label_new("Friend Name: ");
	friend_invalid_label= gtk_label_new(friend_response);
	label2 = gtk_label_new(" ");
	button = gtk_button_new_with_label("ADD");
	g_signal_connect(button, "clicked", G_CALLBACK(button_clicked_add), label2);
	
	gtk_box_pack_start(GTK_BOX(vbox),label, 0,0,0);
	gtk_box_pack_start(GTK_BOX(vbox),add_f_entry, 0,0,0);
	gtk_box_pack_start(GTK_BOX(vbox),button,0,0,0);
	gtk_box_pack_start(GTK_BOX(vbox), friend_invalid_label,0,0,0);
	gtk_container_add(GTK_CONTAINER(AddFriendWindow),vbox);	
	gtk_widget_show_all(AddFriendWindow);
	
	return(AddFriendWindow);	

}


GtkWidget *Remove_Friend_Window()
{
	GtkWidget *button, *label, *hbox, *label2;
        RemoveFriendWindow  = gtk_window_new(GTK_WINDOW_TOPLEVEL);
        g_signal_connect(RemoveFriendWindow,"delete_event",G_CALLBACK(Delete_Friend_Entry2),NULL);

        hbox = gtk_hbox_new(0,0);
        rm_f_entry = gtk_entry_new();
        label = gtk_label_new("Friend Name: ");
	label2 = gtk_label_new(" ");
        button = gtk_button_new_with_label("Remove");
	g_signal_connect(button, "clicked", G_CALLBACK(button_clicked_remove), label2);
        gtk_box_pack_start(GTK_BOX(hbox),label, 0,0,0);
	gtk_box_pack_start(GTK_BOX(hbox),rm_f_entry, 0,0,0);
        gtk_box_pack_start(GTK_BOX(hbox),button,0,0,0);

        gtk_container_add(GTK_CONTAINER(RemoveFriendWindow),hbox);
        gtk_widget_show_all(RemoveFriendWindow);

        return(RemoveFriendWindow);
}
//----------------------MAIN PROGRAM-------------------------------------
//Main Loop
int main(int argc, char *argv[])
{
	gtk_init (&argc, &argv);


#ifdef DEBUG
	printf("%s: Starting...\n", argv[0]);
#endif
	CreateSocket(argc, argv, &SocketFD, SendBuf, RecvBuf);
#ifdef DEBUG
	printf("after creatsocket\n");
        printf("socket creation completed in main\n");
#endif	
	login_window = NULL;
	CreateWindow();
	while(loop)
	{
		UpdateWindow();
	}

	
		
	if (fl!=NULL)
	{
		free(fl);
	}
	return 0;
}
