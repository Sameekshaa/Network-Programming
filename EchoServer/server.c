#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8881
#define LISTENQ 10
#define BUFFSIZE 1024

typedef struct sockaddr SA;

int main(int argc, char **argv)
{
	int sockfd, new_sockfd;
	int n;
	struct sockaddr_in address, clientaddress;
	socklen_t len;
	char buff[BUFFSIZE];

	// creating socket
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
	{
		printf("error creating socket\n");
		exit(EXIT_FAILURE);
	}
	bzero(&address, sizeof(address));
	// assigning address
	address.sin_addr.s_addr = htonl(INADDR_ANY);
	address.sin_port = htons(PORT);
	address.sin_family = AF_INET;

	// binding
	if (bind(sockfd, (SA *)&address, sizeof(address)) == -1)
	{
		printf("error while binding\n");
		exit(EXIT_FAILURE);
	}

	// listen
	listen(sockfd, LISTENQ);
	printf("listeing on port: %d\n", PORT);

	// loop accept
	while (1)
	{
		memset(buff, 0, sizeof(buff));
		// printf("inside loop\n");
		len = sizeof(clientaddress);
		// printf("len %d\n", len);
		new_sockfd = accept(sockfd, (SA *)&clientaddress, &len);
		// printf("new sock %d\n", new_sockfd);
		if (new_sockfd < 0)
		{
			printf("cannot accept\n");
			exit(EXIT_FAILURE);
		}
		// printf("helloworld\n");
		printf("Connection from %s, port %d\n", inet_ntop(AF_INET, &clientaddress.sin_addr, buff, sizeof(buff)), ntohs(clientaddress.sin_port));
		// recv is non blocking
		while ((n = read(new_sockfd, buff, sizeof(buff))) > 0)
		{
			printf("%d bytes received\n", n);
			buff[n] = 0;
			printf("Client send: %s\n", buff);
			send(new_sockfd, buff, n, 0);
			memset(buff, 0, sizeof(buff));
		}
		// close(new_sockfd);
	}
	close(sockfd);
	return 0;
}
