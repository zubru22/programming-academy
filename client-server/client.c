#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

// Display error message if system call fails
void error(char *msg)
{
	perror(msg);
	exit(1);
}

// Gets text from client, it can be either username or message to send
void get_text(char *promp_msg, char *string, int len)
{
	printf("%s", promp_msg);
	fgets(string, len, stdin);
	strtok(string, "\n");
}

int main()
{
	const int user_len = 30;
	const int message_len = 128;
	char user_name[user_len];
	char message[message_len];
	int network_socket;
	int connection_status;
	struct sockaddr_in server_address;
	
	// Specify server's socket
	network_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (network_socket == -1)
		error("Could not create network_socket");
	
	// Specify an address for the socket
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(9000);
	server_address.sin_addr.s_addr = INADDR_ANY;
	
	connection_status = connect(network_socket, (struct sockaddr *) &server_address, (int) sizeof(server_address));
	// Check for error with the connection
	if (connection_status == -1)
	{
		printf("Errno: %d\n", errno);
		error("Error while connecting.");
	}	
	
	get_text("Type in your username: ", user_name, sizeof(user_name));
	
	printf("Type in QUIT to quit.\n");
	while (strcmp(message, "QUIT"))
	{
		get_text("Message: ", message, sizeof(message));
		send(network_socket, message, sizeof(message), 0);
	}
	
	// Close the socket
	close(network_socket);
}
