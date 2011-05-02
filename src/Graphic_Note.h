#ifndef GRAPHIC_NOTE
#define GRAPHIC_NOTE

#include <gtk/gtk.h>
#include <gtk/gtkgl.h>
#include <GL/gl.h>
#include <math.h>

#define SEGMENTS 50
#define RADIUS 0.05
#define ALPHA 0.5

void draw_note(int duration, double x, double y, double z);

#endif
