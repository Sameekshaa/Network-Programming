// socket()
//  bind()
//  listen()
//  accept()
//  read() + write()
//  close()

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>

#define PORT 8888
#define LISTENQ 10
#define BUFFERSIZE 1024

int main(int argc, char const *argv[])
{
    // int socket (int addressFamily, int type, int protocol)

    int sockfd;
    int new_sockfd;
    socklen_t len;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        printf("Socket Error \n");
        exit(EXIT_FAILURE);
    }
    printf("Socket creation successful \n");

    // int bind(int sockfd, const struct sockaddr *servaddr, socklen_t len)
    struct sockaddr_in servaddr;

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY); // l = 8bytes = 64bits
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);

    int checkBind = bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr));
    if (checkBind < 0)
    {
        printf("Bind failed \n");
        exit(1);
    }
    printf("Binding successful\n");

    // int listen(int sockfd, int LISENTQ)
    int checkListen = listen(sockfd, LISTENQ);

    if (checkListen < 0)
    {
        printf("Listenining failed");
        exit(1);
    }
    printf("Listening successful \n");

    // accept(int sockfd, struct sockaddr * clientAddress, socklen_t *clientAddressSize)
    struct sockaddr_in clientaddr; // for IPV4
    // unsigned len = sizeof(clientaddr); //address lina lai memory ma space allocate garna parxa
    // accept(sockfd,(struct sockaddr *)&clientaddr, (socklen_t *) &len);

    while (1)
    {
        len = sizeof(clientaddr); // address lina lai memory ma space allocate garna parxa
        memset(&clientaddr, 0, len);
        new_sockfd = accept(sockfd, (struct sockaddr *)&clientaddr, &len);

        if (new_sockfd < 0)
        {
            printf("Accepting failed.\n");
            exit(1);
        }
        printf("Accepting successful.\n");

        // read-write

        // printf("Now sending data using send() \n");
        // write(int sockfd, void *buff, size_t n)
        char buff[50] = "HelloWorld!";
        send(new_sockfd, (void *)&buff, strlen(buff), 0); // new_sockfd lai balla client ko address haru tha hunxa so yo use
        // send(new_sockfd, (void *)&buff, 10, 0);
        // send le buff vanne bhado ma vako data send garxa, client ma jasko size strlen(buff) le nikalxa ... here 11 bytes are sent

        close(new_sockfd);
    }
    close(sockfd);

    return 0;
}

// int sum (int a, int b){
//     return a + b;
// }

// int c = sum (2,3);