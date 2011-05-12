#ifndef GAMEPLAY
#define GAMEPLAY

#include "Player.h"
#include "Board.h"
#include "Bomb.h"

typedef struct game Game;
struct game {
    Board *board;
    int *c;
    Player ** alive;
    Player ** dead;
    Bomb ** bombs;
    int max_players;
    int current_bomb;
    int max_bomb;
};

Game *begin_game (int num_players, int board_size, int max_bb, int *barriers, int num_barriers);
void no_dead_players (Game *game);
void add_players (int num_player, Game *game);
void player_died (int num_player, Game *game);
void move_player_cond (int num_player, Game *game, int move_incr);
int check_blast (Board *board, Bomb *bomb, Player *player);
void bomb_timer (Game *game, int time);

#endif
