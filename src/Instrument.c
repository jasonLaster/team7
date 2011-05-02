#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fluidsynth.h>

#include "Instrument.h"
#include "Load.h"
#include "PsycheMacros.h"

/* INSTRUMENT_NEW is a constructor method that builds a new instrument struct.
 * In order to build a new instrument, it needs to know which midi-channel it'll be played
 * on and the size of the notes array, which will keep the keys_pressed or song information.
 */
Instrument* instrument_new(int channel, int size) {
  Instrument *instrument;
  NEW(instrument, Instrument);
  instrument->number_of_notes = size;
  instrument->instrument = 0;
  instrument->channel = channel;

  // initialize the instruments note's array and set all of it's elements to zero
  instrument->notes = (int *) malloc(size * sizeof(int));
  int i; for(i=0; i < size; i++) instrument->notes[i] = 0;

  return instrument;
}

// NEED LOAD FILE TO WORK
/*
 */
Instrument* instrument_new_from_song(int channel, char* const song_file) {
  int duration_of_song = song_length(song_file);
  Instrument* instrument = instrument_new(channel, duration_of_song);
  parse_song(song_file, instrument->notes, duration_of_song);

  return instrument;
}


/* INSTRUMENT_NOTE_ON and OFF checks to see if the instrument is currently playing
 * or not playing a note.
 */
int instrument_note_on(Instrument* instrument, int note) {
  return instrument->notes[note] == 1;
}

int instrument_note_off(Instrument* instrument, int note) {
  return instrument->notes[note] == 0;
}


/* INSTRUMENT_FIRST_NOTE and LAST_NOTE checks to see if the instrument just started or
 * stopped playing a note. This method is used to check to see if fluidsynth should turn a note on or off.
 */
int instrument_first_note(Instrument* instrument, int note, int subdivision) {
  return instrument->notes[128*(subdivision-1) + note] == 0 &&
         instrument->notes[128*subdivision     + note] == 1;
}

int instrument_last_note(Instrument* instrument, int note, int subdivision) {
  return instrument->notes[128*subdivision + note] == 2;
}


/* INSTRUMENT_SET_NOTE_ON and OF tell's the instrument to play or stop playing a certain note
 * this is only used with the player instrument or other instruments that are played in realtime.
 */
void instrument_set_note_on(int *notes, int note) {
  notes[note] = 1;
}

void instrument_set_note_off(int *notes, int note) {
  notes[note] = 0;
}


/* INSTRUMENT_DESTROY free's the current instrument
 */
void instrument_destroy(Instrument *instrument) {
  free(instrument);
}
