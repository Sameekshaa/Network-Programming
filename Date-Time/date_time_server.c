// daytime server
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>

#define MAXLINE 1024
#define LISTENQ 10
typedef struct sockaddr SA;

int main(int argc, char **argv)
{
    int listenfd, connfd;
    struct sockaddr_in servaddr, cliaddr;
    char buffSize[MAXLINE];
    time_t ticks;
    int port;
    socklen_t len;
    int bindValue;

    // server listens the socket.
    listenfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); // IPPROTO_TCP or 0 for tcp socket

    port = atoi(argv[1]);

    bzero(&servaddr, sizeof(servaddr)); // resetting buffer

    // Set up address variables
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(port);

    // Binding socket to port address
    bindValue = bind(listenfd, (SA *)&servaddr, sizeof(servaddr));
    printf("Server is waiting for connection at port %d\t\n", port);

    if (bindValue < 0)
    {
        perror("Binding error");
    }

    // Listening socket
    listen(listenfd, LISTENQ);

    while (1)
    {
        len = sizeof(cliaddr);
        connfd = accept(listenfd, (SA *)&cliaddr, &len); // accepting connection from client

        ticks = time(NULL);
        snprintf(buffSize, sizeof(buffSize), "%s\r\n", ctime(&ticks));
        printf("%s\n", buffSize);

        write(connfd, buffSize, strlen(buffSize)); // write date and time to clients end

        // Close socket
        close(connfd);
    }
}