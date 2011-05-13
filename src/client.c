/*
 * client.c
 *
 *  Created on: May 3, 2011
 *      Author: Drew
 */

#include "client.h"
#include "PsycheMacros.h"

Client *client_new(){
  Client *client;
  NEW(client, Client);
  return(client);
}

int client_connect(Client *client, char *address) {

    // Create a socket for the client
    // If sockfd<0 there was an error in the creation of the socket
    if ((client->sockfd = socket (AF_INET, SOCK_STREAM, 0)) <0) {

      perror("Problem in creating the socket");
      return(SOCKET_CREATE_ERROR);
    }

    // Creation of the socket
    memset(&(client->servaddr), 0, sizeof(client->servaddr));
    client->servaddr.sin_family = AF_INET;
    client->servaddr.sin_addr.s_addr = (inet_addr) (address); //what do we put here?
    client->servaddr.sin_port =  htons(SERV_PORT); //convert to big-endian order

    // Connection of the client to the socket
    if (connect(client->sockfd, (struct sockaddr *) &(client->servaddr), sizeof(client->servaddr)) < 0) {

      perror("Problem in connecting to the server");
      exit(SOCKET_CONNECT_ERROR);
    }

    fprintf(stdout, "Connecting to the server...check.\n");

    return(SOCKET_CONNECT_SUCCESS);
}

char *client_listen(Client *client){

  if (recv(client->sockfd, client->recvline, MAXLINE, 0) == 0) {
    //error: server terminated prematurely
    perror("The server terminated prematurely");
    return(NULL);
  }

  return (client->recvline);

}

int client_send(Client *client, char *msg){
  strcpy(client->sendline, msg);

  if( send(client->sockfd, client->sendline, strlen(client->sendline), 0) < strlen(client->sendline) ){
    fprintf(stderr, "Socket send error: not all bytes sent.\n");
  }

  fprintf(stdout, "Sending ""%s"" to the server...check.\n", msg);

  return(MSG_SENT);
}
