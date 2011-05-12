#include "socket.h"
//http://www.tenouk.com/Module41.html

static void listen_socket(Server *server);
static void open_socket(Server *server);
static void bind_socket(Server *server, int port_num);

void error(const char *msg) {
    perror(msg);
    exit(1);
}

Server* server_new(int port_num) { 

    Server *server = (Server*) malloc (sizeof(Server));
    open_socket(server);

    //set address with zeroes
    bzero((char *) &(server -> serv_addr), sizeof(server -> serv_addr));
    FD_ZERO(&(server -> fdset)); //clearing both sets
    FD_ZERO(&(server -> read_fds));

    bind_socket(server, port_num);
    listen_socket(server);
    return server;
}

static void open_socket(Server *server) {
    if ((server -> sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) 
        error("ERROR in Opening Socket");
    printf("Opening Socket ... Check\n");
}

static void bind_socket(Server *server, int port_num) {

     server->serv_addr.sin_family = AF_INET;
     server->serv_addr.sin_addr.s_addr = INADDR_ANY;
     server->serv_addr.sin_port = htons(port_num);

     if (bind(server -> sockfd, (struct sockaddr *) &(server -> serv_addr), sizeof(server -> serv_addr)) < 0) 
              error("ERROR on binding");
     printf("Binding ... Check\n");
}

static void listen_socket(Server *server) {

     if (listen(server -> sockfd, MAX_CONNECTS) == -1)
         error("ERROR in Listening");
     printf("Listening ... Check\n");

     FD_SET(server -> sockfd, &(server -> fdset));
     server -> sockfd_max = server->sockfd;
}

void select_socket(Server *server) {
     if(select(server -> sockfd_max+1, &(server -> read_fds), NULL, NULL, NULL) == -1)
          error("ERROR in Server Selecting\n");
     printf("Selecting ... Check\n");
}

void socket_accept (Server *server) {
    server -> clilen = sizeof(server -> cli_addr);
         if((server -> newsockfd = accept(server -> sockfd,(struct sockaddr *) &(server -> cli_addr), &(server -> clilen))) == -1)
              perror("ERROR in Server Accepting\n");
         else {
             if(server -> sockfd_max > 2 + MAX_CONNECTS) {
                 if(send(server -> sockfd_max + 1, "\nToo Many Connections\n", 21, 0) == -1)
                        perror("ERROR Sending");
                 close(server -> sockfd_max + 1);
             }
             else {
             printf("Accepting ... Check\n");
             FD_SET((server -> newsockfd), &(server -> fdset));
             if (server -> newsockfd > server -> sockfd_max)
                  server -> sockfd_max = server -> newsockfd;  
             }
    }
}

void socket_send (Server *server, int sock_num) {
    bzero(server -> buffer,256);
    if ((server -> n = recv(sock_num, server -> buffer, 256, 0)) < 1) {
          if (server -> n < 0)
                  perror("ERROR Reading from Socket");
          else if (server -> n == 0)
                  printf("Socket %d hung up\n", sock_num);
          close(sock_num);
          FD_CLR(sock_num, &(server -> fdset));
    }
    else
          for(int j = 0; j <= server -> sockfd_max; j ++)
                 if(FD_ISSET(j, &(server -> fdset)))
                         if(j != sock_num && j != server -> sockfd) {
                                if(send(j, server -> buffer, 256, 0) == -1)
                                           perror("ERROR Sending");
                         }
}
