#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8881
#define BUFFSIZE 1024

typedef struct sockaddr SA;

int main(int argc, char **argv)
{
	int sockfd, n;
	struct sockaddr_in address;
	char buff[BUFFSIZE + 1];
	char msg[BUFFSIZE];

	// creating socket
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
	{
		printf("error creating socket\n");
		exit(EXIT_FAILURE);
	}
	// assigning address port
	address.sin_port = htons(PORT);
	address.sin_family = AF_INET;
	inet_pton(AF_INET, "127.0.0.1", &address.sin_addr);
	connect(sockfd, (SA *)&address, sizeof(address));
	printf("Enter the message: ");
	fgets(msg, BUFFSIZE, stdin);
	printf("Sending msg to the server: %s\nSizeof message: %ld\n", msg, strlen(msg));

	send(sockfd, msg, strlen(msg), 0);
	// printf("Sending successful: %s\n", msg);

	n = recv(sockfd, buff, BUFFSIZE, 0);
	buff[n] = 0;
	printf("\n");
	printf("Server sends the message to client: %s\n", buff);

	close(sockfd);
	return 0;
}
