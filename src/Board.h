#ifndef BOARD
#define BOARD

#include <stdio.h>
#include <stdlib.h>

typedef struct board Board;
struct board {
    int side_size;
    int *map;
};

Board *new_board (int size);
void empty_board (Board *board);
void add_barriers (Board *board, int *locat, int num_blocks);
void print_board (Board *board);
void place_bomb (Board *board, int locat);
void remove_bomb (Board *board, int locat);
int check_move (Board *board, int fut_loc);
void delete_board (Board *board);

#endif
