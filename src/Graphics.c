/*
 * An example of using GtkGLExt in C
 *
 * Written by Davyd Madeley <davyd@madeley.id.au> and made available under a
 * BSD license.
*/

#include "Graphics.h"

float boxv[][3] = {
	{ -0.5, -0.5, -0.5 },
	{  0.5, -0.5, -0.5 },
	{  0.5,  0.5, -0.5 },
	{ -0.5,  0.5, -0.5 },
	{ -0.5, -0.5,  0.5 },
	{  0.5, -0.5,  0.5 },
	{  0.5,  0.5,  0.5 },
	{ -0.5,  0.5,  0.5 }
};

static float ang = 30.;
static int duration[NUM_MIDI];

static gboolean
expose (GtkWidget *da, GdkEventExpose *event, gpointer user_data)
{
	GdkGLContext *glcontext = gtk_widget_get_gl_context (da);
	GdkGLDrawable *gldrawable = gtk_widget_get_gl_drawable (da);

	// g_print (" :: expose\n");

	if (!gdk_gl_drawable_gl_begin (gldrawable, glcontext))
	{
		g_assert_not_reached ();
	}

	/* draw in here */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	
	glRotated (ang, 1, 1, 0);

	glShadeModel(GL_FLAT);

        /*glColor4f(0.0, 1.0, 0.0, ALPHA);
        fourth_note(0.5, 0.2, 0, 0.1);
        glColor4f(1.0, 0.0, 0.0, ALPHA);
        full_note(0, 0.2, 0, 0.1);
        glColor4f(0.0, 0.0, 1.0, ALPHA);
        half_note(1, 0.2, 0, 0.1);
        glColor4f(1.0, 0.0, 1.0, ALPHA);
        other_notes(-0.5, 0.2, 0, 0.1, 4);*/

        int count = 0;
        for(int i = 0; i < NUM_MIDI; i ++) {
              if (duration[i] != 0) {
                  draw_note(duration[i], -0.8, -0.8, -(count * 0.3));
                  count ++;
              }
        }

//        draw_note(356, -0.8, -0.8, 0);
//        draw_note(18, -0.8, -0.8, -0.3);
//        draw_note(253, -0.8, -0.8, -0.6);

	glPopMatrix ();

	if (gdk_gl_drawable_is_double_buffered (gldrawable))
		gdk_gl_drawable_swap_buffers (gldrawable);

	else
		glFlush ();

	gdk_gl_drawable_gl_end (gldrawable);

	return TRUE;
}

void set_zero(void) {
     for(int i = 0; i < NUM_MIDI; i ++)
        duration[i] = 0;
}

void increment_duration(int index) {
    duration[index] ++;
}

void delete_duration(int index) {
    duration[index] = 0;
}

static gboolean
configure (GtkWidget *da, GdkEventConfigure *event, gpointer user_data)
{
	GdkGLContext *glcontext = gtk_widget_get_gl_context (da);
	GdkGLDrawable *gldrawable = gtk_widget_get_gl_drawable (da);

	if (!gdk_gl_drawable_gl_begin (gldrawable, glcontext))
	{
		g_assert_not_reached ();
	}

	glLoadIdentity();
	glViewport (0, 0, da->allocation.width, da->allocation.height);
	glOrtho (-10,10,-10,10,-20050,10000);
	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glScalef (10., 10., 10.);
	
	gdk_gl_drawable_gl_end (gldrawable);

	return TRUE;
}

gboolean
rotate (gpointer user_data)
{
	GtkWidget *da = GTK_WIDGET (user_data);

	ang++;

	gdk_window_invalidate_rect (da->window, &da->allocation, FALSE);
	gdk_window_process_updates (da->window, FALSE);

	return TRUE;
}

void set_up_graphics(GtkWidget *da) {

	GdkGLConfig *glconfig;

        set_zero();

	glconfig = gdk_gl_config_new_by_mode (
			GDK_GL_MODE_RGB |
			GDK_GL_MODE_DEPTH |
			GDK_GL_MODE_DOUBLE);

	if (!glconfig)
	{
		g_assert_not_reached ();
	}

	if (!gtk_widget_set_gl_capability (da, glconfig, NULL, TRUE,
				GDK_GL_RGBA_TYPE))
	{
		g_assert_not_reached ();
	}

	g_signal_connect (da, "configure-event",
			G_CALLBACK (configure), NULL);
	g_signal_connect (da, "expose-event",
			G_CALLBACK (expose), NULL);
}

