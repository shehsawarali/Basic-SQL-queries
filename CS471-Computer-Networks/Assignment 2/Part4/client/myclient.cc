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
#include <dirent.h>
#include <fstream>
#include <vector>

#define HOSTNAMELEN 40 // maximal host name length; can make it variable if you want
#define BUFLEN 1024 // maximum response size; can make it variable if you want
// #define PORT 13 // port of daytime server

using namespace std;


bool fileexist(string name) 
{
    ifstream data(name.c_str());
    return data.good();
}


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
		// send(sock, sendbuf, strlen(sendbuf), 0);
		for(int i = 0; i < strlen(sendbuf); i++)
		{
			sendbuf[i] = tolower(sendbuf[i]);
		}


		if((sendbuf[0] == 'e') && (sendbuf[1] == 'x') && (sendbuf[2] == 'i') && (sendbuf[3] == 't'))
		{
			send(sock, sendbuf, strlen(sendbuf), 0);
			recv(sock, recvbuf, BUFLEN, 0);
			cout<<recvbuf<<endl;
			close(sock);
			return 0;
		}

		else if(sendbuf[0] == 'l' && sendbuf[1] == 'i' && sendbuf[2] == 's' && sendbuf[3] == 't')
		{
			if(sendbuf[5] == 's' && sendbuf[6] == 'e' && sendbuf[7] == 'r' && sendbuf[8] == 'v' && sendbuf[9] == 'e' && sendbuf[10] == 'r')
			{
				send(sock, sendbuf, strlen(sendbuf), 0);
				recv(sock, recvbuf, BUFLEN, 0);
				cout << "Server: File List"<<endl;
				cout<<recvbuf<<endl;
			}
			else if(sendbuf[5] == 'c' && sendbuf[6] == 'l'  && sendbuf[7] == 'i'  && sendbuf[8] == 'e' && sendbuf[9] == 'n' && sendbuf[10] == 't')
			{
				cout << "Client: File List" << endl;

				DIR* dirp = opendir("./");
			    struct dirent * dp;
			    while((dp = readdir(dirp)) != NULL)
			    {
			        cout << dp->d_name << endl;
			    }
			    closedir(dirp);
			}
		}
		else if(sendbuf[0] == 'c' && sendbuf[1] == 'r' && sendbuf[2] == 'e' && sendbuf[3] == 'a' && sendbuf[4] == 't' && sendbuf[5] == 'e')
		{
			if(sendbuf[7] == 'c' && sendbuf[8] == 'l'  && sendbuf[9] == 'i'  && sendbuf[10] == 'e' && sendbuf[11] == 'n' && sendbuf[12] == 't')
			{
				int i = 14; string file = "";
				while(sendbuf[i] != '\0')
				{
					file += sendbuf[i];
					i++;
				}

				if(fileexist(file))
				{
					cout<<"Client: The file "<<file<<" already exists"<<endl;
				}
				else
				{
					ofstream data;
	                data.open(file.c_str());
	                data.close();
	                cout<<"Client: The file "<<file<<" has been created"<<endl;
				}
			}
			else if(sendbuf[7] == 's' && sendbuf[8] == 'e' && sendbuf[9] == 'r' && sendbuf[10] == 'v' && sendbuf[11] == 'e' && sendbuf[12] == 'r')
			{
				send(sock, sendbuf, strlen(sendbuf), 0);
				recv(sock, recvbuf, BUFLEN, 0);
				cout<<recvbuf<<endl;
			}
		}
		else if(sendbuf[0] == 'd' && sendbuf[1] == 'e' && sendbuf[2] == 'l' && sendbuf[3] == 'e' && sendbuf[4] == 't' && sendbuf[5] == 'e')
		{
			if(sendbuf[7] == 'c' && sendbuf[8] == 'l'  && sendbuf[9] == 'i'  && sendbuf[10] == 'e' && sendbuf[11] == 'n' && sendbuf[12] == 't')
			{
				int i = 14; char file[BUFLEN] = {'\0'}; int count = 0;
				while(sendbuf[i] != '\0')
				{
					file[count] += sendbuf[i];
					i++;
					count++;
				}

				if(fileexist(file))
				{
					int check = remove(file);
					if(check == 0)
					{
						cout<<"Client: The file "<<file<<" has been deleted"<<endl;
					}
					else
					{
						cout<<"Client: Error: file "<<file<<" not deleted"<<endl;
					}
				}
				else
				{
	                cout<<"Client: The file "<<file<<" does not exist"<<endl;
				}
			}
			else if(sendbuf[7] == 's' && sendbuf[8] == 'e' && sendbuf[9] == 'r' && sendbuf[10] == 'v' && sendbuf[11] == 'e' && sendbuf[12] == 'r')
			{
				send(sock, sendbuf, strlen(sendbuf), 0);
				recv(sock, recvbuf, BUFLEN, 0);
				cout<<recvbuf<<endl;
			}
		}
		else if(sendbuf[0] == 'r' && sendbuf[1] == 'e' && sendbuf[2] == 'c' && sendbuf[3] == 'e' && sendbuf[4] == 'i' && sendbuf[5] == 'v' && sendbuf[6] == 'e')
		{
			int i = 8; string file = "";
			while(sendbuf[i] != '\0')
			{
				file += sendbuf[i];
				i++;
			}
			if(fileexist(file))
			{
				cout<<"Client: File already exists. Replace or keep the old copy?"<<endl;
			}
			else
			{
				send(sock, sendbuf, strlen(sendbuf), 0);
			}
		}
		else if(sendbuf[0] == 's' && sendbuf[1] == 'e' && sendbuf[3] == 'n' && sendbuf[4] == 'd')
		{
			int i = 5; string file = "";
			while(sendbuf[i] != '\0')
			{
				file += sendbuf[i];
				i++;
			}

			if(fileexist(file))
			{
				cout<<"Client: File does not exist"<<endl;
			}
			else
			{
				//send
			}
		}
		else
		{
			send(sock, sendbuf, strlen(sendbuf), 0);
			recv(sock, recvbuf, BUFLEN, 0);
			cout<<recvbuf<<endl;
		}
	}

	// close(sock);
	return 0;
}