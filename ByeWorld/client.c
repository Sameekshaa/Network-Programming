#include <stdio.h> // printf scanf fgets fputs
#include <stdlib.h> // exit
#include <string.h> // bzero
#include <errno.h>
#include <sys/socket.h> // socket bind listen read write close
#include <sys/types.h>
#include <unistd.h>
#include <netinet/in.h> // struct sockaddr_in
#include <arpa/inet.h> // socklen_t

#define PORT 8888
#define BUFFSIZE 1024

typedef struct sockaddr SA;
// command line argument
int main(int argc, char** argv) {
  int sockfd, pton, connectvalue, noofbyteread, closevalue;
  char buff[BUFFSIZE+1];
  struct sockaddr_in serverinfo;
// socket [int socket(int domain, int type, int protocolvalue)]
  sockfd = socket(AF_INET, SOCK_STREAM, 0); 
  if (sockfd < 0) {
    printf("Error creating socket\n");
    exit(EXIT_FAILURE);
  }
  printf("Socket created\n");

  memset(&serverinfo, 0, sizeof(serverinfo));
  serverinfo.sin_family = AF_INET;
  serverinfo.sin_port = htons(PORT);
  pton = inet_pton(AF_INET, "192.168.1.91", &serverinfo.sin_addr);
  if (pton < 0) {
    printf("Error while converting presentation to network\n");
    exit(EXIT_FAILURE);
  }
  // connect [int connect(int sockfd, struct sockaddr* address, socklen_t addresssize)]
  connectvalue = connect(sockfd, (struct sockaddr*) &serverinfo, sizeof(serverinfo)); 
  if (connectvalue < 0) {
    printf("Connection error\n");
    exit(EXIT_FAILURE);
  }
  noofbyteread = read(sockfd, buff, BUFFSIZE);
  buff[noofbyteread] = 0;
  printf("No of byte read: %d\n", noofbyteread);
  printf("Server message: %s\n", buff);
//
// read/write [int read(int sockfd, char* buff, int buffsize)]
// [int write(int sockfd, char* msg, int msgsize)]
//
// close [int close(int sockfd)]
  closevalue = close(sockfd);
  if (closevalue < 0) {
    printf("Error while closing\n");
    exit(EXIT_FAILURE);
  }
  printf("Closed successfully\n");
  return 0;
} 