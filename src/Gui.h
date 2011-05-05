
#ifndef GUI
#define GUI

#include "Core.h"
#include <stdlib.h>
#include <stdio.h>
#include <gtk/gtk.h>

typedef struct login Login;
struct login{
	GtkEntry *server_addr;
	GtkEntry *server_port;
	GtkEntry *username;
};


typedef struct gui Gui;
struct gui{
	Core	*core;
	GtkFileSelection *filew;
	Login *login;
};




Gui *gui_new(void);
void gui_destroy(Gui *gui);

#endif /* GUI */
