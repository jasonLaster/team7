#include "Load.h"

int main () {

   int length = song_length("e2.pond");
   printf("song length: %d\n", length);

   int array_song[length];
   parse_song("e2.pond", array_song, length);
   print_song(array_song, length);

}
