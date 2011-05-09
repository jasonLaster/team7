/* A simple server in the internet domain using TCP
   The port number is passed as an argument */

#include "socket.h"

int main(int argc, char *argv[]) {
     int port_num;
     Server *server;

     if (argc < 2) {
         fprintf(stderr,"ERROR, no port provided\n");
         exit(1);
     }

     //recieving port number;
     if ((port_num = atoi(argv[1])) == 0) {
         fprintf(stderr,"ERROR, Port Reserved or Invalid Port Number");
         exit(1);
     }
     
     server = server_new(port_num);
     while(1) {
         server -> read_fds = server -> fdset;
         select_socket(server);
         for ( int i = 0; i <= server -> sockfd_max ; i ++ ) {
              if(FD_ISSET(i, &(server -> read_fds))) {
                   if (i == (server -> sockfd)) {
                        server -> clilen = sizeof(server -> cli_addr);
                        socket_accept(server);
                   }
                   else 
                        socket_send(server, i);
              }
         }
     }
     return 0;
}

