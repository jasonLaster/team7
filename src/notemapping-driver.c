#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>


#include "NoteMapping.h"
#include "Instrument.h"
#include "Mapii.h"
#include "Load.h"

int main(int argc, char** argv) {

  Mapii* map = core_load_keyboard_map("ascii_notes.map");
  
  printf("note: %c      midi value %d\n", 'q', core_note_to_midi('c', 0, 0));
  printf("note: %s     midi value %d\n", "d'", core_note_to_midi('d', 1, 0));
  printf("note: %s   midi value %d\n", "dis'", core_note_to_midi('d', 1, 1));
  printf("note: %s midi value %d\n", "gis'''", core_note_to_midi('g', 3, 1));
  printf("key: %c       midi value: %d\n", 'q', core_keyboard_to_midi(map, 'q'));
    
  printf("create new song:\n");
  char* song_file = "e1.pond";
  int duration_of_song = song_length(song_file);
  printf("duration: %d\n", duration_of_song);
  
  instrument_new_from_song(15, song_file);
  
  return EXIT_SUCCESS;
}
