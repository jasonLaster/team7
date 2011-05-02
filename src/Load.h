#ifndef LOAD_H
#define LOAD_H

//#include "Synth.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "NoteMapping.h"

#define SUBDIV 64
#define NUM_MIDI 128

/* Prototypes */
int load_file(const char* song_name, int *notes_array);
int song_length(char* const file);
void print_song(int *notes_array, int length);
void parse_song(char* const file, int *notes_array, int length);

#endif
