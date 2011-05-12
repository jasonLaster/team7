#ifndef SOCKET
#define SOCKET

#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MAX_CONNECTS 2

typedef struct server Server;
struct server {

    int sockfd, newsockfd, sockfd_max, n;
    fd_set fdset, read_fds;
    socklen_t clilen;
    char buffer[256];
    struct sockaddr_in serv_addr, cli_addr;

}; 

void error(const char *msg);
Server* server_new(int port_num);
void socket_accept(Server *server);
/*void open_socket(Server *server);
void bind_socket(Server *server , int port_num);
void listen_socket(Server *server);*/
void socket_accept(Server *server);
void select_socket(Server *server);
void socket_send(Server *server, int sock_num);

#endif
