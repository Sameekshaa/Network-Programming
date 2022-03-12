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
#define LISTENQ 10
#define BUFFSIZE 1024

typedef struct sockaddr SA;
// command line argument
int main(int argc, char** argv) {
  int sockfd, bindvalue, listenvalue, new_sockfd, closevalue;
  socklen_t len;
  char msg[100] = "Bye world!!!";
  struct sockaddr_in address, clientinfo;
  // socket [int socket(int domain, int type, int protocolvalue)]
  sockfd = socket(AF_INET, SOCK_STREAM, 0); 
  if (sockfd < 0) {
    printf("Error creating socket\n");
    exit(EXIT_FAILURE);
  }
  printf("Socket created\n");

  memset(&address, 0, sizeof(address));
  address.sin_addr.s_addr = htonl(INADDR_ANY);
  address.sin_family = AF_INET;
  address.sin_port = htons(PORT);
  // bind [int bind(int sockfd, const struct sockaddr* address, socklen_t addresssize)]
  bindvalue = bind(sockfd, (SA*)&address, sizeof(address));
  if (bindvalue < 0) {
    printf("Binding error\n");
    exit(EXIT_FAILURE);
  }
  printf("Binding successful\n");
  //
  // listen [int listen(int sockfd, int backlog/listenq)]
  listenvalue = listen(sockfd, LISTENQ);
  if (listenvalue < 0) {
    printf("Listening error\n");
    exit(EXIT_FAILURE);
  }
  printf("Listening to the port: %d\n", PORT);
  while(1) {
    // accept [int accept(int sockfd, const struct sockaddr* fromadress, socklen_t* addresssize)]
    len = sizeof(clientinfo);
    new_sockfd = accept(sockfd, (SA*) &clientinfo, &len);

    // send(new_sockfd, msg, strlen(msg), 0);
    write(new_sockfd, msg, strlen(msg));
    //
    // read/write [int read(int sockfd, char* buff, int buffsize)]
    // [int write(int sockfd, char* msg, int msgsize)]
    //
    // close [int close(int sockfd)]
    closevalue = close(new_sockfd);
    if (closevalue < 0) {
      printf("Closing error\n");
      exit(EXIT_FAILURE);
    }
    printf("Closing successful\n");
  }
  closevalue = close(sockfd);
  if (closevalue < 0) {
    printf("Closing error\n");
    exit(EXIT_FAILURE);
  }
  printf("Closing outer successful\n");
} 