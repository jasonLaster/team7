#include <stdio.h>
#include <stdlib.h> 
#include "Mapii.h"


/* MAPII_NEW is a constructor method that instantiates a new Mapii struct.
 */
Mapii* mapii_new(int size) {
  Mapii *m = (Mapii *) malloc(sizeof(Mapii));
  m->keys = (int *) malloc(size * sizeof(int));
  m->values = (int *) malloc(size * sizeof(int));
  m->size = size;
  return m;
}



/* MAPIII_LOAD reads in the map file and loops through the lines
 * reading in the keys and their midi values. While each line also has a 
 * piano key value at the end, this is ignored by mapii_load.
 */ 
void mapii_load(Mapii* map, const char* map_file) {

  FILE *source = fopen(map_file, "r");
  int index = 0; // map index
  
  char *line = (char*) malloc(12 * sizeof(char)); // current line
  char *skip = (char*) malloc(10 * sizeof(char)); // junk at end of line that i don't want to cpature
  int i = 0; // current position in line
  char c; // current char
  char key; // key value
  int value; // midi value
  

  // read in characters until EOF
  // set vars when a new line character is read
  while((c = fgetc(source)) != EOF) {
    if(c == '\n'){
      
      // load in values
      sscanf(line, "%c %d %s\n", &key, &value, skip);
      map->keys[index] = key;
      map->values[index++] = value;

      // clear variables
      i=0;
      line = (char*) malloc(12 * sizeof(char));
    } else {
      line[i++] = c;
    }
  }
  fclose(source);
}


/* MAPII_GET takes a map and a key value and returns the
 * int value that correspons with the key.
 */
int mapii_get(Mapii* map, char key) {
  int index = mapii_index(map, key);
  return (index == -1) ?  -1 : map->values[index];
}

/* MAPII_KEY take a map and a key indeci
 * and returns the key value
 */
int mapii_key(Mapii* map, int index) {
  return (index == -1) ?  -1 : map->keys[index];  
}

/* MAPII_INDEX takes a map and a key value and returns the
 * index of the key
 */
int mapii_index(Mapii* map, char key) {
  int i;
  for(i=0; (i < map->size) && (map->keys[i] != key); i++);
  return (i < map->size) ? i : -1; 
}


/* MAPII_VALUE_INDEX takes a map and a values value and returns 
 * the index of the value
 */
int mapii_value_index(Mapii* map, int value) {
  int i;
  for(i=0; (i < map->size) && (map->values[i] != value); i++);
  return (i < map->size) ? i : -1;
}


/* MAPII_DESTROY takes a Mapii struct and frees its
 * member keys and value arrays, and then proceeds to kill itself
 */ 
void mapii_destroy(Mapii* map) {
  free(map->keys);
  free(map->values);
  free(map);
}

