#include <iostream>
#include <stdio.h> // basic I/O
#include <stdlib.h>
#include <sys/types.h> // standard system types
#include <netinet/in.h> // Internet address structures
#include <sys/socket.h> // socket API
#include <arpa/inet.h>
#include <netdb.h> // host to IP resolution
#include <string.h>
#include <unistd.h>

#define HOSTNAMELEN 40 // maximal host name length; can make it variable if you want
#define BUFLEN 1024 // maximum response size; can make it variable if you want
// #define PORT 13 // port of daytime server

using namespace std;

int main(int argc, char *argv[])
{
	if(argc != 3)
	{
		fprintf(stderr, "Usage: myserver <hostname> <portnumber between 1024 and 65535>\n");
		exit(-1);
	}

	cout<<".. creating local connector socket"<<endl;
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock < 0)
	{
		cout<<"Error. Socket not created.\n";
		return 0;
	}

	int port = stoi(argv[2]);
	sockaddr_in server, client;
	server.sin_family = AF_INET;
	server.sin_port =  htons(21070);
	server.sin_addr.s_addr =  INADDR_ANY;

	cout<<".. binding socket to port"<<":"<<to_string(21070)<<endl;
	int b =  bind(sock, (struct sockaddr*)&server, sizeof(server));
	if(b < 0)
	{
		cout<<"Error. Socket not bound.\n";
		return 0;
	}

	listen(sock, 1);

	cout<<".. listening"<<endl;
	char recvbuf[BUFLEN] = {'\0'};
	
	while(true)
	{
		memset(recvbuf, '\0', BUFLEN);
		socklen_t l = sizeof(client);
		cout<<".. accepting client"<<endl;
		int clientsock = accept(sock, (sockaddr*) &client, &l);
		if(clientsock < 0)
		{
			cout<<"Error. Client not accepted\n";
			return 0;
		}

		cout<<"client connected\n";

		send(clientsock, "Hello", 11, 0);
		bool sentinel =  true;

		while(sentinel)
		{
			memset(recvbuf, '\0', BUFLEN);
			cout<<"c: ";
			recv(clientsock, recvbuf, BUFLEN, 0);
			send(clientsock, "Command received", 16, 0);

			if((recvbuf[0] == 'e' || recvbuf[0] == 'E') && (recvbuf[1] == 'x' || recvbuf[1] == 'X') && (recvbuf[2] == 'i' || recvbuf[2] == 'I') && (recvbuf[3] == 't' || recvbuf[3] == 'T') && recvbuf[4] == '\n')
			{
				sentinel = false;
				close(clientsock);
			}

			cout<<recvbuf<<endl;
		}

		cout<<".. disconnecting"<<endl;
		cout<<".. connection disconnected"<<endl;
		cout<<".. server listening for new connection"<<endl;
	}

	close(sock);

	return 0;
}