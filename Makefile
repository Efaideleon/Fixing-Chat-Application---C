# SOURCE MAKEFILE
# Roll Two Die
# VersionNo: 0.1
# VsCreator: Justin Kim

# GTK Compiler Flags 
GTKINC  = `pkg-config --cflags gtk+-2.0` 
GTKLIBS = `pkg-config --libs gtk+-2.0`

#Debug Flags
DEBUG = -g -DDEBUG
CDEBUG = -g -DDEBUG -DCDEBUG

#Compiling Flags 
CFLAGS  = -Wall -ansi -std=c99 $(GTKINC) -c -Wno-deprecated-declarations
LFLAGS  = -Wall -ansi -std=c99 $(GTKLIBS) -Wno-deprecated-declarations

all: Server Client

#---- Object Compilation ----
user.o: user.c user.h GlobalDefs.h
	gcc $(CFLAGS) -g user.c -o user.o

Client.o: TestClient.h TestClient.c GlobalDefs.h
	gcc $(CFLAGS) -g TestClient.c -o Client.o
	
send.o: send.c send.h user.h GlobalDefs.h
	gcc $(CFLAGS) -g send.c -o send.o
	
GTK.o: GTK.c user.h TestClient.h GlobalDefs.h
	gcc $(CFLAGS) -g GTK.c -o GTK.o

ServerGTK.o: TestClient.h TestServerGTK.c TestServer.h GlobalDefs.h send.h user.h
	gcc $(CFLAGS) -g TestServerGTK.c -o ServerGTK.o  
	
#---- Executable Compilation
Server: ServerGTK.o send.o user.o
	gcc $(LFLAGS) -g ServerGTK.o send.o user.o -o ChatServer
	
Client: GTK.o user.o send.o Client.o
	gcc $(LFLAGS) -g GTK.o user.o send.o Client.o -o ChatClient

#------------------------------------------------------------------------------------
clean: 
	rm -f *.o
	rm -f TestChatClient
	rm -f TestChatServer
	rm -f TestChatClientText
	rm -f TestChatServerText
	rm -f ChatClient
	rm -f ChatServer
	rm -f ChatClientText
	rm -f ChatServerText
 
	
