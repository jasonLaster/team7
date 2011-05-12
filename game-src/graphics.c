
#include "Graphics.h"


static gboolean expose(GtkWidget *da, GdkEventExpose *event, gpointer user_data) {
  
  // SETUP
	GdkGLContext *glcontext = gtk_widget_get_gl_context(da);
	GdkGLDrawable *gldrawable = gtk_widget_get_gl_drawable(da);
	if (!gdk_gl_drawable_gl_begin(gldrawable, glcontext)) g_assert_not_reached ();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // DRAW STUFF
  draw_board();
  draw_player(2);
  draw_bomb(5);

  // STOP DRAWING
  gdk_gl_drawable_is_double_buffered(gldrawable) ? gdk_gl_drawable_swap_buffers(gldrawable) : glFlush();
	gdk_gl_drawable_gl_end(gldrawable);

	return TRUE;
}

static gboolean configure(GtkWidget *da, GdkEventConfigure *event, gpointer user_data) {

  // SETUP 
	GdkGLContext *glcontext = gtk_widget_get_gl_context (da);
	GdkGLDrawable *gldrawable = gtk_widget_get_gl_drawable (da);
	if (!gdk_gl_drawable_gl_begin (gldrawable, glcontext)) g_assert_not_reached ();

  const int XSize = WINDOW_WIDTH;
  const int YSize = WINDOW_HEIGHT;
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, XSize, YSize, 0, 0, 1);
  glMatrixMode(GL_MODELVIEW);

	return TRUE;
}

void timer(gpointer user_data) {}

void set_up_graphics(GtkWidget *da) {

  // SETUP GL_CONFIG
	GdkGLConfig *glconfig;
	glconfig = gdk_gl_config_new_by_mode(GDK_GL_MODE_RGB | GDK_GL_MODE_DOUBLE);
	if (!glconfig) g_assert_not_reached();
	if (!gtk_widget_set_gl_capability(da, glconfig, NULL, TRUE, GDK_GL_RGBA_TYPE)) g_assert_not_reached();
	
  // SETUP CALLBACKS
	g_signal_connect(da, "configure-event", G_CALLBACK (configure), NULL);
	g_signal_connect(da, "expose-event", G_CALLBACK (expose), NULL);
}

