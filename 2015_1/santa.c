#include <stdio.h>

int main (void) {

    FILE *fp;
    fp = fopen("./input.txt", "r");
    if(fp) {

        char buffer[1] = {0};
        int count = 0;
        int floor = 0;
        int firstBasement = 0;
        while(fread(buffer, sizeof(char), sizeof(char), fp) != 0) {
        //to some byte stuff
        printf("char: %c\n", buffer[0]);

        if (buffer[0] == '(') {floor++;}
        if (buffer[0] == ')') {floor--;}
        count++;
            if (floor == -1) {
                firstBasement = count;
                break;
            }

        }
    printf("Total Length checked: %d\n", count);
    printf("Final floor: %d\n", floor);
    printf("Position of first basement entry: %d\n", firstBasement);
    }


    fclose(fp);
} //main