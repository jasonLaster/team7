#include <gtk/gtk.h>

#include "Graphics.h"

int main(int argc, char **argv) {
	GtkWidget *window;
	GtkWidget *da;

	gtk_init (&argc, &argv);
	gtk_gl_init (&argc, &argv);

	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_default_size(GTK_WINDOW (window), 800, 600);
	da = gtk_drawing_area_new ();

	gtk_container_add(GTK_CONTAINER (window), da);
	g_signal_connect_swapped (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);

	gtk_widget_set_events(da, GDK_EXPOSURE_MASK);
  set_up_graphics(da);

  for(int i = 0; i < 57; i ++) increment_duration(1);
  for(int i = 0; i < 10; i ++) increment_duration(127);
  for(int i = 0; i < 234; i ++) increment_duration(12);
  for(int i = 0; i < 115; i ++) increment_duration(15);

	gtk_widget_show (window);
	gtk_widget_show_all (window);

	g_timeout_add(16, rotate, da);
	gtk_main ();
}
