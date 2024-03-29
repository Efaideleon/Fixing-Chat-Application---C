# GTK Compiler Flags
GTKINC = `pkg-config --cflags gtk+-2.0`
GTKLIBS = `pkg-config --libs gtk+-2.0`

CC = gcc -Wno-deprecated-declarations # -Wno-deprecated-declarations: disables deprecated warnings from gtk
CFLAGS = -Wall -ansi -std=c99 $(GTKINC)
LFLAGS = -Wall -ansi -std=c99 $(GTKLIBS)

# List of all the .c file
APPLICATION_MANAGER_C_FILES = ApplicationManager/ApplicationManager.c
CHAT_WINDOW_UI_C_FILES = ChatWindowUI/ChatWindowUI.c
CREDENTIAL_SERVICE_C_FILES = CredentialService/CredentialService.c
FRIEND_LIST_UI_C_FILES = FriendListUI/FriendListUI.c
FRIEND_REQUEST_HANDLER_C_FILES = FriendRequestHandler/FriendRequestHandler.c
FRIEND_REQUEST_WIDGET_UI_C_FILES = FriendRequestWidgetUI/FriendRequestWidgetUI.c
LOGIN_WINDOW_UI_C_FILES = LoginWindowUI/LoginWindowUI.c
MESSAGE_SERVICE_C_FILES = MessageService/MessageService.c
NETWORK_SERVICE_C_FILES = NetworkService/NetworkService.c
REMOVE_FRIEND_WIDGET_UI_C_FILES = RemoveFriendWidgetUI/RemoveFriendWidgetUI.c
WINDOW_MANAGER_C_FILES = WindowManager/WindowManager.c
EXTERNAL_TESTCLIENT_C_FILES = ../TestClient.c
EXTERNAL_SEND_C_FILES = ../send.c
EXTERNAL_USER_C_FILES = ../user.c

# Source directories
APPLICATION_MANAGER_SRC_DIR = ApplicationManager
CHAT_WINDOW_UI_SRC_DIR = ChatWindowUI
CREDENTIAL_SERVICE_SRC_DIR = CredentialService
FRIEND_LIST_UI_SRC_DIR = FriendListUI
FRIEND_REQUEST_HANDLER_SRC_DIR = FriendRequestHandler
FRIEND_REQUEST_WIDGET_UI_SRC_DIR = FriendRequestWidgetUI
LOGIN_WINDOW_UI_SRC_DIR = LoginWindowUI
MESSAGE_SERVICE_SRC_DIR = MessageService
NETWORK_SERVICE_SRC_DIR = NetworkService
REMOVE_FRIEND_WIDGET_UI_SRC_DIR = RemoveFriendWidgetUI
WINDOW_MANAGER_SRC_DIR = WindowManager
EXTERNAL_SRC_DIR = ..

# Object directories
APPLICATION_MANAGER_OBJ_DIR = ApplicationManager/objs
CHAT_WINDOW_UI_OBJ_DIR = ChatWindowUI/objs
CREDENTIAL_SERVICE_OBJ_DIR = CredentialService/objs
FRIEND_LIST_UI_OBJ_DIR = FriendListUI/objs
FRIEND_REQUEST_HANDLER_OBJ_DIR = FriendRequestHandler/objs
FRIEND_REQUEST_WIDGET_UI_OBJ_DIR = FriendRequestWidgetUI/objs
LOGIN_WINDOW_UI_OBJ_DIR = LoginWindowUI/objs
MESSAGE_SERVICE_OBJ_DIR = MessageService/objs
NETWORK_SERVICE_OBJ_DIR = NetworkService/objs
REMOVE_FRIEND_WIDGET_UI_OBJ_DIR = RemoveFriendWidgetUI/objs
WINDOW_MANAGER_OBJ_DIR = WindowManager/objs
EXTERNAL_OBJ_DIR = ..

# Objects
APPLICATION_MANAGER_OBJ = $(patsubst $(APPLICATION_MANAGER_SRC_DIR)/%.c, $(APPLICATION_MANAGER_OBJ_DIR)/%.o, $(APPLICATION_MANAGER_C_FILES))

CHAT_WINDOW_UI_OBJ = $(patsubst $(CHAT_WINDOW_UI_SRC_DIR)/%.c, $(CHAT_WINDOW_UI_OBJ_DIR)/%.o, $(CHAT_WINDOW_UI_C_FILES))

CREDENTIAL_SERVICE_OBJ = $(patsubst $(CREDENTIAL_SERVICE_SRC_DIR)/%.c, $(CREDENTIAL_SERVICE_OBJ_DIR)/%.o, $(CREDENTIAL_SERVICE_C_FILES))

FRIEND_LIST_UI_OBJ = $(patsubst $(FRIEND_LIST_UI_SRC_DIR)/%.c, $(FRIEND_LIST_UI_OBJ_DIR)/%.o, $(FRIEND_LIST_UI_C_FILES))

FRIEND_REQUEST_HANDLER_OBJ = $(patsubst $(FRIEND_REQUEST_HANDLER_SRC_DIR)/%.c, $(FRIEND_REQUEST_HANDLER_OBJ_DIR)/%.o, $(FRIEND_REQUEST_HANDLER_C_FILES))

FRIEND_REQUEST_WIDGET_UI_OBJ = $(patsubst $(FRIEND_REQUEST_WIDGET_UI_SRC_DIR)/%.c, $(FRIEND_REQUEST_WIDGET_UI_OBJ_DIR)/%.o, $(FRIEND_REQUEST_WIDGET_UI_C_FILES))

LOGIN_WINDOW_UI_OBJ = $(patsubst $(LOGIN_WINDOW_UI_SRC_DIR)/%.c, $(LOGIN_WINDOW_UI_OBJ_DIR)/%.o, $(LOGIN_WINDOW_UI_C_FILES))

MESSAGE_SERVICE_OBJ = $(patsubst $(MESSAGE_SERVICE_SRC_DIR)/%.c, $(MESSAGE_SERVICE_OBJ_DIR)/%.o, $(MESSAGE_SERVICE_C_FILES))

NETWORK_SERVICE_OBJ = $(patsubst $(NETWORK_SERVICE_SRC_DIR)/%.c, $(NETWORK_SERVICE_OBJ_DIR)/%.o, $(NETWORK_SERVICE_C_FILES))

REMOVE_FRIEND_WIDGET_UI_OBJ = $(patsubst $(REMOVE_FRIEND_WIDGET_UI_SRC_DIR)/%.c, $(REMOVE_FRIEND_WIDGET_UI_OBJ_DIR)/%.o, $(REMOVE_FRIEND_WIDGET_UI_C_FILES))

WINDOW_MANAGER_OBJ = $(patsubst $(WINDOW_MANAGER_SRC_DIR)/%.c, $(WINDOW_MANAGER_OBJ_DIR)/%.o, $(WINDOW_MANAGER_C_FILES))

EXTERNAL_TESTCLIENT_OBJ = $(patsubst $(EXTERNAL_SRC_DIR)%.c, $(EXTERNAL_OBJ_DIR)%.o, $(EXTERNAL_TESTCLIENT_C_FILES))

EXTERNAL_USER_OBJ = $(patsubst $(EXTERNAL_SRC_DIR)%.c, $(EXTERNAL_OBJ_DIR)%.o, $(EXTERNAL_USER_C_FILES))

EXTERNAL_SEND_OBJ = $(patsubst $(EXTERNAL_SRC_DIR)%.c, $(EXTERNAL_OBJ_DIR)%.o, $(EXTERNAL_SEND_C_FILES))

ALL_OBJS = $(APPLICATION_MANAGER_OBJ) $(NETWORK_SERVICE_OBJ) $(CREDENTIAL_SERVICE_OBJ) $(LOGIN_WINDOW_UI_OBJ) $(EXTERNAL_TESTCLIENT_OBJ) $(EXTERNAL_USER_OBJ) $(EXTERNAL_SEND_OBJ) $(MESSAGE_SERVICE_OBJ) $(FRIEND_REQUEST_HANDLER_OBJ) $(FRIEND_LIST_UI_OBJ) $(WINDOW_MANAGER_OBJ) $(CHAT_WINDOW_UI_OBJ) $(FRIEND_REQUEST_WIDGET_UI_OBJ)

# Compiling files
all: GuiApp 

# Executable
GuiApp: $(ALL_OBJS)
	$(CC) $(LFLAGS) -g $(ALL_OBJS) -o guiapp

$(APPLICATION_MANAGER_OBJ_DIR)/%.o: $(APPLICATION_MANAGER_SRC_DIR)/%.c $(wildcard APPLICATION_MANAGER_SRC_DIR*.h)
	$(CC) $(CFLAGS) -c -g $< -o $@

$(CHAT_WINDOW_UI_OBJ_DIR)/%.o: $(CHAT_WINDOW_UI_SRC_DIR)/%.c $(wildcard CHAT_WINDOW_UI_SRC_DIR*.h)
	$(CC) $(CFLAGS) -c -g $< -o $@

$(CREDENTIAL_SERVICE_OBJ_DIR)/%.o: $(CREDENTIAL_SERVICE_SRC_DIR)/%.c $(wildcard CREDENTIAL_SERVICE_SRC_DIR*.h)
	$(CC) $(CFLAGS) -c -g $< -o $@

$(FRIEND_LIST_UI_OBJ_DIR)/%.o: $(FRIEND_LIST_UI_SRC_DIR)/%.c $(wildcard FRIEND_LIST_UI_SRC_DIR*.h)
	$(CC) $(CFLAGS) -c -g $< -o $@

$(FRIEND_REQUEST_HANDLER_OBJ_DIR)/%.o: $(FRIEND_REQUEST_HANDLER_SRC_DIR)/%.c $(wildcard FRIEND_REQUEST_HANDLER_SRC_DIR*.h)
	$(CC) $(CFLAGS) -c -g $< -o $@

$(FRIEND_REQUEST_WIDGET_UI_OBJ_DIR)/%.o: $(FRIEND_REQUEST_WIDGET_UI_SRC_DIR)/%.c $(wildcard FRIEND_REQUEST_WIDGET_UI_SRC_DIR*.h)
	$(CC) $(CFLAGS) -c -g $< -o $@

$(LOGIN_WINDOW_UI_OBJ_DIR)/%.o: $(LOGIN_WINDOW_UI_SRC_DIR)/%.c $(wildcard LOGIN_WINDOW_UI_SRC_DIR*.h)
	$(CC) $(CFLAGS) -c -g $< -o $@

$(MESSAGE_SERVICE_OBJ_DIR)/%.o: $(MESSAGE_SERVICE_SRC_DIR)/%.c $(wildcard MESSAGE_SERVICE_SRC_DIR*.h)
	$(CC) $(CFLAGS) -c -g $< -o $@

$(NETWORK_SERVICE_OBJ_DIR)/%.o: $(NETWORK_SERVICE_SRC_DIR)/%.c $(wildcard NETWORK_SERVICE_SRC_DIR*.h)
	$(CC) $(CFLAGS) -c -g $< -o $@

$(REMOVE_FRIEND_WIDGET_UI_OBJ_DIR)/%.o: $(REMOVE_FRIEND_WIDGET_UI_SRC_DIR)/%.c $(wildcard REMOVE_FRIEND_WIDGET_UI_SRC_DIR*.h)
	$(CC) $(CFLAGS) -c -g $< -o $@

$(WINDOW_MANAGER_OBJ_DIR)/%.o: $(WINDOW_MANAGER_SRC_DIR)/%.c $(wildcard WINDOW_MANAGER_SRC_DIR*.h)
	$(CC) $(CFLAGS) -c -g $< -o $@

$(EXTERNAL_OBJ_DIR)/%.o: $(EXTERNAL_SRC_DIR)/%.c $(wildcard EXTERNAL_SRC_DIR*.h)
	$(CC) $(CFLAGS) -c -g $< -o $@

# Removing all files	
clean:
	rm -f *.o $(APPLICATION_MANAGER_OBJ_DIR)/*.o $(CHAT_WINDOW_UI_OBJ_DIR)/*.o $(CREDENTIAL_SERVICE_OBJ_DIR)/*.o $(FRIEND_LIST_UI_OBJ_DIR)/*.o $(FRIEND_REQUEST_HANDLER_OBJ_DIR)/*.o $(LOGIN_WINDOW_UI_OBJ_DIR)/*.o $(MESSAGE_SERVICE_OBJ_DIR)/*.o $(NETWORK_SERVICE_OBJ_DIR)/*.o $(REMOVE_FRIEND_WIDGET_UI_OBJ_DIR)/*.o $(WINDOW_MANAGER_OBJ_DIR)/*.o $(FRIEND_REQUEST_WIDGET_UI_OBJ_DIR)/*.o
	rm -f *.o $(EXTERNAL_OBJ_DIR)/*.o
	rm -f guiapp

