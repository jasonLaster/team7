#include <stdio.h>

#include "Support.h"

/* SUPPORT_LINES_IN_FILE is a simple helper function that 
 * returns the number of lines in a file
*/

int support_lines_in_file(const char* file_name){
  int lines = 1;
  char c;
  FILE *source = fopen(file_name, "r");
  
  while((c = fgetc(source)) != EOF) {
    if(c == '\n') lines++;
  }
  
  fclose(source);
  return lines;
}
