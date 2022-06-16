#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// returns the number of words in the buffer
int wordCount (char *str) {
  int count = 0;
  for (int i = 0; str[i] != '\0'; i++) {
    if (str[i] == ' ' && str[i+1] != ' ')
    count++;
  }
  return count + 1;
}

int main (void) {
    int grid[1000] [1000] = {0};
    int function = 0; // 0 = none, 1 = on, 2 = off, 3 = toggle
    int counter = 0, processed = 0, x_start = 0, y_start = 0, x_end = 0, y_end = 0;
    char str[40], format_string[10], start_string[10], end_string[10], *ptr; 
    char x_start_string[4], y_start_string[4], x_end_string[4], y_end_string[4];


    FILE *fp = fopen("input.txt", "r");
    if (!fp) {return 1; printf("no file found");}

    while (fscanf(fp, "%[^\n] ", str) != EOF) {

      // parse the string into usable variables
      if (wordCount(str) == 4) {
        function = 3;
        sscanf (str, "%*s %s %*s %s", start_string, end_string);
      }
      if (wordCount(str) == 5) {
        sscanf (str, "%*s %s %s %*s %s\n", format_string, start_string, end_string);
        if (strcmp(format_string, "on") == 0) {function = 1;}
        else if (strcmp(format_string, "off") == 0) {function = 2;}
      } 
      sscanf (start_string, "%[^,], %s", x_start_string, y_start_string);
      x_start = strtol(x_start_string, &ptr, 10);
      y_start = strtol(y_start_string, &ptr, 10);
      sscanf (end_string, "%[^,], %s", x_end_string, y_end_string);
      x_end = strtol(x_end_string, &ptr, 10);
      y_end = strtol(y_end_string, &ptr, 10);
      //printf("Function: %d  xs%d  ys%d  xe%d  ye%d\n", function, x_start, y_start, x_end, y_end);

      // update current range into the grid with current function
      for (int y = y_start; y <= y_end; y++) {
        for (int x = x_start; x <= x_end; x++) {
          if (function == 1) {grid [x][y] = 1;}
          else if (function == 2) {grid [x][y] = 0;}
          else if (function == 3) {
            if (grid [x][y] == 0) {grid [x][y] = 1;}
            else if (grid [x][y] == 1) {grid [x][y] = 0;}
          }
        }
      }
    processed++;
    } // while

    // get the count from grid
    for (int y = 0; y <= 999; y++) {
      for (int x = 0; x <= 999; x++) {
        if (grid [x][y] == 1) {counter++;}
      }
      printf("\n");
    }

    printf("\n%d lights are lit out of %d lines processed\n", counter, processed);
    fclose(fp);
    return 0;
} //main

/*

--- Day 6: Probably a Fire Hazard ---
Because your neighbors keep defeating you in the holiday house decorating contest 
year after year, you've decided to deploy one million lights in a 1000x1000 grid.

Furthermore, because you've been especially nice this year, Santa has mailed you 
instructions on how to display the ideal lighting configuration.

Lights in your grid are numbered from 0 to 999 in each direction; the lights at 
each corner are at 0,0, 0,999, 999,999, and 999,0. The instructions include whether 
to turn on, turn off, or toggle various inclusive ranges given as coordinate pairs. 
Each coordinate pair represents opposite corners of a rectangle, inclusive; a 
coordinate pair like 0,0 through 2,2 therefore refers to 9 lights in a 3x3 square. 
The lights all start turned off.

To defeat your neighbors this year, all you have to do is set up your lights by 
doing the instructions Santa sent you in order.

For example:

turn on 0,0 through 999,999 would turn on (or leave on) every light.
toggle 0,0 through 999,0 would toggle the first line of 1000 lights, turning off the 
ones that were on, and turning on the ones that were off.
turn off 499,499 through 500,500 would turn off (or leave off) the middle four 
lights.

After following the instructions, how many lights are lit? 543903 correct answer

PART 2

You just finish implementing your winning light pattern when you realize you 
mistranslated Santa's message from Ancient Nordic Elvish.
The light grid you bought actually has individual brightness controls; each light 
can have a brightness of zero or more. The lights all start at zero.

The phrase turn on actually means that you should increase the brightness of those 
lights by 1.

The phrase turn off actually means that you should decrease the brightness of those 
lights by 1, to a minimum of zero.

The phrase toggle actually means that you should increase the brightness of those 
lights by 2.

What is the total brightness of all lights combined after following Santa's 
instructions?

For example:
turn on 0,0 through 0,0 would increase the total brightness by 1.
toggle 0,0 through 999,999 would increase the total brightness by 2000000.
*/