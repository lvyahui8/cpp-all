include ../Make.defines.linux
ROOT 	= ..

all: server.app client.app

server.app:opend.o server_main.o
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS) $(LDLIBS) 
client.app:open.o client_main.o
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS) $(LDLIBS) 

clean:
	-rm -f *.o *.app 
