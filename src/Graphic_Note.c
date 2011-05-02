#include "Graphic_Note.h"

static void oval_vertices(double x, double y, double z, int segments, double r) {
   for(int i = 0; i < segments; i++) {
        double a = i * 2.0 * 3.1415926535 / segments;
        glVertex3f(x + r * cos(a) * 1.5, y + r * sin(a), z);
    }   
}

static void oval_solid(double x, double y, double z, int segments, double r) {
   for(int i = 1 ; i <= segments; i++) {
       double b = i * 2.0 * 3.1415926535 / segments;
       oval_vertices(x, y ,  z + r*cos(b), segments, r * sin(b));
    }
}

static void rectangle_horiz(double x, double y, double z, double r) {
    glVertex3f(x + r, y, z + r);
    glVertex3f(x + r, y, z);
    glVertex3f(x, y, z);
    glVertex3f(x, y, z + r);
}

static void rectangle_vert(double x, double y, double z, double yr, double r) {
    glVertex3f(x + r, y + yr, z + r);
    glVertex3f(x + r, y, z + r);
    glVertex3f(x, y + yr, z + r);
    glVertex3f(x, y, z + r);
    glVertex3f(x, y + yr, z);
    glVertex3f(x, y, z);
    glVertex3f(x + r, y + yr, z);
    glVertex3f(x + r, y, z);
    glVertex3f(x + r, y + yr, z + r);
    glVertex3f(x + r, y, z + r);
}

static void connect_rect(double x1, double x2, double y1, double y2, double z, double r) {
    glBegin(GL_TRIANGLE_STRIP);
    glVertex3f(x1, y1, z);
    glVertex3f(x2, y2, z);
    glVertex3f(x1 + r, y1, z);
    glVertex3f(x2 + r, y2, z);
    glVertex3f(x1 + r, y1, z + r);
    glVertex3f(x2 + r, y2, z + r);
    glVertex3f(x1, y1, z + r);
    glVertex3f(x2, y2, z + r);
    glVertex3f(x1, y1, z);
    glVertex3f(x2, y2, z);
    glEnd();
}

static void fourth_note(double x, double y, double z, double r) {
        glBegin(GL_TRIANGLE_FAN);
        oval_solid( x , y , z , SEGMENTS, r);
        glEnd();
        glBegin(GL_TRIANGLE_STRIP);
        rectangle_vert((x + r), y , (z - r/4) , 6*r, r/2);
        glEnd();
        glBegin(GL_QUADS);
        rectangle_horiz((x + r), (y + 6*r), (z - r/4) , r/2);
        glEnd();
}

static void other_notes(double x, double y, double z, double r, int lines) {
        glBegin(GL_TRIANGLE_FAN);
        oval_solid( x , y , z , SEGMENTS, r);
        glEnd();
        glBegin(GL_TRIANGLE_STRIP);
        rectangle_vert((x + r), y , (z - r/4) , 6*r, r/2);
        glEnd();
        for(int i = 0; i < lines; i ++)
            connect_rect((x + r), (x + 2.5*r), (y + (6 - i)*r), (y + (3.5 - i)*r), (z - r/4), r/2);
        glBegin(GL_TRIANGLE_STRIP);
        rectangle_vert((x + 2.5*r), (y + 0.5*r), (z - r/4), 3*r, r/2);
        glEnd();
        glBegin(GL_QUADS);
        rectangle_horiz((x + r), (y + 6*r), (z - r/4) , r/2);
        glEnd();
}

static void half_note(double x, double y, double z, double r) {
        glBegin(GL_LINE_LOOP);
        oval_solid( x , y , z , SEGMENTS, r);
        glEnd();
        glBegin(GL_LINE_LOOP);
        rectangle_vert((x + r), y , (z - r/4) , 6*r, r/2);
        rectangle_horiz((x + r), (y + 6*r), (z - r/4) , r/2);
        glEnd();
}

static void full_note(double x, double y, double z, double r) {
       glBegin(GL_LINE_LOOP);
       oval_solid(x, y, z, SEGMENTS, r);
       glEnd();
}

//group together later
void draw_note(int duration, double x, double y, double z) {
       int number;
       double init_x = x;
       double x_incr = 0.5;
       double y_incr = 0.5;
       double r = RADIUS;

       if ((number = duration / 64) != 0) {
           glColor4f(1.0, 0.0, 0.0, ALPHA);
           duration %= 64;
           for(int i = 0; i < number; i ++) {
               full_note(x, y, z, r);
               x += x_incr;
               if (i % 4 == 3) {
                  y += y_incr;
                  x = init_x;
               }
           }
       }
       if ( x == init_x + (4 * x_incr) ) {
           x = init_x;
           y += y_incr;
       }
       if ((number = duration / 32) != 0) {
           glColor4f(0.0, 1.0, 0.0, ALPHA);
           duration %= 32;
           for(int i = 0; i < number; i ++) {
               half_note(x, y, z, r);
               x += x_incr;
           }            
       } 
       if ( x == init_x + (4 * x_incr) ) {
           x = init_x;
           y += y_incr;
       }
       if ((number = duration / 16) != 0) {
           glColor4f(0.0, 0.0, 1.0, ALPHA);
           duration %= 16;
           for(int i = 0; i < number; i ++) {
               fourth_note(x, y, z, r);
               x += x_incr;
           }
       }
       if ( x == init_x + (4 * x_incr) ) {
           x = init_x;
           y += y_incr;
       }
       if ((number = duration / 8) != 0) {
           glColor4f(1.0, 1.0, 0.0, ALPHA);
           duration %= 8;
           for(int i = 0; i < number; i ++) {
               other_notes(x, y, z, r, 1);
               x += x_incr;
           }
       }
       if ( x == init_x + (4 * x_incr) ) {
           x = init_x;
           y += y_incr;
       }
       if ((number = duration / 4) != 0) {
           glColor4f(0.0, 1.0, 1.0, ALPHA);
           duration %= 4;
           for(int i = 0; i < number; i ++) {
               other_notes(x, y, z, r, 2);
               x += x_incr;
           }
       }
       if ( x == init_x + (4 * x_incr) ) {
           x = init_x;
           y += y_incr;
       }
       if ((number = duration / 2) != 0) {
           glColor4f(1.0, 0.0, 1.0, ALPHA);
           duration %= 2;
           for(int i = 0; i < number; i ++) {
               other_notes(x, y, z, r, 3);
               x += x_incr;
           }
       }
       if ( x == init_x + (4 * x_incr) ) {
           x = init_x;
           y += y_incr;
       }
       if ((number = duration / 1) != 0) {
           glColor4f(1.0, 1.0, 1.0, ALPHA);
           for(int i = 0; i < number; i ++) {
               other_notes(x, y, z, r, 4);
               x += x_incr;
           }
      }
}
