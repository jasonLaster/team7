#include "Gameplay.h"

//Understand that the allocation of max bomb may cause bugs because of the number given
Game *begin_game (int num_players, int board_size, int max_bb, int *barriers, int num_barriers) {

     Game* game = (Game *) malloc (sizeof (game) );
     game -> board = new_board (board_size);
     game -> alive = (Player **) malloc (sizeof (Player) * num_players);
     game -> dead = (Player **) malloc (sizeof (Player) * num_players);
     game -> bombs = (Bomb **) malloc (sizeof (Bomb) * max_bb);
     game -> max_players = num_players;
     game -> current_bomb = 0;
     game -> max_bomb = max_bb;

     empty_board(game -> board);
     add_barriers(game -> board, barriers, num_barriers);

     for(int i = 1; i <= num_players; i ++)
         add_players(i, game);

     return game;
}

void no_dead_players (Game *game) {
    for(int i = 0; i < game -> max_players; i ++)
        game -> dead[i] = NULL;
}

//make diverse starting locations
void add_players (int num_player, Game *game) {
    game -> alive[num_player - 1] = new_player(num_player, 0, 3, 2);
}

void player_died (int num_player, Game *game) {
    game -> dead[num_player - 1] = game -> alive[num_player - 1];
    game -> alive[num_player - 1] = NULL;
}

void move_player_cond (int num_player, Game *game, int move_incr) {
    if (check_move(game -> board, game -> alive[num_player - 1]-> location + move_incr))
        player_move(game -> alive[num_player - 1], move_incr);
}

void drop_bomb (int num_player, Game *game, int time, int duration) {
      if (game -> alive[num_player - 1] -> current_bomb <= game -> max_bomb) {
           Bomb *bomb;
           bomb = new_bomb(game -> alive[num_player - 1] -> location , time, duration, game -> alive[num_player - 1] -> blast_rad, game -> alive[num_player - 1]);
           game -> alive[num_player - 1] -> current_bomb ++;
           game -> current_bomb ++;
      }
}

int check_blast (Board *board, Bomb *bomb, Player *player) {
    if (bomb -> loc == player -> location)
       return 1;
    else {
          for (int i = 1; i <= bomb -> blast_rad; i ++) {
              if((bomb -> loc + (board -> side_size * i)) >= (board -> side_size * board -> side_size))
                    break;
              else if(board -> map[(bomb -> loc + (board -> side_size * i))] == 1)
                    break;
              else if(board -> map[(bomb -> loc + (board -> side_size * i))] == player -> location)
                    return 1;
          }
          for (int i = 1; i <= bomb -> blast_rad; i ++) {
              if((bomb -> loc + i) % board -> side_size == 0)
                    break;
              else if(board -> map[(bomb -> loc + i)] == 1)
                    break;
              else if(board -> map[(bomb -> loc + i)] == player -> location)
                    return 1;
          }
          for (int i = 1; i <= bomb -> blast_rad; i ++) {
              if((bomb -> loc - (board -> side_size * i)) <= 0)
                    break;
              else if(board -> map[(bomb -> loc - (board -> side_size * i))] == 1)
                    break;
              else if(board -> map[(bomb -> loc - (board -> side_size * i))] == player -> location)
                    return 1;
          }
          for (int i = 1; i <= bomb -> blast_rad; i ++) {
              if((bomb -> loc - i) % board -> side_size == (board -> side_size - 1))
                    break;
              else if(board -> map[(bomb -> loc - i)] == 1)
                    break;
              else if(board -> map[(bomb -> loc - i)] == player -> location)
                    return 1;
          }
          return 0;
     }
}

void bomb_timer (Game *game, int time) {
      for(int i = 0; i < game -> current_bomb; i ++) {
          if(explode_bomb(game -> bombs[i], time))
               for(int j = 0; j < game -> max_players; j ++) {
                     if(check_blast(game -> board, game -> bombs[i], game -> alive[j]))
                           player_died(j, game);
               }
      }                    
}
