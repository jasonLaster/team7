/*
 * client.h
 *
 *  Created on: May 3, 2011
 *      Author: Drew
 */

#ifndef CLIENT
#define CLIENT

#include "PsycheMacros.h"

typedef struct client Client;
struct client{
  int channel,
      instrument;

  int sockfd;
  struct sockaddr_in servaddr;
  char sendline[MAXLINE], recvline[MAXLINE];
};

Client *client_new();
int client_connect(Client *client);
char *client_listen(Client *client);
int client_send(Client *client, char *msg);

#endif /* CLIENT */
