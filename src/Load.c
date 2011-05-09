#include "Load.h"

static void set_empty_array(int *notes_array, int length);
static void update_song(int midi, int start, double duration , int *song);
static void condition_update (char note, double prev, int count, int notation, int octcount, double number, int *notes_array);
static int note_cmp(char note, int* rel_note, int octcount, int rel_octcount);

//opens the file and calculates the length of the song
//returns the length as a double value.
int song_length(char* const file) {
  char relative[100];
  char relative_note[10];
  char c;

  double tot_len = 0;
  double number = 0;
  double prev = 0;
  int shift = 0;

  FILE* song_file = fopen(file, "r");

  while ((c = fgetc(song_file)) != EOF) {

    // UPDATE VALUES
    if ((c == ' ' || c == '\n') && shift == 1) {
      tot_len += (number == 0) ? (1 / prev) : (1 / number);
      prev = (number == 0) ? prev : number;
      number = 0;
      shift = 0;
    }

    // PARSE CHARACTER
    else {

      // dot
      if (c == '.'){
        number /= 1.5; 
      }

      // relative note
      else if (c == '\\') {
        fscanf(song_file, "%s%s %c ", relative, relative_note, &c);
        if (strcmp(relative, "relative") || c != '{') {
          fprintf(stderr, "ERROR: MISSPELLING\n");
        }
      }

      // pause
      else if (shift == 0 && ((c >= 'a' && c <= 'g') || c == 'r')) {
        shift++;
      }

      // get number
      else if (c >= '0' && c <= '9' && number == 0) {
        number = c - '0';
      } else if (c >= '0' && c <= '9') {
        number = number * 10 + (c - '0');
      }

      // read in } and do nothing 
      else if (c == '}') {}

      // fail if we don't know what to do with the character
      else {
        // printf("fail %c\n", c);
      }
    }
  }

  fclose(song_file);
  return (tot_len * SUBDIV * NUM_MIDI);
}



//sets the array as empty
static void set_empty_array(int *notes_array, int length) {
      for(int i = 0; i < length; i ++)
          notes_array[i] = 0;
}

//updates the song
static void update_song(int midi, int start, double duration , int *notes_array) {
     duration = (1 / duration) * SUBDIV;
     for(int i = 0; i < (duration - 1); i ++)
          notes_array[(midi + (start + i) * NUM_MIDI)] = 1;
     notes_array[(int)(midi + (duration + start - 1) * NUM_MIDI)] = 2;
     printf("\n");
}

//prints the song
void print_song(int *notes_array, int length) {
    for(int i = 0; i < length; i ++) {
       printf("%i ", notes_array[i]);
       if (i%128 == 127)
       printf("\n");
    }
}

//updates the condition
static void condition_update(char note, double prev, int count, int notation, int octcount, double number, int *notes_array) {

     int midi;

     midi = core_note_to_midi(note, octcount, notation);
     //printf("note %c, octcount %i, number %f, prev %f, midi %i \n", note, octcount, number, prev, midi);
     if (number == 0)
         update_song(midi, count, prev, notes_array);
     else
         update_song(midi, count, number, notes_array);
}

//finds the nearest octave for the note
static int note_cmp(char note, int* rel_note, int octcount, int rel_octcount) {
    double low_midi;
    double high_midi;
    double reg_midi;

    low_midi = core_note_to_midi(note, rel_octcount - 1, 0);
    reg_midi = core_note_to_midi(note, rel_octcount, 0);
    high_midi = core_note_to_midi(note, rel_octcount + 1, 0);

    if(*rel_note > reg_midi) {
          if((*rel_note - reg_midi) > (high_midi - *rel_note)) {
             octcount ++;
             high_midi += octcount * 12;
             rel_note = (int *) &high_midi;
          }
    }
    else if (*rel_note < reg_midi) {
          if((reg_midi - *rel_note) > (*rel_note - low_midi)) {
             octcount --;
             low_midi += octcount * 12;
             rel_note = (int *) &low_midi;
          }
    }
    else
          rel_note = (int *) &reg_midi;
          
    return (octcount + rel_octcount);

}

//parses the song. needs a file because its a waste to close and open
//a file twice. its always not good coding to create an array with a
//local function and send the address.
void parse_song(char* const file, int *notes_array, int length) {
  char c;
  char pr = ' ';
  char note;
  char relative[100];

  double prev = 0;//previous duration
  int rel = 0;//relative switch
  int rel_note = 0; //relative midi note value
  int *rel_p;
  int rel_octcount = 0;
  int count = 0;

  int notation = 0;
  int shift = 0;
  int octcount = 0;
  double number = 0;
  
  FILE* song_file = fopen(file, "r");
  rel_p = &rel_note;
  set_empty_array(notes_array, length);

  while((c = fgetc(song_file)) != EOF) {
    if( (c == ' ' || c == '\n') && pr != '{') {
      if (shift >= 1) {
        printf("%c\n", note);
        if (note != 'r') {
          if (shift == 2) {
            rel_note = core_note_to_midi(note, octcount, notation);
            rel_octcount = octcount;
          }
          else if (rel == 1) {
            rel_octcount = note_cmp(note, rel_p, octcount, rel_octcount);
            condition_update(note, prev, count, notation, rel_octcount, number, notes_array);
            rel_note = core_note_to_midi(note, rel_octcount, notation);
          }
          else
            condition_update(note, prev, count, notation, octcount, number, notes_array);
        }        
        printf("rel_note %i, note %i, octcount %i, number %f, rel_count %i\n", rel_note, note, octcount, number, rel_octcount);
        if(number != 0 && shift != 2) {
          count += (1 / number) * SUBDIV;
          prev = number;
        }
        else if(shift != 2)
          count += (1 / prev) * SUBDIV;
        number = 0;
        octcount = 0;
        shift = 0;
        notation = 0;
        pr = c;
      }
    }
    else {
      if (c == '\'')
        octcount++;
      else if (c == '.')
        number /= 1.5;
      else if (c == '}')
        rel = 0;
      else if (c == ',')
        octcount--;
      else if (c == 'i' && shift == 1)
        notation = 1;
      else if (c == 'e' && shift == 1)
        notation = -1;
      else if (c == '\\') {
        fscanf(song_file, "%s %c ", relative, &c);
        if (!strcmp(relative,"relative")) {
          rel = 1;
          shift = 2;
        }
        else
          fprintf(stderr, "ERROR: MISSPELLING\n");
      }
      else if (shift == 0 && ( (c >= 'a' && c <= 'g') || c == 'r') ) {
        note = c;
        shift++;
      }
      else if (c >= '0' && c <= '9' && number == 0)
        number = c - '0';
      else if (c >= '0' && c <= '9')
        number = number * 10 + (c - '0');
      else if (c == '%' && pr == '\n')
        for(char ch = ' '; ch != '\n' && ch != EOF; ch = fgetc(song_file));
    }
  }

  fclose(song_file);
}

