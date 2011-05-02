#ifndef MAPII_H
#define MAPII_H

typedef struct mapii Mapii;
struct mapii {
  int *keys;
  int *values;
  int size;
};

/* Prototypes */
Mapii* mapii_new(int s);
void mapii_load(Mapii* map, const char* map_file);
int mapii_get(Mapii* map, char key);
int mapii_index(Mapii* map, char key);
int mapii_value_index(Mapii* map, int value);
int mapii_key(Mapii* map, int index);
void mapii_destroy(Mapii* map);

#endif
