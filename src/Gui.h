
#ifndef GUI
#define GUI

#include "Core.h"
#include "client.h"
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
	GtkWidget *filew;
	Login *login;
	Client *client;
};




Gui *gui_new(void);
void gui_destroy(Gui *gui);
void gui_txt_recv(Gui *gui, char *line);

#endif /* GUI */
