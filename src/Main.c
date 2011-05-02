#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <gtk/gtk.h>
#include <gtk/gtkgl.h>
#include <GL/gl.h>

#include "Core.h"
#include "Gui.h"

// MAIN instantiates gtk, a piano struct, and then starts
// the gtk_main loop which will listen for keypresses.
int main(int argc, char** argv) {

	Gui	*gui;

	//initialize gtk and openGL
	gtk_init (&argc, &argv);
	gtk_gl_init (&argc, &argv);

	//create the new core and gui
	gui = gui_new();

	//start gtk
	gtk_main();

	gui_destroy(gui);

  return (EXIT_SUCCESS);
}
