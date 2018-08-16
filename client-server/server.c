/* A simple server in the internet domain using TCP. The port number is passed as an argument */
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
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
	int sockfd, newsockfd; // file descriptors
	int portno; // port number on which server accepts connections
	int clilen; // size of address of the client, needed for the accept system call
	
	char buffer[256];
	struct sockaddr_in serv_addr, cli_addr;
	int n;
	
	if (argc < 2)
	{
		fprintf(stderr, "ERROR, no port provided\n");
		exit(1);
	}
	
	// System call to create new socket. AF_INET is internet domain, SOCK_STREAM is type of socket, third argument is the protocol chosen by operating system
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	
	if (sockfd < 0)
		error("ERROR opening socket");
	
	// Sets all values in a buffer to zero, first argument is pointer to the buffer and second is the size of the buffer
	bzero((char *) &serv_addr, sizeof(serv_addr));
	
	// The port number on which server will listen for connections (passed as argument), converted from string to integer
	portno = atoi(argv[1]);
	
	serv_addr.sin_family = AF_INET; // should be always set to symbolic constant AF_INET
	serv_addr.sin_port = htons(portno); // contains port number, it's necessary to convert this to network byte order using htons()
	/* Contains IP address of the host. For server code this will always be the IP address of the machine on which the server is running 
	 * and there is symbolic constant INADDR_ANY which gets this address */
	serv_addr.sin_addr.s_addr = INADDR_ANY; 
	
	/* System call binds socket to an address, in this case the address of current host and port number on which the server will run.
	 * It takes three arguments, the socket file descriptor, the address to which is bound and the size of the address to which it is bound.
	 * This can fail for number of reason but most obvious being that this socket is already in use on this machine. */
	if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
		error("ERROR on binding");
		
	 /* System call allows the proccess to listen on the socket for connections. 
	  * Second argument is the size of backlog queue - the number of connections that can be waiting while the process is handling a particular connection. 
	  * This should be set to 5, the maximum size permitted by most systems.
	  * If the first argument is valid socked this call cannot fail so the code doesn't check for errors */
	listen(sockfd, 5);
	
	/* The accept call causes the process to block until a client connects to the server. 
	 * Thus it wakes up the process when a connection from a client has been successfully established.
	 * It returns new file descriptor and all communication on this connection should be done using the new file descriptor.
	 * Second argument is reference pointer to the address of the client on the other end of the connection.
	 * Third argument is the size of this structure */
	clilen = sizeof(cli_addr);
	newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
	if (newsockfd < 0)
		error("ERROR on accept");
		
	/* Once a connection has been established, both ends can both read and write to the connection.
	 * Naturally, everything written by the client will be read by the server,
	 * and everything written by the server will be read by the client.
	 * This code simply writes a short message to the client. 
	 * The last argument of write is the size of the message */
	bzero(buffer, 256);
	n = read(newsockfd, buffer, 255);
	if (n < 0)
		error("ERROR writing to socket.");
	
	printf("Here is the message: %s\n", buffer);
		
	return 0;
}
