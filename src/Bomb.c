#include "Bomb.h"

Bomb *new_bomb (int locat, int start, int durat, int blast, Player *player) {

     Bomb *bomb = (Bomb *) malloc(sizeof (Bomb));
     bomb -> loc = locat;
     bomb -> st_time = start;
     bomb -> dur = durat;
     bomb -> blast_rad = blast;
     bomb -> player = player;

     return bomb;
}

//check if freeing the player causing problems
void delete_bomb (Bomb *bomb) {
     free(bomb -> player);
     free(bomb);
}

int explode_bomb(Bomb *bomb, int time) {
    if (time == bomb -> st_time + bomb -> dur) {
        bomb -> player -> current_bomb --;
        return 1;
    }
    else
        return 0;
}



