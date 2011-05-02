#ifndef GRAPHICS
#define GRAPHICS

#include "Graphic_Note.h"

#define NUM_MIDI 128

void set_up_graphics(GtkWidget *da);
gboolean rotate (gpointer user_data);
void change_notes(int *notes);
void set_zero(void);
void increment_duration(int index);
void delete_duration(int index);

#endif
