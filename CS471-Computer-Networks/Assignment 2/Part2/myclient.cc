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
		fprintf(stderr, "Usage: simpleclient <hostname> <port>\n");
		exit(-1);
	}

	cout<<"Running client..."<<endl;
	cout<<"Will try to connect to "<<argv[1]<<" at port "<<argv[2]<<endl;

	hostent* host = gethostbyname(argv[1]);
	if(host == NULL)
	{
		cout<<"Error. Incorrect webaddress.\n";
		return 0;
	}

	cout<<".. creating local connector socket"<<endl;
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock < 0)
	{
		cout<<"Error. Socket not created.\n";
		return 0;
	}

	int port = stoi(argv[2]);
	sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_port =  htons(port);
	server.sin_addr.s_addr =  INADDR_ANY;

	int c = connect(sock, (struct sockaddr*)&server, sizeof(server));

	cout<<".. connecting socket to "<<argv[1]<<":"<<argv[2]<<endl;

	if(c < 0) //whether or not socket is connected
	{
		cout<<"Error. Socket not connected\n";
		return 0;
	}

	char recvbuf[BUFLEN] = {'\0'};
	char sendbuf[BUFLEN] = {'\0'};
	bool sentinel = true;
	recv(sock, recvbuf, BUFLEN, 0);

	cout<<".. connection established\n\n";

	cout<<recvbuf<<endl;

	while(true)
	{
		memset(recvbuf, '\0', BUFLEN);
		memset(sendbuf, '\0', BUFLEN);
		cout<<"c: ";
		fgets(sendbuf, BUFLEN, stdin);
		int count = strlen(sendbuf);

		sendbuf[count] = '\n';

		send(sock, sendbuf, strlen(sendbuf), 0);
		if((sendbuf[0] == 'e' || sendbuf[0] == 'E') && (sendbuf[1] == 'x' || sendbuf[1] == 'X') && (sendbuf[2] == 'i' || sendbuf[2] == 'I') && (sendbuf[3] == 't' || sendbuf[3] == 'T') && recvbuf[4] == '\n')
		{
			recv(sock, recvbuf, BUFLEN, 0);
			cout<<recvbuf<<endl;
			close(sock);
			return 0;
		}
		else
		{
			recv(sock, recvbuf, BUFLEN, 0);
			cout<<recvbuf<<endl<<endl;
		}
	}

	// close(sock);
	return 0;
}