/**
 * @file patternMatching.c
 * @author Christodoulos Constantinou
 * @brief This program calculates the distance between two string sequences, 
 *  which is the minimum number of single-character edits (insertions, deletions or substitutions) required to change one word into the other
 * @version 1.0
 * @date 2022-10-16
 * 
 * 
 * 
 */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

//Macro definition to distinguish the smallest number between 3 integers
#define MIN3(a, b, c) ((a) < (b) ? ((a) < (c) ? (a) : (c)) : ((b) < (c) ? (b) : (c)))

//FUNCTION BODY DECLARATION
int stringEvresisDistance(char *s1,int s1len, char *s2, int s2len) ;

/**
 * @brief This function calculates the minimum number of single-character edits (insertions, deletions or substitutions) required to change one word into the other
 * 
 * @param s1 first string 
 * @param s1len first string's length
 * @param s2  second string
 * @param s2len second string's length
 * @return int Minimum edits required to convert one string to the other  
 */
int stringEvresisDistance(char *s1,int s1len, char *s2, int s2len){
    unsigned int x, y, lastdiag, olddiag;
    unsigned int column[s1len + 1];

    for (y = 1; y <= s1len; y++)
        column[y] = y;
    for (x = 1; x <= s2len; x++) {
        column[0] = x;
        for (y = 1, lastdiag = x - 1; y <= s1len; y++) {
            olddiag = column[y];
            column[y] = MIN3(column[y] + 1, column[y - 1] + 1, lastdiag + (s1[y-1] == s2[x - 1] ? 0 : 1));
            lastdiag = olddiag;
        }
    }
   
    return column[s1len];
}
/**
 * @brief This is the main function of the program it takes two txt files as command line arguements and then calls the stringEvresisFunction in order to 
 * calculate the distance between the two strings contained in the input txt files.
 * 
 * @param argc 
 * @param argv 
 */
void main(int argc, char* argv[]){ 
    //Reading 1st string from the first arguement text file and storing it
    FILE *fp = fopen(argv[1], "r");

    //Checking if first file pointer is null
    if (fp == NULL) {
        printf("ERROR!!! The first text file given as an arguement does not exist\n");
    }

    //this char stores each character from the 1st input .txt file that contains the 1st string
	char chr;
    //this integer contains the value of the first string length
	int temp = 0;
	while(fscanf(fp,"%c",&chr) != EOF){
		temp++;
	}
    
    //printf("first string length is %d.\n",temp); //for testing purposes
    fclose(fp);

    //Char Pointer s1 points to dynamic char array str1 to store the first string from the 1st input file 
	char str1;
    char *s1;
    s1 = (char *)malloc((sizeof(char) * temp));

    if(s1 == NULL){
        printf("MEMORY CANNOT BE ALLOCATED");
    }

	fp = fopen(argv[1], "r");
	int i = 0;

	while(fscanf(fp,"%c",&str1) != EOF){
		s1[i] = str1;
        i++;
	}
    i++; // '\0'

    //Free allocated memory for pointer char s1
    //free(s1);
    //Closes first file pointer
    fclose(fp);

    //Reading 2nd string from the second arguement text file and storing it
    FILE *fp2 = fopen(argv[2], "r");
    //Checking the second file pointer is null
    if (fp2 == NULL) {
        printf("ERROR!!! The second text file given as an arguement does not exist\n");
    }

    //this char stores each character from the 2nd input file that contains the 2nd string
    char chr2;
    int temp2 = 0;

    while(fscanf(fp2,"%c",&chr2) != EOF){
        temp2++;
    }

    //printf("second string length is %d.\n",temp2); //for testing purposes

    //Char Pointer s2 points to dynamic char array str2 to store the second string from the 2nd input file
    char str2;
    char *s2;
    s2 = (char *)malloc((sizeof(char) * temp2));

    if(s2 == NULL){
        printf("MEMORY CANNOT BE ALLOCATED");
    }

    fp2 = fopen(argv[2], "r");
    int j = 0;

    while(fscanf(fp2,"%c",&str2) != EOF){
        s2[j] = str2;
        j++;
    }
    j++; // '\0'

    //Closes second file pointer
    fclose(fp2);

    //Printing the strings for testing purposes
    /**
     *  for(i=0; i<temp; i++){
        printf("%c\t",s1[i]);
    }
    printf("\n");
    for(i=0; i<temp2; i++){
        printf("%c\t",s2[i]);
    }
    printf("\n");
     */
   
    int d = stringEvresisDistance(s1, temp, s2, temp2);
    printf("Minimum edits required to convert is: %d.\n", d);
    
}

