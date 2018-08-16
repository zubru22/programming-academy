/* A simple server in the internet domain using TCP. The port number is passed as an argument */
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Display error message if system call fails
void error(char *msg)
{
	perror(msg);
	exit(1);
}

int main(int argc, char *argv[])
{
	int sockfd, portno, n;
	struct sockaddr_in serv_addr; // will contain the address of the server to which we want to connect.
	struct hostent *server; // it defines host computer on the Internet
	
	/* All this code is the same as that in the server */
	char buffer[256];
    if (argc < 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }
    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");
    
    /* argv[1] contains the name of a host on the Internet, e.g. cheerios@cs.rpi.edu 
     * hostent takes a name as argument and returns a pointer to hostent containing information about that host.
     * The field char *h_addr contains the IP address.
     * If this structure is NULL, the system could not locate a host with this name. */    
	server = gethostbyname(argv[1]);
	if (server == NULL)
	{
		fprintf(stderr, "ERROR, no such host\n");
		exit(0);
	}
	
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy((char *) server->h_addr, (char *) &serv_addr.sin_addr.s_addr, server->h_length); // server->h_addr is string so we use bcopy()
	serv_addr.sin_port = htons(portno);
	
	/* The connect function is called by the client to establish a connection to the server.
	 * It takes three arguments, socket file descriptor, the address of the host to which it wants to connect (including port number)
	 * and the size of this address. Function return 0 on success and -1 if it fails */
	if (connect(sockfd, &serv_addr, sizeof(serv_addr)) < 0)
		error("ERROR connecting");
		
	printf("Please enter the message: ");
	bzero(buffer, 256);
	fgets(buffer, 255, stdin);
	n = write(sockfd, buffer, strlen(buffer));
	
	if (n < 0)
		error("ERROR writing to socket");
		
	printf("%s\n", buffer);
	
	return 0;
}
