#ifndef INSTRUMENT_H
#define INSTRUMENT_H

#include <fluidsynth.h>
#include "Synth.h"

typedef struct instrument Instrument;
struct instrument {
	int instrument;
	int channel;
	int* notes;
	int number_of_notes;
};

/* Prototypes */
Instrument* instrument_new(int channel, int size);
Instrument* instrument_new_from_song(int channel, char* const song_file);

int instrument_note_on(Instrument* instrument, int note);
int instrument_note_off(Instrument* instrument, int note);

int instrument_first_note(Instrument* instrument, int note, int subdivision);
int instrument_last_note(Instrument* instrument, int note, int subdivision);

void instrument_set_note_on(int *notes, int note);
void instrument_set_note_off(int *notes, int note);

void instrument_destroy(Instrument* instrument);

#endif
