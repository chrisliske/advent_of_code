#include <stdio.h>
#include <string.h>

int main(void) {
    char str[20], *p, pair[3], pair2[3];
    int niceCount = 0, niceCount2 = 0, badToggle = 0;
    int vowelCount = 0, doubleCheck = 0, dupCheck = 0, totalCount = 0;
    pair[2] = NULL;
    pair2[2] = NULL;

    FILE *fp = fopen("input.txt", "r");
    if (!fp) {return 1; printf("no file");}
    
    while (fgets(str, 20, fp) != NULL) {
        totalCount++;
        doubleCheck = 0;
        dupCheck = 0;
        badToggle = 0; // reset 0=good 1=bad
       
        // does not include: ab, cd, pq, or xy
        // p = strstr(str, "ab");
        // if (p) {badToggle = 1;}
        // p = strstr(str, "cd");
        // if (p) {badToggle = 1;}
        // p = strstr(str, "pq");
        // if (p) {badToggle = 1;}
        // p = strstr(str, "xy");
        // if (p) {badToggle = 1;}
        
        // at least 3 vowels
        // vowelCount = 0;        
        // for (int i = 0; i < 17; i++) {
        //     if (str[i] == 'a') {vowelCount++;}
        //     if (str[i] == 'e') {vowelCount++;}
        //     if (str[i] == 'i') {vowelCount++;}
        //     if (str[i] == 'o') {vowelCount++;}
        //     if (str[i] == 'u') {vowelCount++;}
        // }
        // if (vowelCount < 3) {badToggle = 1;}
        
        // needs double letter
        // doubleCheck = 0;
        // for (int i = 1; i < 17; i++) {
        //     if (str[i-1] == str[i]) {doubleCheck = 1; break;}
        // }
        // if(!doubleCheck) {badToggle = 1;}



        // needs double double letter


        for (int i = 0; i < strlen(str); i++) {
            pair[0] = str[i];
            pair[1] = str[i+1];
            for (int j = 0; j < strlen(str); j++) {
                pair2[0] = str[j];
                pair2[1] = str[j+1];
                if (i != j && i != j+1) {                
                    if (strcmp(pair, pair2) == 0) {
                        doubleCheck++;
                    }
                }
            }
        }
        if (doubleCheck < 2) {badToggle = 1;}

        // repeating letter with one between like xyx or aaa
        for (int i = 0; i < strlen(str); i++) {
            if (str[i] == str[i+2]) {
                dupCheck = 1;
                printf("dupCheck: %d    i= %c   i+2=%c\n", dupCheck, str[i], str[i+2]);   
                break; 
            }
        }

        if (dupCheck < 1) {badToggle = 1;}



        printf("%d %s", badToggle, str);
        if (!badToggle) {niceCount++;}
    } //while
    
    fclose(fp);
    printf("Total counted: %d\n", totalCount);
    printf("niceCount: %d\n", niceCount);
    return 0;
} // main

/*
--- Day 5: Doesn't He Have Intern-Elves For This? ---
Santa needs help figuring out which strings in his text file are naughty or nice.

A nice string is one with all of the following properties:

It contains at least three vowels (aeiou only), like aei, xazegov, or aeiouaeiouaeiou.

It contains at least one letter that appears twice in a row, like xx, abcdde (dd), or aabbccdd (aa, bb, cc, or dd).

It does not contain the strings ab, cd, pq, or xy, even if they are part of one of the other requirements.
For example:

ugknbfddgicrmopn is nice because it has at least three vowels (u...i...o...), a double letter (...dd...), and none of the disallowed substrings.
aaa is nice because it has at least three vowels and a double letter, even though the letters used by different rules overlap.
jchzalrnumimnmhp is naughty because it has no double letter.
haegwjzuvuyypxyu is naughty because it contains the string xy.
dvszwmarrgswjxmb is naughty because it contains only one vowel.
How many strings are nice?

Part 2
Now, a nice string is one with all of the following properties:

It contains a pair of any two letters that appears at least twice in the string without overlapping, like xyxy (xy) or aabcdefgaa (aa), but not like aaa (aa, but it overlaps).
It contains at least one letter which repeats with exactly one letter between them, like xyx, abcdefeghi (efe), or even aaa.

*/
