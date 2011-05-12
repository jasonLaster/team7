#include "graphics_helpers.h"



void draw_board(){
  
  // BOARD PERIMETER
  glColor3f(0.0, 0.0, 0.8);
  glBegin(GL_LINE_LOOP);
    glVertex2f(BOARD_OFFSET, BOARD_OFFSET);
    glVertex2f(WINDOW_WIDTH - BOARD_OFFSET, BOARD_OFFSET);
    glVertex2f(WINDOW_WIDTH - BOARD_OFFSET, WINDOW_HEIGHT - BOARD_OFFSET);
    glVertex2f(BOARD_OFFSET, WINDOW_HEIGHT - BOARD_OFFSET);
  glEnd();


  // BOARD GRID
  glColor3f(0.2, 0.2, 0.2);
  glBegin(GL_LINES);
    for(int i=1; i<24; i++){
      glVertex2f(i*CELL_SIZE+BOARD_OFFSET, BOARD_OFFSET+1);
      glVertex2f(i*CELL_SIZE+BOARD_OFFSET, WINDOW_HEIGHT-BOARD_OFFSET-1);      
    }
    for(int i=1; i<16; i++){
      glVertex2f(BOARD_OFFSET+1, i*CELL_SIZE+BOARD_OFFSET);
      glVertex2f(WINDOW_WIDTH-BOARD_OFFSET-1, i*CELL_SIZE+BOARD_OFFSET);
    }
  glEnd();
}

void draw_player(int cell){
  double x1=BOARD_OFFSET+(CELL_SIZE/2) +(cell-1)*CELL_SIZE;
  double y1=BOARD_OFFSET+(CELL_SIZE/2);
  double radius = CELL_SIZE/4;
  glColor3f(0.7,0.7,0.7);
  glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x1, y1);
    for(int deg=0; deg<360; deg+=1)  {
      glVertex2f(x1 + (sin(deg)*radius), y1 + (cos(deg)*radius));
    }
  glEnd();
  glBegin(GL_LINE_LOOP);
   for(int deg=0; deg<360; deg+=1)  {
     glVertex2f(x1 + (sin(deg)*radius), y1 + (cos(deg)*radius));
   }
  glEnd();
}

void draw_bomb(int cell) {
  // BOARD PERIMETER
  double offset = 3;
  double x=BOARD_OFFSET + (cell-1)*CELL_SIZE + offset; 
  double y=BOARD_OFFSET + offset;
  double size = CELL_SIZE-offset*2;
  
  
  glColor3f(0.0, 0.3, 0.0);
  glBegin(GL_QUADS);
    glVertex2f(x,y);
    glVertex2f(x+size,y);
    glVertex2f(x+size,y+size);
    glVertex2f(x,y+size);
  glEnd();

}


