#include <stdlib.h>
#include <stdio.h>
#include <gtk/gtk.h>

#include "Gui.h"
#include "PsycheMacros.h"
#include "Graphics.h"
#include "Core.h"
#include "NoteMapping.h"
#include "Instrument.h"

#define WINDOWSIZE 800
#define NOTETIME 2000

static void cb_keypress(GtkWidget *widget, GdkEventKey *kevent, gpointer data);
static void cb_keyrelease(GtkWidget *widget, GdkEventKey *kevent, gpointer data);
static void cb_play(GtkWidget *widget, GdkEventKey *kevent, gpointer data);
static void cb_file_select(GtkWidget *widget, GdkEventKey *kevent, gpointer data);
static void cb_subdivision_beat(gpointer data);
static gboolean button_press ( GtkWidget *widget, GdkEvent *event );
static void destroy( GtkWidget *widget, gpointer data);
static gboolean delete_event( GtkWidget *widget, GdkEvent  *event, gpointer data );
static void file_ok_sel( GtkWidget *widget, gpointer g);

//CREATES AND RETURNS A NEW GUI
Gui *gui_new(void){
  Gui *gui;

  //set up the new GUI
  NEW(gui, Gui);
  gui->core = core_new("ascii_notes.map");

  GtkAdjustment *adj;

  //declare the widgets
  GtkWidget   *window,
              *menuBar,
              *fileMenu,
              *fileItem,
              *songMenu,
              *songItem,
              *userMenu,
              *userItem,
              *quitItem,
              *openItem,
              *instrumentItem1,
              *instrumentItem2,
              *playButton,
              *da,
              *spinButton1,
              *spinButton2,
              *table;

  GTimer    *timer;

  //setup the window
  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_widget_set_size_request (GTK_WIDGET (window), WINDOWSIZE, WINDOWSIZE);
  gtk_window_set_title (GTK_WINDOW (window), "Psyche");
  g_signal_connect (window, "destroy", G_CALLBACK (destroy), NULL);

	table = gtk_table_new (30, 30, TRUE);
	gtk_container_add (GTK_CONTAINER (window), table);

  /*setup the spin button and adjustment
        adj = (GtkAdjustment *) gtk_adjustment_new (0, 0, 127, 1, 5, 0);
        spinButton1 = gtk_spin_button_new();*/


  //setup the menu bar
  menuBar = gtk_menu_bar_new ();
  gtk_table_attach_defaults (GTK_TABLE (table), menuBar, 0, 30, 0, 1);
  gtk_widget_show (menuBar);

  //setup the menu items
  fileItem = gtk_menu_item_new_with_label ("File");
  gtk_widget_show(fileItem);
  songItem = gtk_menu_item_new_with_label ("Song");
  gtk_widget_show(songItem);
  userItem = gtk_menu_item_new_with_label ("User");
  gtk_widget_show(userItem);//group together and put it somewhere else

  //put the main menu items in the menu bar
  gtk_menu_shell_append (GTK_MENU_SHELL (menuBar), fileItem);
  gtk_menu_shell_append (GTK_MENU_SHELL (menuBar), songItem);
  gtk_menu_shell_append (GTK_MENU_SHELL (menuBar), userItem);

  //setup the sub menus
  fileMenu = gtk_menu_new ();
  songMenu = gtk_menu_new ();
  userMenu = gtk_menu_new ();

  //setup the sub menu items
  quitItem = gtk_menu_item_new_with_label ("Quit");
  gtk_widget_show(quitItem);
  openItem = gtk_menu_item_new_with_label ("Open");
  gtk_widget_show(openItem);
  instrumentItem1 = gtk_menu_item_new_with_label ("Instrument");
  gtk_widget_show(instrumentItem1);
  instrumentItem2 = gtk_menu_item_new_with_label ("Instrument");
  gtk_widget_show(instrumentItem2);

  //links the menu to the items
  gtk_menu_item_set_submenu(GTK_MENU_ITEM (fileItem) , fileMenu);
  gtk_menu_item_set_submenu(GTK_MENU_ITEM (songItem) , songMenu);
  gtk_menu_item_set_submenu(GTK_MENU_ITEM (userItem) , userMenu);

  //put the sub menu items in the proper menus
  gtk_menu_append (GTK_MENU (fileMenu), quitItem);
  gtk_menu_prepend (GTK_MENU_SHELL (fileMenu), openItem);
  gtk_menu_shell_append (GTK_MENU_SHELL (songMenu), instrumentItem1);
  gtk_menu_shell_append (GTK_MENU_SHELL (userMenu), instrumentItem2);

  //setup the menu item call backs
  g_signal_connect_swapped (quitItem, "activate", G_CALLBACK (delete_event), gui);
  g_signal_connect_swapped (openItem, "activate", G_CALLBACK (cb_file_select), gui);

  //set up the drawing area
  da = gtk_drawing_area_new ();
  gtk_table_attach_defaults (GTK_TABLE (table), da, 0, 30, 2, 30);
  gtk_widget_set_events (da, GDK_EXPOSURE_MASK | GDK_BUTTON_PRESS_MASK);
  set_up_graphics(da);

  //setup the button
  playButton = gtk_button_new_with_label("Play");
  gtk_table_attach_defaults (GTK_TABLE (table), playButton, 0, 30, 1, 2);

  //set up the call backs for buttons pressed
  g_signal_connect(G_OBJECT(window), "key_press_event", G_CALLBACK(cb_keypress), gui);
  g_signal_connect(G_OBJECT(window), "key_release_event", G_CALLBACK(cb_keyrelease), gui);
  g_signal_connect(G_OBJECT(playButton), "button-press-event", G_CALLBACK(cb_play), gui);
  g_timeout_add(16, (GSourceFunc) cb_subdivision_beat, gui);

  //show the window
  gtk_widget_show_all (window);

  //set up the timer
  timer = g_timer_new();

        //graphics timer
  g_timeout_add(16, rotate, da);

  return(gui);
}

static gboolean button_press ( GtkWidget *widget, GdkEvent *event ) {
       if (event -> type == GDK_BUTTON_PRESS) {
           GdkEventButton *bevent = (GdkEventButton *) event;
           gtk_menu_popup (GTK_MENU (widget), NULL, NULL, NULL, NULL, bevent->button, bevent->time);
           return TRUE;
       }
       return FALSE;
}

//FREES THE GUI AND ASSOCIATED MEMORY
void gui_destroy(Gui *gui){
  core_destroy(gui->core);
  free(gui);
}

// EVENTS


/* CB_KEYPRESS is a piano callback function that is called everytime gtk responds to a keypress
 * from the user. When called, cb_keypress figures out which note the user is playing and if the note is not
 * currently being played it turns it off. If the escape key is pressed, the app will quit.
 */
static void destroy( GtkWidget *widget, gpointer data) {
  Gui *gui = (Gui *) data;
  gui_destroy(gui);
  gtk_main_quit ();

}


//FROM THE HELLO WORLD GTK TUTORIAL AT http://developer.gnome.org/gtk-tutorial/stable/c39.html#SEC-HELLOWORLD
static gboolean delete_event( GtkWidget *widget,
                              GdkEvent  *event,
                              gpointer   data )
{
    /* If you return FALSE in the "delete-event" signal handler,
     * GTK will emit the "destroy" signal. Returning TRUE means
     * you don't want the window to be destroyed.
     * This is useful for popping up 'are you sure you want to quit?'
     * type dialogs. */

  g_print ("delete event occurred\n");

  //added by Drew J.
  Gui *gui = (Gui *) data;
  gui_destroy(gui);



    /* Change TRUE to FALSE and the main window will be destroyed with
     * a "delete-event". */

  return FALSE;
}


static void cb_file_select(GtkWidget *widget, GdkEventKey *kevent, gpointer data) {
      GtkWidget *filew;
      Gui    *gui = (Gui *) data;

      //set up the file open menu
      gui->filew = gtk_file_selection_new ("File Selection");
      gtk_signal_connect (GTK_OBJECT (filew), "destroy", (GtkSignalFunc) destroy, &filew);
      gtk_signal_connect (GTK_OBJECT (GTK_FILE_SELECTION (filew) ->ok_button), "clicked", (GtkSignalFunc) file_ok_sel, gui);
      gtk_signal_connect_object (GTK_OBJECT (GTK_FILE_SELECTION (filew) -> cancel_button), "clicked", (GtkSignalFunc) gtk_widget_destroy, GTK_OBJECT (filew));
      gtk_widget_show(filew);
}

static void file_ok_sel(GtkWidget *widget, gpointer g) {
  Gui* gui = (Gui*) g;
  g_print ("%s\n", gtk_file_selection_get_filename (GTK_FILE_SELECTION (gui->filew)));
}

static void cb_keypress(GtkWidget *widget, GdkEventKey *kevent, gpointer data){

  Gui* gui = (Gui*) data;
  Core* core = gui->core;
  int key = kevent->keyval;
  int note = core_keyboard_to_midi(core->keyboard_map, key);


  if (key == ESCAPE) { // escape key pressed
    core_destroy(core);
    gtk_main_quit();
  }
  else if (note != NOVALUE){

    if(!instrument_note_on(core->player, note)) {
       instrument_set_note_on(core->player->notes, note);
       print_keys_pressed(core);
       fluid_synth_noteon(core->synth, core->player->channel, note, 100);
       increment_duration(note);
    }

    //draw_note(duration, x, x, x);
  }
}


/* CB_KEYRELEASE is a piano callback function that is called everytime gtk responds to a key release event
 * from the user. When called, cb_keyrelease figures out which note the user is releasing and turns it off.
 */
static void cb_keyrelease(GtkWidget *widget, GdkEventKey *kevent, gpointer data){

  Gui* gui = (Gui*) data;
  Core* core = gui->core;
  int key = kevent->keyval;
  int note = core_keyboard_to_midi(core->keyboard_map, key);

  if (note != NOVALUE){
    instrument_set_note_off(core->player->notes, note);
    print_keys_pressed(core);
    fluid_synth_noteoff(core->synth, core->player->channel, note);
    delete_duration(note);
  }
}

static void cb_play(GtkWidget *widget, GdkEventKey *kevent, gpointer data){
  Gui* gui = (Gui*) data;
  Core* core = gui->core;
  core_play_song(core);
}

/*
 *
 */
static void cb_subdivision_beat(gpointer data) {

  Gui* gui = (Gui *) data;
  Core *core = gui->core;

  // Play the song as long as long as the current sub-division is greater than zero
  if (core->current_subdiv > 0){

    // Loop through all the notes and check to see if that note needs to be turned on or off
    for(int note = 0; note < 128; note++) {

      if (instrument_first_note(core->song, note, core->current_subdiv - 1)){
        fluid_synth_noteon(core->synth, core->song->channel, note, 100);
      }

      if (instrument_last_note(core->song, note, core->current_subdiv - 1)){
        fluid_synth_noteoff(core->synth, core->song->channel, note);
      }

    }

    core->current_subdiv++;
  }

  // ONCE THE SONG IS OVER, BRING THE CURRENT_SUBDIV BACK TO ZERO
  if(core->current_subdiv >= (core->song->number_of_notes / 128))
    core->current_subdiv = 0;

}
