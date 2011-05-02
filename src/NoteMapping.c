#include <stdio.h>
#include <stdlib.h>

#include "NoteMapping.h"
#include "Mapii.h"
#include "Support.h"

#define NOVALUE -1

/* CORE_NOTE_TO_MIDI takes a note, octave, and sharp_flat and
 * returns the midi value.
 */
int core_note_to_midi(char const note, int octave, int sharp_flat) {
  char notes[] = {'c', ' ', 'd', ' ', 'e', 'f', ' ', 'g', ' ', 'a', ' ', 'b'};

  int note_index;
  for(note_index=0; notes[note_index] != note; note_index++);

  return ((octave + 1) * 12) + note_index + sharp_flat;
}

/* CORE_QWERTY_TO_MIDI takes a Mapii struct and a qwerty key and
 * returns the midi value that corresponds to that key.
 */
int core_keyboard_to_midi(Mapii* map, char const key) {
  return mapii_get(map, key);
}


char core_midi_to_keyboard(Mapii* map, int const midi) {
  int index = mapii_value_index(map, midi);
  return map->keys[index];
}


Mapii* core_load_keyboard_map(const char *keyboard_map_filename) {
  // get number of keys
  int notes = support_lines_in_file(keyboard_map_filename);
  Mapii *map = mapii_new(notes);
  mapii_load(map, keyboard_map_filename);
  return map;
}
