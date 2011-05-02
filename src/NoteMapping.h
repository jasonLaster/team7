#ifndef NOTEMAPPING_H
#define NOTEMAPPING_H

#include "Mapii.h"


/* Prototypes */
int core_note_to_midi(char const note, int octave, int sharp_flat);
int core_keyboard_to_midi(Mapii* map, char const key);
char core_midi_to_keyboard(Mapii* map, int const midi);
Mapii* core_load_keyboard_map(const char *keyboard_map_filename);

// int piano_note_index(NoteMapping* notes, char note, int octave);
// int qwerty_key_index(NoteMapping* notes, char note);
// void note_mapping_destroy(NoteMapping* notes);

#endif
