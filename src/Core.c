#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fluidsynth.h>

#include "Core.h"
#include "NoteMapping.h"

/* CORE_NEW is a constructor method that takes a fluidSynth reference and an
 * asciimap_filename and builds a Piano struct and sets up gtk events for key presses and releases.
 */
Core* core_new(const char *keyboard_map_file){ //FluidSynth* fluid,

  // instantiate a new core struct
  Core *core = (Core *) malloc(sizeof(Core));
  core->keyboard_map = core_load_keyboard_map(keyboard_map_file);
  core->synth = fluidsynth_new();
  core->player = instrument_new(0, 128);
  core->current_subdiv = 0;
  

  printf("core pointer address %p\n", core);

  // SIMULATE load and play callbacks
  core_load_song(core, "e2.pond");
  // cb_play_song(core);

  return core;
}

/*
 *
 */
void core_load_song(Core* core, char* const songfile) {
  core->song = instrument_new_from_song(15, songfile);
}


/*
 *
 */
void core_play_song(Core* core){
  core->current_subdiv = 1;
}


// OTHER STATIC METHODS

/* PRINT_KEYS_PRESSED is a simple helper function that prints the current
 * keys being played to the screen.
 */
void print_keys_pressed(Core* core) {
  Instrument *instrument = core->player;
  for(int i=0; i < instrument->number_of_notes; i++) {
    if (instrument_note_on(instrument, i)) printf("%c ", core_midi_to_keyboard(core->keyboard_map, i));
  }
  printf("\n");
}


/* CORE_DESTROY frees the ascii_note mapii, keys_pressed array, and fluidsynth
 * before freeing piano itself
 */
void core_destroy(Core* core) {
  instrument_destroy(core->player);
  instrument_destroy(core->song);
  mapii_destroy(core->keyboard_map);
  fluidsynth_destroy(core->synth);
  free(core);
}
