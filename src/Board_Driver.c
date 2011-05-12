#include "Board.h"

int main () {
    Board *board = new_board(7);
    //first test
    /*int barriers[] = {0,4,15,16,32,10};
    empty_board(board);
    add_barriers(board, barriers, 6);
    print_board(board);*/
    
    //second test
    /*empty_board(board);
    place_bomb(board, 32);
    place_bomb(board, 31);
    if(check_move(board, 31))
       remove_bomb(board, 31);
    print_board(board);*/

return EXIT_SUCCESS;
}
