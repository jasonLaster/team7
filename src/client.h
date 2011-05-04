/*
 * client.h
 *
 *  Created on: May 3, 2011
 *      Author: Drew
 */

#ifndef CLIENT
#define CLIENT

#include "PsycheMacros.h "

typedef struct client Client;
struct client{
  int channel,
      instrument;
};

Client *client_new();

#endif /* CLIENT */
