/*
 * PsycheMacros.h
 *
 *  Created on: Apr 26, 2011
 *      Author: Drew
 */

#ifndef PSYCHEMACROS
#define PSYCHEMACROS

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>

#define NEW(s,t)  if( ( (s) = (t*) malloc( sizeof(t) ) ) == NULL ){ FATAL("malloc() returned NULL") }
#define FATAL(s){fprintf(stderr, "EXITING: fatal error at [%s:%d]:%s\n", __FILE__, __LINE__, s); exit(EXIT_FAILURE);}
#define ESCAPE 0xff1b
#define NOVALUE -1
#define MAXLINE 4096 /*max text line length*/
#define SERV_PORT 7744 /*port*/
#define SERV_ADDR "spruce.cs.dartmouth.edu"
#define SOCKET_CREATE_ERROR -1
#define SOCKET_CONNECT_ERROR -2
#define SOCKET_CONNECT_SUCCESS 0
#define MSG_SENT 0

#endif /* PSYCHEMACROS_H_ */
