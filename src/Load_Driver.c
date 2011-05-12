#include "Load.h"

int main () {

   int length = song_length("e2.pond");
   int notes_array [length];

   parse_song("e2.pond", notes_array, length);
}
