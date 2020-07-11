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
#define PORT 13 // port of daytime server

using namespace std;

int main(int argc, char *argv[])
{
  // define your variables here
	hostent* name1;
	in_addr** array;
	int s; int c;
  sockaddr_in server;
  char buf[BUFLEN] = {'0'};

  // check that there are enough parameters
  if (argc != 2)
    {
      fprintf(stderr, "Usage: mydaytime <hostname>\n");
      exit(-1);
    }

  // Write your code here

    name1 = gethostbyname(argv[1]);
    if(name1 == NULL) //whether or not hostname works
      {
        cout<<"Error. Incorrect webaddress.";
        return 0;
      }

    array = (in_addr**)name1->h_addr_list;


    s = socket(AF_INET, SOCK_STREAM, 0); //whether or not socket is created
    if(s < 0)
    {
      cout<<"Error. Socket not created.";
      return 0;
    }

    server.sin_family = AF_INET;
    server.sin_addr = *array[0];
    server.sin_port = htons(PORT);

    c = connect(s, (struct sockaddr*)&server, sizeof(server));

    if(c < 0) //whether or not socket is connected
    {
        cout<<"Error. Socket not connected";
        return 0;
    }

    if(read(s , buf, BUFLEN) < 0) //whether or not server responds
      {
        cout<<"Error. Time not received";
        return 0;
      }
    
    /*for(int i = 0; i < BUFLEN; i++)
    {
    	if(buf[i] !=  '0')
    		{cout<<buf<<endl;}
    }*/
    cout<<buf<<endl;

  return 0;
}