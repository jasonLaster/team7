/*
 * clientdriver.c
 *
 *  Created on: May 12, 2011
 *      Author: Grim
 */

#include "PsycheMacros.h"
#include "client.h"

int main (int argc, char *argv[]){
  Client *client;
  char  s[MAXLINE],
        s2[MAXLINE];

  client = client_new();
  client_connect(client);

  while(scanf("%s", s) != EOF){
    fprintf(stdout, "Sending: %s\n", s);

    if(client_send(client, s) == MSG_SENT){
      fprintf(stdout, "Message sent to the server.\n");
    }

    client_listen(client);
    //fprintf(stdout, "%s\n", s2);
  }
}
