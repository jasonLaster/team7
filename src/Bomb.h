#ifndef BOMB
#define BOMB

#include <stdio.h>
#include <stdlib.h>
#include "Player.h"

typedef struct bomb Bomb;
struct bomb {
   int st_time;
   int dur;
   int loc;
   int blast_rad;
   Player *player;
};

Bomb *new_bomb (int locat, int start, int durat, int blast, Player *player);
void delete_bomb (Bomb *bomb);
int explode_bomb (Bomb *bomb, int time);

#endif
