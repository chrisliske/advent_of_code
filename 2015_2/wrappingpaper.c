#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void){

    FILE *fp;
    fp = fopen("input.txt", "r");

    char str[10];
    int length, width, height;
    int xCount = 0;
    int i = 0;
    char *container[3];
    int total = 0;
    int smallest = 0;
    int item = 0;
    int side1 = 0, side2 = 0, side3 = 0;
    int ribbon = 0, ribbon_temp = 0;

    
/*
Per reddit:
    Instead of a fixed-size buffer, fgets(), strtok(), and atoi(), you can just do this:
while (fscanf(fp, "%dx%dx%d\n", &length, &width, &height) == 3) {
    Also: there is never, ever any reason to use atoi(). It is a dumb function with no error checking.
Use strtol() or sscanf() instead.
*/


    while (fgets (str, 10, fp) != NULL) {
        //puts(str); // check output
        xCount++;
        i = 0;
        // look into fscanf options
        char *p = strtok (str, "x");
        while (p != NULL) {
            container[i++] = p;
            p = strtok(NULL, "x");
        }
        length = atoi(container[0]);
        width = atoi(container[1]);
        height = atoi(container[2]);
   
        side1 = length*width;  // = 2 x 3 = 6
        side2 = width*height;  // = 3 x 4
        side3 = height*length; // = 4 x 2
    
        ribbon_temp = 0;

        smallest = side1;
        ribbon_temp = (length*2) + (width*2) + (length*width*height);

        if (side2 < smallest) {
            smallest = side2;
            ribbon_temp = (width*2) + (height*2) + (length*width*height);
        }
        if (side3 < smallest) {
            smallest = side3;
            ribbon_temp = (height*2) + (length*2) + (length*width*height);
        }

        item = (side1*2) + (side2*2) + (side3*2) + smallest;
        ribbon = ribbon + ribbon_temp;
        total = total + item;

        



        printf("Length: %d, Width: %d, Height: %d, wrap: %d, smallest: %d, total: %d, ribbon: %d\n", length, width, height, item, smallest, total, ribbon);
    } 

    printf("Total amout to order: %d\n", total);
    printf("Count: %d\n", xCount);
    fclose(fp);
} //main