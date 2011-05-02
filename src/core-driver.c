#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <gtk/gtk.h>


#include "Core.h"
#include "NoteMapping.h"

int main(int argc, char** argv) {

  gtk_init (&argc, &argv);

  Core* core = core_new("ascii_notes.map");

  printf("check to see if the core's keyboard map was properly set:\n");
  printf("key: %c =>  %d\n\n", 'q', core_keyboard_to_midi(core->keyboard_map, 'q'));
  if(core_keyboard_to_midi(core->keyboard_map, 'q') != 60) printf("the q key should be set to 60");

  printf("check to see if the player's notes array is set correctly:\n");
  printf("player->notes[0] = %d\n\n", core->player->notes[1]);
  if (core->player->notes[1] != 0) printf("the player's notes array was not properly set.\n");

  printf("start gtk:\n");
  gtk_main();
  
  return EXIT_SUCCESS;
}
