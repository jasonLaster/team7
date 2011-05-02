/*
 * PsycheMacros.h
 *
 *  Created on: Apr 26, 2011
 *      Author: Drew
 */

#ifndef PSYCHEMACROS
#define PSYCHEMACROS

#define NEW(s,t)  if( ( (s) = (t*) malloc( sizeof(t) ) ) == NULL ){ FATAL("malloc() returned NULL") }
#define FATAL(s){fprintf(stderr, "EXITING: fatal error at [%s:%d]:%s\n", __FILE__, __LINE__, s); exit(EXIT_FAILURE);}
#define ESCAPE 0xff1b
#define NOVALUE -1

#endif /* PSYCHEMACROS_H_ */
