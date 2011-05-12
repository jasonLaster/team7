#include "Player.h"

Player *new_player (int num_play, int strt_loc, int num_lives, int max_bbs) {
     
    Player *player = (Player *) malloc ( sizeof(Player) );
    player -> location = strt_loc;
    player -> lives = num_lives;
    player -> player_num = num_play;
    player -> max_bombs = max_bbs;
    player -> current_bomb = 1;
    player -> blast_rad = 2;

    return player;
}

void delete_player (Player *player) {
    free(player);
}

void player_move (Player *player, int move_incr) {
    player -> location += move_incr;
}

void add_life (Player *player) {
   player -> lives ++;
}

int delete_life (Player *player) {
   player -> lives --;
   if (player -> lives == 0)
      return 1;
   else
      return 0;
}

//note that blast is constant for now
/*Bomb *drop_bomb (Player *player, int time, int duration) {
   if (player -> current_bomb == player -> max_bombs)
      return NULL;
   else {
      Bomb *bomb;
      bomb = new_bomb (player -> location, time, duration, 2);
      player -> current_bomb ++;
      return bomb;
   }
}*/

void print_player (Player *player) {
    printf("location: %i\n", player -> location);
    printf("lives: %i\n", player -> lives);
    printf("player number: %i\n", player -> player_num);
    printf("Maximum Bombs: %i\n", player -> max_bombs);
    printf("Current Bomb: %i\n", player -> current_bomb);
}



