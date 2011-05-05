/*
 * client.c
 *
 *  Created on: May 3, 2011
 *      Author: Drew
 */

#include "client.h"
#include "PsycheMacros.h"

int connect(int port) {
    int sockfd;
    struct sockaddr_in servaddr;
    char sendline[MAXLINE], recvline[MAXLINE];

    // Create a socket for the client
    // If sockfd<0 there was an error in the creation of the socket
    if ((sockfd = socket (AF_INET, SOCK_STREAM, 0)) <0) {

      perror("Problem in creating the socket");
      return(SOCKET_CREATE_ERROR);
    }

    // Creation of the socket
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(argv[1]); //what do we put here?
    servaddr.sin_port =  htons(SERV_PORT); //convert to big-endian order

    // Connection of the client to the socket
    if (connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0) {

      perror("Problem in connecting to the server");
      exit(SOCKET_CONNECT_ERROR);
    }

    while (fgets(sendline, MAXLINE, stdin) != NULL) {

        send(sockfd, sendline, strlen(sendline), 0);

        if (recv(sockfd, recvline, MAXLINE,0) == 0) {
            //error: server terminated prematurely
            perror("The server terminated prematurely");
            exit(4);
        }
        printf("%s", "String received from the server: ");
        fputs(recvline, stdout);
    }

    exit(0);
}
