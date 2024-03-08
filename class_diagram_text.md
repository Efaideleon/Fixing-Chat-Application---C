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

* window
* vbox
* label
* label2
* label3
* button
* button2
* button3
* hbutton_box
* hpaned
* buffer
* buffer2
* table

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

* window
* scrolled_window
* button
* table
* label
* text_area
* bugger
* message_label

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

* window
* button
* label
* scroll_window
* vbox
* table 

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

* button
* label
* vbox
* label2

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

* button
* label
* hbox
* label2

### Attribute Dependencies

* RemoveFriendWindow
* rm_f_entry

### Method Dependencies

```c
Delete_Friend_Entry2(RemoveFriendWindow) // destroys the RemoveFriendWindow widget
button_clicked_remove(data, rm_f_entry, friend_name)
```

---

# Refactoring Initial State of GTK.c

## UI Class

---

## Credential Service

### Methods

```c
button_clicked(data, entry, username, name) // get the username from the entry box and store it in a variable
button_clicked2(data, password, entry2, LogInFlag) // get the password from the entry box and store it in a variable
check_credentials(RefFlag, name, signUpvalid, (func) SignUp, (func) update_invalid_label, (func) SignIn, (func) FriendList) // check if the username can be registered, and check if username and password are correct
button_clicked_register(name, data, entry) // stores the username in the name buffer when register button is clicked
button_clicked_register2(password, data, entry2, RegFlag) // stores the password in the password buffer when the register button is clicked
```

---

## Message Service

### Methods

```c
send_message(data, message, sent_message, message_buffer, contacts, SocketFD, st, (func) SendMessage) // gets the message from the text entry box in the chat window and calls SendMessage
request_message(ChatWindow, contact, username, notebook, SocketFD, OpenDialog, message_buffer, (func) SendMessage, (func) read_compare, (func) open_dialog) //retrieves message from the server
```

---

## Window Manager

### Methods

```c
create_friend_window() // sets flag to create friend window
CreateWindow(ChatFlag, FriendFlag, Window, FriendWindow, (func/class) Login_Window, ChatWindow, (func/class) Chat_Window(), (func/class) Friend_List) // determines which window to create and destroy based on the flags
delete_chat_window() // sets flag to delete chat window
close_friend_window() // set Friendflag to 0 to show that its inactive
create_chat_window() // set ChatFlag to 1 for active
delete_friend_window() // set FriendFlag to 0 to show that its inactive
Delete_Friend_Entry2(RemoveFriendWindow) // destroys the RemoveFriendWindow widget
Delete_Friend_Entry(AddFriendWindow) // destroys the AddFriendWindow widget
```

--

## Friend Request Handler

### Methods

```c
accept_friend((func) SendMessage, SocketFD, OpenDialog) // sends message to the server with acceptrequest
(func/Class) Remove_Friend_Window
(func/Class) Add_Friend_Window
update_contact_list((func/class) Friend_List, FriendL, contacts) // refreshes the friend list with new friends or replaces it with No friend
button_clicked_add(data, add_f_entry, friendname, add_to, SocketFD, (func) SendMessage) // when accept friend button is pressed send: addto 'friendname'
button_clicked_remove(data, rm_f_entry, friend_name)
```

---

## Application Manager

### Methods

```c
gtk_main_quit()
close_program() // sets loop boolean to 0
remove_book(notebook) // forces the widget to redraw itself
```
