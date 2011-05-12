
#include "gui.h"

static void cb_keypress(GtkWidget *widget, GdkEventKey *kevent, gpointer data);
static void cb_keyrelease(GtkWidget *widget, GdkEventKey *kevent, gpointer data);
static gboolean cb_expose(GtkWidget *da, GdkEventExpose *event, gpointer user_data);
static void cb_timer(gpointer user_data);

static gboolean configure(GtkWidget *da, GdkEventConfigure *event, gpointer user_data);

void gui_new(GtkWidget* window, GtkWidget* da){
  printf("hello world\n");
  set_up_graphics(da);
  
  
  g_signal_connect(da, "configure-event", G_CALLBACK (configure), NULL);
	g_signal_connect(da, "expose-event", G_CALLBACK (cb_expose), NULL);
	
}


static void cb_keypress(GtkWidget *widget, GdkEventKey *kevent, gpointer data){}
static void cb_keyrelease(GtkWidget *widget, GdkEventKey *kevent, gpointer data){}
static void cb_timer(gpointer user_data) {}

static gboolean cb_expose(GtkWidget *da, GdkEventExpose *event, gpointer user_data) {
  
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

  // INITIALIZE PROPERTIES
  const int XSize = WINDOW_WIDTH;
  const int YSize = WINDOW_HEIGHT;
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, XSize, YSize, 0, 0, 1);
  glMatrixMode(GL_MODELVIEW);

	return TRUE;
}
