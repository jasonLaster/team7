#ifndef PLAYER
#define PLAYER

#include <stdio.h>
#include <stdlib.h>
//#include "Bomb.c"

typedef struct player Player;
struct player {

     int location;
     int player_num;
     int lives;
     int max_bombs;
     int current_bomb;
     int blast_rad;

};

Player *new_player (int num_play, int strt_loc, int num_lives, int max_bbs);
//Bomb *drop_bomb (Player *player, int time, int duration);
int delete_life (Player *player);
void add_life (Player *player);
void player_move (Player *player, int move_incr);
void delete_player (Player *player);
void print_player (Player *player);

#endif
