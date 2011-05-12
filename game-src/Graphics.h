#ifndef GRAPHICS
#define GRAPHICS

#include <gtk/gtk.h>
#include <gtk/gtkgl.h>
#include <GL/gl.h>
#include <math.h>

#include "graphics_helpers.h"

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480
#define BOARD_OFFSET 80
#define CELL_SIZE 20

void set_up_graphics(GtkWidget *da);
void timer(gpointer user_data);

#endif
