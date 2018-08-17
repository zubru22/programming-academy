/* A simple server in the internet domain using TCP. The port number is passed as an argument */
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#define MAX_EVENTS 10

// Display error message if system call fails
void error(char *msg)
{
	perror(msg);
	exit(1);
}

void do_use_fd(int socket)
{
	printf("Goodbye!\n");
}

int main()
{
	const int message_len = 256;
	char user_says[message_len];
	int server_socket;
	int client_socket;
	int epoll_fd;
	int nfds;
	int status;
	struct sockaddr_in server_address;
	struct epoll_event ev;
	struct epoll_event events[MAX_EVENTS];
	
	// Create the server socket
	server_socket = socket(AF_INET, SOCK_STREAM, 0);
	
	// Define the server address
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(9000);
	server_address.sin_addr.s_addr = INADDR_ANY;
	
	// Bind the socket to our specified IP and port
	bind(server_socket, (struct sockaddr *) &server_address, (int) sizeof(server_address));
	
	listen(server_socket, 5);
	
	// Create epoll file descriptor
	epoll_fd = epoll_create1(0);
	if (epoll_fd == -1)
		error("Error while creating epoll_fd");
		
	ev.events = EPOLLIN;
	ev.data.fd = server_socket;
	if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, server_socket, &ev) == -1)
		error("Error epoll_ctl: server_socket");
	
	while(1)
	{
		nfds = epoll_wait(epoll_fd, events, MAX_EVENTS, -1);
		if (nfds == -1)
			error("Error with epoll_wait");
			
		for (int n = 0; n < nfds; ++n)
		{
			if (events[n].data.fd == server_socket)
			{	
				// (struct sockaddr *) &client_address, sizeof(struct sockaddr_in)
				client_socket = accept(server_socket, NULL, NULL);
				if (client_socket == -1)
				{
					printf("Errno: %d\n", errno);
					error("Error with accept");
				}	
				status = fcntl(client_socket, F_SETFL, fcntl(client_socket, F_GETFL, 0) | O_NONBLOCK);
				if (status == -1)
					error("Error while calling fcntl");
				
				ev.events = EPOLLIN | EPOLLET;
				ev.data.fd = client_socket;
				if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, client_socket, &ev) == -1)
					error("Error with epoll_ctl: client_socket");
	
			}
			else
			{
				recv(client_socket, &user_says, sizeof(user_says), 0);
				//recv(client_socket, &user_message, sizeof(user_message), 0);
				printf("%s\n", user_says);
			}
		}
	}
	
	// Close the socket
	close(server_socket);
	
	return 0;
}
