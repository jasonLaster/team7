#include "Gameplay.h"

int main () {
  Game *game;
  int barriers[] = {10, 15, 23, 2, 34};
  game = begin_game(4, 7, 10, barriers, 5);
  return EXIT_SUCCESS;
}
