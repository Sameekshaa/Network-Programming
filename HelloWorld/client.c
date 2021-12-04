#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define PORT 8888
#define MAXLINE 1024

// socket()
// --
// connect()
// --
// read()/write()
// close()

int main(int argc, char const *argv[])
{
    int sockfd, checkConnect;
    char buff[MAXLINE];
    socklen_t len;

    // int socket(int addrFamily/Domain, int sockType, int protocolValue);
    sockfd = socket(AF_INET, SOCK_STREAM, 0); //socket le address family(int), socket type(int) ra protocol value(int) linxa ani socket file descripter(int) return garxa 

    if (sockfd == -1){
        printf("Socket creation failed\n");
        exit(EXIT_FAILURE);
    }
    printf("Socket created successfully \n");

    struct sockaddr_in servaddr;

    memset(&servaddr, 0, sizeof(servaddr)); // yo memory address dekhi - yo memory address ko value lai 0 banaune sizeof(servaddr)
    servaddr.sin_port = htons(PORT);
    servaddr.sin_family = AF_INET; // address family assign gareko

    // int inet_pton(int addrFamily, char *IPaddress, void * servaddr);

    inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr); // presentation layer ko IP address lai network layer(0's and 1's) ma set gareko, &servaddr.sin_addr ma

    //int connect(int sockfd, const struct sockaddr *servaddr, socklen_t len)
    len = sizeof(servaddr);
    checkConnect = connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr) );
    // connect le connect to server
    // sockaddr_in le IPV4 ko lagi ho but connect ko function prototype ma sockaddr support garxa which is generic(can be applicable to both IPV4 and IPv6), so typecast is done as they have diff datatypes.

    // int recv(int sockfd, void* buff (bhado), int buffSize, int flags )
    memset(&buff, 0, sizeof(buff));
    int dataSize = recv(sockfd, buff, sizeof(buff), 0); //recv() or read() le ...yeti bytes of data paye vanera return garxa
    // int dataSize = recv(sockfd, buff, 5, 0);
    // receive gareko kura buff vanne bhado ma rakhdinxa jasko capacity sizeof(buff) le dinxa

    printf("Message received!!!\n");
    printf("The message is %s \n",buff);
    printf("%d bytes message received.\n", dataSize); //dataSize ma server le jati byte of data send gareko xa send() ma teti aauxa 
    // HelloWorld! ma 11 byte so 
    printf("%d bhado ko capacity.\n", sizeof(buff)); //1024 as size of character is 1byte, we have 1024 characters size in total.

    close(sockfd); //closes the socket and returns status.

    return 0;
}

