#include "Board.h"

Board *new_board (int size) {

     Board *board = (Board *) malloc(sizeof (Board));
     board -> map = (int *) malloc(sizeof (int) * size *size);
     board -> side_size = size;

     return board;
}

void delete_board (Board *board) {
     free(board -> map);
     free(board);
}

void empty_board (Board *board) {
     for(int i = 0; i < ( board-> side_size * board -> side_size ) ; i ++)
            board -> map[i] = 0;
}

//change in accordance to other factors
void add_barriers (Board *board, int *locat, int num_blocks) {
     for(int i = 0; i < num_blocks; i ++)
         if(locat[i] >= ( board -> side_size * board -> side_size ))
             printf("Not In Proper Location\n");
         else
             board -> map[locat[i]] = 1;
}

void place_bomb (Board *board, int locat) {
     board -> map[locat] = 2;
}

void remove_bomb (Board *board, int locat) {
     board -> map[locat] = 0;
}

int check_move (Board *board, int fut_loc) {

     if (board -> map[fut_loc] != 0)
        return 0;
     else
        return 1;
}

//used for testing
void print_board (Board *board) {
     for(int i = 0; i < ( board-> side_size * board -> side_size ) ; i ++) {
            if ( i % board -> side_size == 0)
                printf("\n");
            printf("%i ", board -> map[i]);
     }
     printf("\n");
}

