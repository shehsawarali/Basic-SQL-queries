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

using namespace std;

int main(int argc, char *argv[])
{
  // define your variables here
	hostent* name1;
	in_addr** array;
	int i = 0;


  // check that there are enough parameters
  if (argc != 2)
    {
      fprintf(stderr, "Usage: mydns <hostname>\n");
      exit(-1);
    }

  // Address resolution stage by using gethostbyname()
    name1 = gethostbyname(argv[1]);

    if(name1 == NULL)
    	{cout<<"Error. Incorrect webaddress."; return 0;}
  // Write your code here!
    array = (in_addr**)name1->h_addr_list;
  // Print to standard output

    while(array[i] != NULL)
    {
    	cout<<inet_ntoa(*array[i])<<endl;
    	i++;
    }
  return 0;
}
