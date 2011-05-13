/*
 * clientdriver.c
 *
 *  Created on: May 12, 2011
 *      Author: Grim
 */

#include "PsycheMacros.h"
#include "client.h"

static void listen_thread(void *arg);

int main (int argc, char *argv[]){
  Client *client;
  char  s[MAXLINE];

  if (argc < 2){
    fprintf(stderr, "Please provide an address to connect to.\n");
    return(EXIT_FAILURE);
  }

  client = client_new();


  //connect the client to the server
  if(client_connect(client, argv[1]) == SOCKET_CONNECT_ERROR){
    fprintf(stdout, "Cannot connect to the server\n");
  }

  //create the listening thread of the client
  pthread_t t1;
  int iret1 = pthread_create(&t1, NULL, listen_thread, (void *) client);

  //sending loop
  while(true){

    while(fgets(s, MAXLINE, stdin) != NULL){
      fprintf(stdout, "Sending: %s to the client.\n", s);

      char *c;
      if ((c = strchr(s, '\n')) != NULL)
        *c = '\0';

      if(client_send(client, s) == MSG_SENT){
        fprintf(stdout, "Message sent to the server.\n");
      }
    }
  }

  return(EXIT_SUCCESS);
}

static void listen_thread(void *arg){
  Client *client = (Client *) arg;
  char s[MAXLINE];

  while(true){
    strcpy(s, client_listen(client));
    fprintf(stdout, "%s\n", s);
  }
}
