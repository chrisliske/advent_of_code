#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// use of unsigned short to limit expected range: 0 to 65535 for not operations
unsigned short wires_a_int[340] = {0};
unsigned short wires_b_int[340] = {0};
unsigned short wires_out_int[340] = {0};

int solvedCount = 0;
int inputType[340] = {0};
char wires_a[340][10];
int wires_a_solved_flag[340] = {0};
char wires_b[340][10];
int wires_b_solved_flag[340] = {0};
char wires_out[340][10];
int wires_out_solved_flag[340] = { 0 };
char operators[340][7];
int lineCount = 0;
char str[25];
char wire_a[3], operator[7], wire_b[3], wire_out[3];
char *ptr;

// counts the number of wires_out_solved_flag and returns
int countSolvedFlags() {
    int solved = 0;
    for (int i = 0; i < lineCount; i++)
    {
        if (wires_out_solved_flag[i] == 1) {solved++;}
    }
    return solved;
}

// returns the number of words in the buffer
int wordCount (char *str) {
  int count = 0;
  for (int i = 0; str[i] != '\0'; i++) {
    if (str[i] == ' ' && str[i+1] != ' ')
    count++;
  }
  return count + 1;
}

// prints out the contents of all the arrays
void printArrays (void) {
    solvedCount = 0;
    for (int i = 0; i < lineCount; i++)
    {
        printf ("%d. ", i+1);
        printf ("[type: %d] ", inputType[i]);
        printf ("[solved: %d%d%d] ", wires_a_solved_flag[i], wires_b_solved_flag[i], wires_out_solved_flag[i]);
        printf ("[a: %s] ", wires_a[i]);
        printf ("[a_int: %d] ", wires_a_int[i]);
        printf ("[op: %s] ", operators[i]);
        printf ("[b: %s] ", wires_b[i]);
        printf("[b_int: %d] ", wires_b_int[i]);
        printf ("[out: %s] ", wires_out[i]);
        printf ("[out_int: %d]\n", wires_out_int[i]);
        if (wires_out_solved_flag[i]) {solvedCount++;}
    }   
        printf ("lineCount=%d   solvedCount=%d   line 79 ('a')=%d\n", lineCount, solvedCount+1, wires_out_int[78]);
} //printArrays

// reads the contents of file into the arrays
int fileToArrays() {
    FILE *fp = fopen("input.txt", "r");
    if (!fp) {return 1; printf("no file found");}
    while (fscanf(fp, "%[^\n] ", str) != EOF) {
        if (wordCount(str) == 5) {sscanf (str, "%s %s %s %*s %s", wire_a, operator, wire_b, wire_out);
            strcpy (operators[lineCount], operator);
            strcpy (wires_b[lineCount], wire_b);
            inputType[lineCount] = 5;
        }
        if (wordCount(str) == 3) {
            sscanf (str, "%s %*s %s", wire_a, wire_out);
            strcpy (operators[lineCount], "DIRECT");
            strcpy (wires_b[lineCount], "\0"); // wire b not used so populate with null. redundant?
            inputType[lineCount] = 3;
        }
        if (wordCount(str) == 4) {
            sscanf (str, "%s %s %*s %s", operator, wire_a, wire_out);
            strcpy (operators[lineCount], operator);
            strcpy (wires_b[lineCount], "\0"); // wire b not used so populate with null. redundant?
            inputType[lineCount] = 4;
            }
        strcpy (wires_a[lineCount], wire_a);
        strcpy (wires_out[lineCount], wire_out);
        lineCount++;
    }
    fclose (fp);
} //fileToArrays

// run through wires_a populating wires_a_int if we can
void populate_wires_a_int () {
    for (int i = 0; i < lineCount; i++) {
        int j = 0; // define or reset char counter
        while (wires_a[i][j]) { // run through string[j] til null
            if (!isalpha(wires_a[i][j])) {
                wires_a_int[i] = strtol(wires_a[i], &ptr, 10); // convert and populate wires_a_int
                wires_a_solved_flag[i] = 1; 
                break; // done, no need to keep checking 
            }
            j++;
        } //while
    } //for
}

// run through wires_b populating wires_b_int if we can
void populate_wires_b_int () {
    for (int i = 0; i < lineCount; i++) {
        int j = 0; // define or reset char counter
        while (wires_b[i][j]) { // run through string[j] til null
            if (!isalpha(wires_b[i][j])) {
                wires_b_int[i] = strtol(wires_b[i], &ptr, 10); // convert and populate wires_a_int
                wires_b_solved_flag[i] = 1;
                break; // done, no need to keep checking 
            }
            j++;
        } //while
    } //for
}

// if input type 3 and a[0] is digit, update solved flag and out_int
void trySolveForType3() {
    for (int i = 0; i < lineCount; i++)
    {
        if (inputType[i] == 3 && isdigit(wires_a[i][0])) {
            wires_out_solved_flag[i] = 1;
            wires_out_int[i] = wires_a_int[i];
        }
    }
}

// run through the list. If we have any solved, go through and replace any other
// instances of wire found (string compare from solved to a and b). Update flags   
void checkXX1andUpdate() {
    for (int i = 0; i < lineCount; i++)
    {
        if (wires_out_solved_flag[i]) { // this one is solved so we can grab the out string
            for (int j = 0; j < lineCount; j++) { // and recurse through again to make the changes
                if (!strcmp(wires_out[i], wires_a[j])) { // match
                    wires_a_int[j] = wires_out_int[i];
                    wires_a_solved_flag[j] = 1; // update flag
                }
                if (!strcmp(wires_out[i], wires_b[j])) { // match
                    wires_b_int[j] = wires_out_int[i];
                    wires_b_solved_flag[j] = 1; // update flag
                }        
            } //for
        } //if
    } //for
}

void check110AndSolve() {
    for (int i = 0; i < lineCount; i++)
    {
        if (wires_a_solved_flag[i] && wires_b_solved_flag[i] && !wires_out_solved_flag[i]) { // if 110
            // TODO: check logical possibilities of differnt input types for each op
            if (  (!strcmp (operators[i], "AND")  )  ) {wires_out_int[i] = wires_a_int[i] & wires_b_int[i];}
            if (  (!strcmp (operators[i], "OR")  )  ) {wires_out_int[i] = wires_a_int[i] | wires_b_int[i];}
            if (  (!strcmp (operators[i], "RSHIFT")  )  ) {wires_out_int[i] = wires_a_int[i] >> wires_b_int[i];}
            if (  (!strcmp (operators[i], "LSHIFT")  )  ) {wires_out_int[i] = wires_a_int[i] << wires_b_int[i];}
            wires_out_solved_flag[i] = 1;
        }
        // not will never get 110 so we check them here for 100+not
        else if (  (!strcmp (operators[i], "NOT") && wires_a_solved_flag[i]  )  ) {
            wires_out_int[i] = ~wires_a_int[i];
            wires_out_solved_flag[i] = 1;
        }
        // catch the input type 3 (DIRECT) conditions
        else if (inputType[i] == 3 && !strcmp (operators[i], "DIRECT")  ) {wires_out_solved_flag[i] = 1;}
    }
}

int main () {

    fileToArrays();
    populate_wires_a_int();
    populate_wires_b_int();

    // overide 'b' with 'a' for part 2
    wires_out_int[55-1] = 16076;
    wires_a_int[55-1] = 16076;

    trySolveForType3();

    while (solvedCount != 339) {
        checkXX1andUpdate();
        check110AndSolve();
        solvedCount = countSolvedFlags();
        printf ("%d\n", solvedCount);
    }

    // lazy cop out solution for the only type 3 DIRECT. Why bother
    wires_out_int[79-1] = wires_out_int[199-1];
    // Part 1 output: 'a' = 16076
    printArrays();

    return 0;
} //main

/*
SOLVED FLAGS: 111 [wires_a_Solved_flag][wires_b_solved_flag][wires_out_solved_flag]
(101's are NOT, therefor no b)

INPUT TYPES:
    lf AND lq -> ls     [5]
    iu RSHIFT 1 -> jn   [5]
    1 AND io -> ip      [5]
    19138 -> b          [3]
    lx -> a             [3]
    NOT el -> em        [4]

--- Part Two ---
Now, take the signal you got on wire a, override wire b to that signal, 
and reset the other wires (including wire a). What new signal is ultimately 
provided to wire a?
*/