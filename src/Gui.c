#include "Gui.h"
#include "PsycheMacros.h"
#include "Graphics.h"
#include "Core.h"
#include "client.h"
#include "NoteMapping.h"
#include "Instrument.h"

#define WINDOWSIZE 800
#define NOTETIME 2000

/* EVENTS */
static void click_open_song(GtkWidget *widget, GdkEventKey *kevent, gpointer data);
<<<<<<< .merge_file_ZMpch0
static gboolean button_press(GtkWidget *widget, GdkEvent *event );
=======
static void click_login(GtkWidget *widget, GdkEventKey *kevent, gpointer data);
// static gboolean button_press(GtkWidget *widget, GdkEvent *event );
>>>>>>> .merge_file_5rVZYp

/* CALLBACKS */
static void cb_keypress(GtkWidget *widget, GdkEventKey *kevent, gpointer data);
static void cb_keyrelease(GtkWidget *widget, GdkEventKey *kevent, gpointer data);
static void cb_subdivision_beat(gpointer data);
static void cb_play_song(GtkWidget *widget, GdkEventKey *kevent, gpointer data);
<<<<<<< .merge_file_ZMpch0
static void cb_load_song(GtkWidget *widget, gpointer g);
=======
static void cb_load_song(GtkWidget *widget, gpointer data);
static void cb_server_login(GtkWidget *widget, gpointer data);

>>>>>>> .merge_file_5rVZYp

/* DESTROY METHODS */
static void destroy( GtkWidget *widget, gpointer data);
static gboolean delete_event( GtkWidget *widget, GdkEvent  *event, gpointer data );


//CREATES AND RETURNS A NEW GUI
Gui *gui_new(void){

  //set up the new GUI
  Gui *gui;
  NEW(gui, Gui);
  gui->core = core_new("ascii_notes.map");
  gui->login = (Login *) malloc(sizeof(Login));
  gui->client = client_new();

<<<<<<< .merge_file_ZMpch0
  printf("gui pointer address %p\n", gui);
  printf("core pointer address %p\n", gui->core);

  GtkAdjustment *adj;
=======
  // GtkAdjustment *adj;
>>>>>>> .merge_file_5rVZYp

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
              *loginItem,
              *instrumentItem1,
              *instrumentItem2,
              *playButton,
              *da,
              // *spinButton1,
              // *spinButton2,
              *table;

  GTimer *timer;

  //setup the window
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_widget_set_size_request(GTK_WIDGET (window), WINDOWSIZE, WINDOWSIZE);
  gtk_window_set_title(GTK_WINDOW (window), "Psyche");
  g_signal_connect(window, "destroy", G_CALLBACK (destroy), NULL);

  // setup chat window components
  GtkWidget* chat_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  GtkWidget* vbox = gtk_vbox_new(FALSE, 10);
  // GtkWidget* scrollable_region = gtk_layout_new(NULL, NULL);
  GtkWidget *chat_log = gtk_text_view_new();
  GtkTextBuffer *chat_log_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW (chat_log));
  GtkWidget *chat_input = gtk_text_view_new();
  GtkTextBuffer *chat_input_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW (chat_input));



  // layout chat window components
  gtk_container_add(GTK_CONTAINER(chat_window), vbox);
  gtk_box_pack_start(vbox, chat_log, TRUE, FALSE, 0);
  gtk_box_pack_start(vbox, chat_input, FALSE, FALSE, 0);
  // gtk_layout_put(scrollable_region, text_view, 0,0);

  // set chat window component parameters
  // gtk_layout_get_size(scrollable_region, 300, 700);
  gtk_window_set_title(chat_window, "Chat");
  gtk_window_resize(chat_window, 300, 800);
  gtk_editable_set_editable(chat_log_buffer, FALSE);
  gtk_text_buffer_set_text(chat_log_buffer, "Hello, this is some text", -1);
  gtk_text_buffer_set_text(chat_input_buffer, "Hello, this is some text", -1);
  gtk_widget_show_all(chat_window);


  // setup layout table for the primary window
	table = gtk_table_new(30, 30, TRUE);
	gtk_container_add(GTK_CONTAINER (window), table);

  /*
    setup the spin button and adjustment
    adj = (GtkAdjustment *) gtk_adjustment_new (0, 0, 127, 1, 5, 0);
    spinButton1 = gtk_spin_button_new();
  */


  //setup the menu bar
  menuBar = gtk_menu_bar_new ();
  gtk_table_attach_defaults (GTK_TABLE (table), menuBar, 0, 30, 0, 1);
  gtk_widget_show (menuBar);

  //setup the menu items
  fileItem = gtk_menu_item_new_with_label("File");
  songItem = gtk_menu_item_new_with_label("Song");
  userItem = gtk_menu_item_new_with_label("User");
  gtk_widget_show(fileItem);
  gtk_widget_show(songItem);
  gtk_widget_show(userItem);

  //put the main menu items in the menu bar
  gtk_menu_shell_append(GTK_MENU_SHELL (menuBar), fileItem);
  gtk_menu_shell_append(GTK_MENU_SHELL (menuBar), songItem);
  gtk_menu_shell_append(GTK_MENU_SHELL (menuBar), userItem);

  //setup the sub menus
  fileMenu = gtk_menu_new ();
  songMenu = gtk_menu_new ();
  userMenu = gtk_menu_new ();

  //setup the sub menu items
  quitItem = gtk_menu_item_new_with_label("Quit");
  openItem = gtk_menu_item_new_with_label("Open");
  loginItem = gtk_menu_item_new_with_label("Login");
  instrumentItem1 = gtk_menu_item_new_with_label("Instrument");
  instrumentItem2 = gtk_menu_item_new_with_label("Instrument");
  gtk_widget_show(quitItem);
  gtk_widget_show(openItem);
  gtk_widget_show(loginItem);
  gtk_widget_show(instrumentItem1);
  gtk_widget_show(instrumentItem2);


  //links the menu to the items
  gtk_menu_item_set_submenu(GTK_MENU_ITEM (fileItem), fileMenu);
  gtk_menu_item_set_submenu(GTK_MENU_ITEM (songItem), songMenu);
  gtk_menu_item_set_submenu(GTK_MENU_ITEM (userItem), userMenu);

  //put the sub menu items in the proper menus
  gtk_menu_append(GTK_MENU (fileMenu), loginItem);
  gtk_menu_append(GTK_MENU_SHELL (fileMenu), openItem);
  gtk_menu_append(GTK_MENU (fileMenu), quitItem);

  gtk_menu_shell_append(GTK_MENU_SHELL (songMenu), instrumentItem1);
  gtk_menu_shell_append(GTK_MENU_SHELL (userMenu), instrumentItem2);

  //setup the menu item call backs
<<<<<<< .merge_file_ZMpch0
  g_signal_connect(GTK_OBJECT(quitItem), "activate", G_CALLBACK(delete_event), gui);
  g_signal_connect(GTK_OBJECT(openItem), "activate", G_CALLBACK(click_open_song), gui);
=======
  g_signal_connect(GTK_OBJECT(quitItem), "activate", G_CALLBACK(delete_event), gui); // the data goes in the kevent, this bad but whatever
  g_signal_connect(GTK_OBJECT(openItem), "activate", G_CALLBACK(click_open_song), gui); // the data goes in the kevent, this bad but whatever
  g_signal_connect(GTK_OBJECT(loginItem), "activate", G_CALLBACK(click_login), gui); // the data goes in the kevent, this bad but whatever
>>>>>>> .merge_file_5rVZYp

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
  g_signal_connect(G_OBJECT(playButton), "button-press-event", G_CALLBACK(cb_play_song), gui);
  g_timeout_add(16, (GSourceFunc) cb_subdivision_beat, gui);

  //show the window
  gtk_widget_show_all(window);

  //set up the timer
  timer = g_timer_new();

  //graphics timer
  g_timeout_add(16, rotate, da);

  return(gui);
}

///////////////////////////////////
// EVENTS /////////////////////////
///////////////////////////////////

<<<<<<< .merge_file_ZMpch0

static void click_open_song(GtkWidget *widget, GdkEventKey *kevent, gpointer data) {

  // Get GUI and FILE_SELECTOR
  Gui* gui = (Gui*) data;
  Core* core = gui->core;
  GtkWidget *file_selector;
  
  printf("gui pointer address %p\n", gui);
  printf("core pointer address %p\n", core);
  
  file_selector = gtk_file_selection_new ("Please select a file for editing.");
  gui->filew = file_selector;

  // printf("current subdiv %d\n", core->current_subdiv);
=======
/*
 */
static void click_open_song(GtkWidget *widget, GdkEventKey *kevent, gpointer data) {

  // Get GUI and FILE_SELECTOR
  Gui* gui = (Gui*) kevent;
  GtkWidget *file_selector;
  file_selector = gtk_file_selection_new ("Please select a file for playing.");
  gui->filew = file_selector;

>>>>>>> .merge_file_5rVZYp

  // OK button -> store filename
  g_signal_connect(
    GTK_FILE_SELECTION (file_selector)->ok_button,
    "clicked",
    G_CALLBACK (cb_load_song),
    gui
   );

  // OK button -> close widget
  g_signal_connect_swapped(
    GTK_FILE_SELECTION (file_selector)->ok_button,
    "clicked",
    G_CALLBACK (gtk_widget_destroy),
    file_selector
   );

  // CANCEL button -> close widget
  g_signal_connect_swapped(
    GTK_FILE_SELECTION (file_selector)->cancel_button,
    "clicked",
    G_CALLBACK (gtk_widget_destroy),
    file_selector
  );

  // SHOW file selector
  gtk_widget_show (file_selector);
}

<<<<<<< .merge_file_ZMpch0
static gboolean button_press ( GtkWidget *widget, GdkEvent *event ) {
       if (event -> type == GDK_BUTTON_PRESS) {
           GdkEventButton *bevent = (GdkEventButton *) event;
           gtk_menu_popup (GTK_MENU (widget), NULL, NULL, NULL, NULL, bevent->button, bevent->time);
           return TRUE;
       }
       return FALSE;
}

=======

/*
 */
static void click_login(GtkWidget *widget, GdkEventKey *kevent, gpointer data) {
  // Get GUI and DIALOG
  Gui* gui = (Gui*) kevent;
  GtkWidget *dialog,
            *content_area;
  GtkButton *login;

  dialog = gtk_dialog_new();
  gtk_window_set_default_size(dialog, 300,150);

  // create all the fields
  gui->login->server_addr = gtk_entry_new();
  gui->login->server_port = gtk_entry_new();
  gui->login->username = gtk_entry_new();
  content_area = gtk_dialog_get_content_area (GTK_DIALOG (dialog));

  gtk_entry_set_text(gui->login->server_addr, "server address");
  gtk_entry_set_text(gui->login->server_port, "server port");
  gtk_entry_set_text(gui->login->username, "username");
  gtk_box_pack_start(content_area, gui->login->server_addr, TRUE, TRUE, 0);
  gtk_box_pack_start(content_area, gui->login->server_port, TRUE, TRUE, 0);
  gtk_box_pack_start(content_area, gui->login->username, TRUE, TRUE, 0);

  // create login button
  login = gtk_dialog_add_button(dialog, "Login", 1);

  // LOGIN button clicked -> call cb_server_login
  g_signal_connect(
    (GtkButton*) login,
    "clicked",
    G_CALLBACK (cb_server_login),
    gui
   );

  // LOGIN button clicked -> close dialog
   g_signal_connect_swapped( (GtkButton*) login, "clicked", G_CALLBACK (destroy), dialog );

  gtk_widget_show_all(dialog);
}


/*
 */
// static gboolean button_press ( GtkWidget *widget, GdkEvent *event ) {
//        if (event -> type == GDK_BUTTON_PRESS) {
//            GdkEventButton *bevent = (GdkEventButton *) event;
//            gtk_menu_popup (GTK_MENU (widget), NULL, NULL, NULL, NULL, bevent->button, bevent->time);
//            return TRUE;
//        }
//        return FALSE;
// }

>>>>>>> .merge_file_5rVZYp
/* CB_KEYPRESS is a piano callback function that is called everytime gtk responds to a keypress
 * from the user. When called, cb_keypress figures out which note the user is playing and if the note is not
 * currently being played it turns it off. If the escape key is pressed, the app will quit.
 */
static void cb_keypress(GtkWidget *widget, GdkEventKey *kevent, gpointer data){

  Gui* gui = (Gui*) data;
  Core* core = gui->core;
  int key = kevent->keyval;
  int note = core_keyboard_to_midi(core->keyboard_map, key);

<<<<<<< .merge_file_ZMpch0
  printf("gui pointer address %p\n", gui);

=======
>>>>>>> .merge_file_5rVZYp
  if (key == ESCAPE) { // escape key pressed
    core_destroy(core);
    gtk_main_quit();
  }
  else if (note != NOVALUE){
    increment_duration(note);

    if(!instrument_note_on(core->player, note)) {
       instrument_set_note_on(core->player->notes, note);
       print_keys_pressed(core);
       fluid_synth_noteon(core->synth, core->player->channel, note, 100);
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

/*
 */
static void cb_subdivision_beat(gpointer data) {

  Gui* gui = (Gui *) data;
  Core *core = gui->core;

  // Play the song as long as long as the current sub-division is greater than zero
  if (core->current_subdiv > 0){

    // Loop through all the notes and check to see if that note needs to be turned on or off
    for(int note = 0; note < 128; note++) {
      if (instrument_note_on(core ->song, note + core->current_subdiv *128)){
         increment_duration(note);
      }
      if (instrument_note_on(core ->player, note)){
         increment_duration(note);
      }
      else if(core -> current_subdiv % 80 == 0)
         delete_duration(note);
      if (instrument_first_note(core->song, note, core->current_subdiv)){
        fluid_synth_noteon(core->synth, core->song->channel, note, 100);
      }

      if (instrument_last_note(core->song, note, core->current_subdiv)){
        fluid_synth_noteoff(core->synth, core->song->channel, note);
      }

    }

    core->current_subdiv++;
  }

  // ONCE THE SONG IS OVER, BRING THE CURRENT_SUBDIV BACK TO ZERO
  if(core->current_subdiv >= (core->song->number_of_notes / 128))
    core->current_subdiv = 0;

}

/*
 */
static void cb_play_song(GtkWidget *widget, GdkEventKey *kevent, gpointer data){
  Gui* gui = (Gui*) data;
  Core* core = gui->core;
  core_play_song(core);
<<<<<<< .merge_file_ZMpch0
}

/*
 */
static void cb_load_song(GtkWidget *widget, gpointer g) {
  Gui* gui = (Gui *) g;
  GtkFileSelection *file_selector = gui->filew;
  char* selected_filename = gtk_file_selection_get_filename(file_selector);
  
  g_print("Selected filename: %s\n", selected_filename);
  printf("current subdiv: %d\n", gui->core->current_subdiv);
  // cb_load_song(gui->core, selected_filename);
}

=======
  set_zero();
}

/*
 */
static void cb_load_song(GtkWidget *widget, gpointer data) {
  Gui* gui = (Gui *) data;
  GtkFileSelection *file_selector = gui->filew;
  char* selected_filename = gtk_file_selection_get_filename(file_selector);
  core_load_song(gui->core, selected_filename);
}

/*
 */
static void cb_server_login(GtkWidget *widget, gpointer data) {
  Gui* gui = (Gui *) data;
  pthread_t client;

  client_connect(gui->client);
  //int iret1 = pthread_create(&client, NULL, client_listen, NULL);

  printf("server addr: %s\n", gtk_entry_get_text(gui->login->server_addr));
  printf("server port: %s\n", gtk_entry_get_text(gui->login->server_port));
  printf("username: %s\n", gtk_entry_get_text(gui->login->username));
  printf("server login\n");
}

void gui_txt_recv(Gui *gui, char *line){

}



>>>>>>> .merge_file_5rVZYp

///////////////////////////////////
// DESTROY ////////////////////////
///////////////////////////////////


static void destroy(GtkWidget *widget, gpointer data) {
<<<<<<< .merge_file_ZMpch0
  Gui *gui = (Gui *) data;
  gui_destroy(gui);
=======

>>>>>>> .merge_file_5rVZYp
  gtk_main_quit ();

}

/*
 */
static gboolean delete_event(GtkWidget *widget, GdkEvent  *event, gpointer data ) {
<<<<<<< .merge_file_ZMpch0

  g_print ("delete event occurred\n");
  Gui *gui = (Gui *) data;
  printf("gui pointer address %p\n", gui);
  // gui_destroy(gui);

  // FALSE => destroy window, TRUE => do nothing 
=======
  gtk_main_quit();
>>>>>>> .merge_file_5rVZYp
  return FALSE;
}


/* GUI_DESTROY frees the gui and associated memory
 */
void gui_destroy(Gui *gui){
  core_destroy(gui->core);
  free(gui);
}
