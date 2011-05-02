
#ifndef GUI
#define GUI

#include "Core.h"

typedef struct gui Gui;
struct gui{
	Core	*core;
	GtkFileSelection *filew;
};

Gui *gui_new(void);
void gui_destroy(Gui *gui);

#endif /* GUI */
