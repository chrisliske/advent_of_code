#include <stdio.h>

int main(void) {

int x = 500, y = 500, x_santa = 500, y_santa = 500, x_robo = 500, y_robo = 500, uniqueCount = 0, totalCount = 0, toggle = 0, roboCount = 0, santaCount = 0;
char ch;
int map [1000] [1000];
FILE *fp;
fp = fopen("input.txt", "r");

// TODO: test if we are going to pass array length with travel

map [x_santa] [y_santa] = 1; // first present at starting pos

while ((ch = fgetc(fp)) != EOF) {
    // uniqueCount
    // if (ch == '<') {x--;}
    // if (ch == '^') {y++;}
    // if (ch == '>') {x++;}
    // if (ch == 'v') {y--;}
    totalCount++; // get total count to ensure we caputred them all
    //if (map[x] [y] == 0) {
        //map[x] [y] = 1; // Marks the location visited
        //uniqueCount++;  // and increments count only of its new
    //}
    // roboCount

    

    if (toggle == 0) {
        if (ch == '<') {x_santa--;}
        if (ch == '^') {y_santa++;}
        if (ch == '>') {x_santa++;}
        if (ch == 'v') {y_santa--;}
        if (map[x_santa] [y_santa] == 0){
            map[x_santa] [y_santa] = 1;
            santaCount++;
            toggle = 1;
        }
    }

    else if (toggle == 1) {
        if (ch == '<') {x_robo--;}
        if (ch == '^') {y_robo++;}
        if (ch == '>') {x_robo++;}
        if (ch == 'v') {y_robo--;}
        if (map[x_robo] [y_robo] == 0){
            map[x_robo] [y_robo] = 1;
            roboCount++;
            toggle = 0;
        }
    }
    
} // while
printf("santaCount = %d\n", santaCount);
printf("roboCount = %d\n", roboCount);
printf("%d houses visited at least once\n", santaCount + roboCount);
printf("%d moves made\n", totalCount);

fclose(fp);
} //main

// 2631?