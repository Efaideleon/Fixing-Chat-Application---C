# GUI Class Diagram Text

**What is the application you're modeling?**
This is a chat application. This is the software architecture for the GUI. 

**What are the main functionalities?**
The GUI's main functionality is to show the login window so that the user can login and register, the friend list window to add friends and click on friends to open the chat window, and the chat window so that the user can send messages to their friends.

## Initial State for GTK.c

**What are the main objects or concepts in your system?**

* Login Window
* Chat Window
* Friend List
* Add Friend Window
* Remove Friend Window

---

## Login Window

### Attributes

* window       : GtkWidget*
* vbox         : GtkWidget*
* label        : GtkWidget*
* label2       : GtkWidget*
* label3       : GtkWidget*
* invalid_label: GtkWidget*
* button       : GtkWidget*
* button2      : GtkWidget*
* button3      : GtkWidget*
* hbutton_box  : GtkWidget*
* hpaned       : GtkWidget*
* buffer       : GtkEntryBuffer*
* buffer2      : GtkEntryBuffer*
* table        : GtkWidget*
* entry        : GtkWidget*
* entry2       : GtkWidget*

### Methods

* update_invalid_label()

### Attribute Dependecies

* invalid_label

### Method Dependencies

```c
button_clicked(data, entry, username, name) // get the username from the entry box and store it in a variable
button_clicked2(data, password, entry2, LogInFlag) // get the password from the entry box and store it in a variable
create_friend_window() // sets flag to create friend window
check_credentials(RefFlag, name, signUpvalid, (func) SignUp, (func) update_invalid_label, (func) SignIn, (func) FriendList) // check if the username can be registered, and check if username and password are correct
CreateWindow(ChatFlag, FriendFlag, Window, FriendWindow, (func/class) Login_Window, ChatWindow, (func/class) Chat_Window(), (func/class) Friend_List) // determines which window to create and destroy based on the flags
button_clicked_register(name, data, entry) // stores the username in the name buffer when register button is clicked
button_clicked_register2(password, data, entry2, RegFlag) // stores the password in the password buffer when the register button is clicked
create_friend_window() // sets flag that friend window is active
gtk_main_quit()
close_program() // sets loop boolean to 0
```

---

## Chat Window

### Attributes

* window            : GtkWidget*
* scrolled_window   : GtkWidget*
* button            : GtkWidget*
* table             : GtkWidget*
* label             : GtkWidget*
* text_area         : GtkWidget*
* buffer            : GtkEntryBuffer*
* message_label     : GtkWidget*

### Attribute Dependencies

* notebook
* message_buffer
* contacts
* message

### Method Dependencies

```c
send_message(data, message, sent_message, message_buffer, contacts, SocketFD, st, (func) SendMessage) // gets the message from the text entry box in the chat window and calls SendMessage
delete_chat_window() // sets flag to delete chat window
create_friend_window() // sets flag that friend window is active
CreateWindow(ChatFlag, FriendFlag, Window, FriendWindow, (func/class) Login_Window, ChatWindow, (func/class) Chat_Window(), (func/class) Friend_List) // determines which window to create and destroy based on the flags
request_message(ChatWindow, contact, username, notebook, SocketFD, OpenDialog, message_buffer, (func) SendMessage, (func) read_compare, (func) open_dialog) //retrieves message from the server
accept_friend((func) SendMessage, SocketFD, OpenDialog) // sends message to the server with acceptrequest
remove_book(notebook) // forces the widget to redraw itself
```

---

## Friend List

### Attributes

* window        : GtkWidget*
* button        : GtkWidget*
* label         : GtkWidget*
* scroll_window : GtkWidget*
* vbox          : GtkWidget*
* table         : GtkWidget*   

### Attribute Dependencies

* FriendL
* contacts

### Method Dependencies

```c
close_friend_window() // set Friendflag to 0 to show that its inactive
create_chat_window() // set ChatFlag to 1 for active
CreateWindow(ChatFlag, FriendFlag, Window, FriendWindow, (func/class) Login_Window, ChatWindow, (func/class) Chat_Window(), (func/class) Friend_List) // determines which window to create and destroy based on the flags
(func/Class) Remove_Friend_Window
(func/Class) Add_Friend_Window
update_contact_list((func/class) Friend_List, FriendL, contacts) // refreshes the friend list with new friends or replaces it with No friend
delete_friend_window() // set FriendFlag to 0 to show that its inactive
```

---

## Add Friend Window

### Attributes

* button    : GtkWidget*
* label     : GtkWidget*
* vbox      : GtkWidget*
* label2    : GtkWidget*

### Attribute Dependencies

* AddFriendWindow
* friend_invalid_label
* add_f_entry
* friend_response

#### Method Dependecies

```c
Delete_Friend_Entry(AddFriendWindow) // destroys the AddFriendWindow widget
button_clicked_add(data, add_f_entry, friendname, add_to, SocketFD, (func) SendMessage) // when accept friend button is pressed send: addto 'friendname'
```

---

## Remove Friend Window

### Attributes

* button    : GtkWidget*
* label     : GtkWidget*
* hbox      : GtkWidget*
* label2    : GtkWidget*

### Attribute Dependencies

* RemoveFriendWindow
* rm_f_entry

### Method Dependencies

```c
Delete_Friend_Entry2(RemoveFriendWindow) // destroys the RemoveFriendWindow widget
button_clicked_remove(data, rm_f_entry, friend_name)
```

---
---

# Refactoring Initial State of GTK.c

## UI Class

---

* **LoginWindowUI**
* **FriendListUI**
* **ChatWindowUI**
* **FriendRequesWidgetUI**
* **RemoveFriendWidgetUI**


## Credential Service

### Attributes

* username      : char
* name          : char*
* password      : char*
* LogInFlag     : int
* signUpValid   : int
* SignUp        : int
* RegFlag       : int
* credentials_data : struct CredentialsData
* network_service : NetworkService
* signInvalid   : int

### Methods

```c
void button_clicked(gpointer data, (G) GtkWidget* entry, (G) char username, (G) char* name) // get the username from the entry box and store it in a variable
button_clicked2(gpointer data, (G) char* password, GtkWidget* entry2, (G) int LogInFlag) // get the password from the entry box and store it in a variable
check_credentials((G) int RefFlag, (G) char* name, (G) int signUpvalid, (G) char [] RecvBuf, (func) int SignUp, (func) void update_invalid_label, (func) int SignIn, (func) char* FriendList) // check if the username can be registered, and check if username and password are correct
button_clicked_register((G) char* name, gpointer data, (G) GtkWidget* entry) // stores the username in the name buffer when register button is clicked
button_clicked_register2((G) char* password, gpointer data,(G) GtkWidget* entry2,(G) int RegFlag) // stores the password in the password buffer when the register button is clicked
```

### Attribute Dependencies

* data      : gpointer
* entry2    : GtkWidget*
* RecvBuf   : char[]
* entry     : GtkWidget*

### Method Dependencies

```c
SignUp()
update_invalid_label()
SignIn()
FriendList()
```

---

## Message Service

### Attributes

* message           : GtkWidget*
* sent_message      : char[]
* message_buffer    : GtkTextBuffer*[]
* st                : char[]
* OpenDialog        : int

### Methods

```c
send_message(gpointer data, (G) GtkWidget* message, (G) char [] sent_message, (G) GtkTextBuffer* [] message_buffer, (G) char [][] contacts, (G) int SocketFD, (G) char[] st, (func) void SendMessage) // gets the message from the text entry box in the chat window and calls SendMessage
request_message((G) GtkWidget* ChatWindow, (G) char[][] contacts, (G) char[] username, (G) GtkWidget* notebook, (G) int SocketFD, (G) int OpenDialog, (G) GtkTextBuffer* [] message_buffer, (func) void SendMessage, (func) int read_compare, (func) void open_dialog) //retrieves message from the server
```

### Attribute Dependencies

* data          : gpointer
* SocketFD      : int
* ChatWindow    : GtkWidget*
* contacts      : char[][]
* notebook      : GtkWidget*

### Method Dependencies

```c
SendMessage()
read_compare()
open_dialog()
```

---

## Window Manager

### Attributes

* ChatFlag              : int
* FriendFlag            : int
* Window                : GtkWidget*
* FriendWindow          : GtkWidget*
* RemoveFriendWindow    : GtkWidget*
* AddFriendWindow       : GtkWidget*

### Methods

```c
create_friend_window() // sets flag to create friend window
CreateWindow((G) int ChatFlag, (G) int FriendFlag, (G) GtkWidget* Window, (G) GtkWidget* FriendWindow, (func/class) GtkWidget* Login_Window, (G) GtkWidget* ChatWindow, (func/class) GtkWidget* Chat_Window(), (func/class) GtkWidget* Friend_List) // determines which window to create and destroy based on the flags
delete_chat_window() // sets flag to delete chat window
close_friend_window() // set Friendflag to 0 to show that its inactive
create_chat_window() // set ChatFlag to 1 for active
delete_friend_window() // set FriendFlag to 0 to show that its inactive
Delete_Friend_Entry2((G) GtkWidget* RemoveFriendWindow) // destroys the RemoveFriendWindow widget
Delete_Friend_Entry((G) GtkWidget* AddFriendWindow) // destroys the AddFriendWindow widget
```

### Attribute Dependencies

### Method Dependencies

```c
Login_Window() // class
Chat_Window() // class
Friend_List() // class
```

---

## Friend Request Handler

### Attributes

* FriendL       : char*
* contacts      : char[][]
* add_to        : char[]
* friendname    : char[]
* add_f_entry   : GtkWidget*
* rm_f_entry    : GtkWidget*
* friend_name   : char[]

### Methods

```c
accept_friend((func) void SendMessage, (G) int SocketFD, (G) int OpenDialog) // sends message to the server with acceptrequest
(func/Class) Remove_Friend_Window
(func/Class) Add_Friend_Window
update_contact_list((func/class) GtkWidget* Friend_List, (G) char* FriendL, (G) char[][] contacts, gpointer data) // refreshes the friend list with new friends or replaces it with No friend
button_clicked_add(gpointer data, (G) GtkWidget* add_f_entry, (G) char[] friendname, (G) char[] add_to, (G) int SocketFD, (func) void SendMessage) // when accept friend button is pressed send: addto 'friendname'
button_clicked_remove(gpointer data, (G) GtkWidget* rm_f_entry, (G) char[] friend_name)
```

### Attribute Dependencies

* OpenDialog : int
* contacs    : char[][]
* SocketFD   : int

### Function Dependencies

```c
SendMessage()
```

---

## Network Service

### Attributes

* RecvBuf  : char[]
* SendBuf  : char[]
* SocketFD : int

---

## Application Manager

### Methods

```c
gtk_main_quit()
close_program() // sets loop boolean to 0
remove_book((G) notebook) // forces the widget to redraw itself
```
---

>*Notes*
>* (G) - stands for global variable

---
