/********************************************************************************* 
* Lex.c
* Implementation of indirectly alphabetize the lines in a file by using List ADT
*********************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include "List.h"

#define MAX_LEN 300

int main(int argc, char * argv[]){

    int line_count;
    FILE *in, *out;
    char line[MAX_LEN];
    // char tokenBuffer[MAX_LEN];
    // char* token;
    List newL = newList();
    int index1 = 0;
    // check command line for correct number of arguments
    if( argc != 3 ){
        printf("Usage: %s <input file> <output file>\n", argv[0]);
        exit(1);
    }

    // open files for reading and writing 
    in = fopen(argv[1], "r");
    if( in==NULL ){
        printf("Unable to open file %s for reading\n", argv[1]);
        exit(1);
    }

    out = fopen(argv[2], "w");
    if( out==NULL ){
        printf("Unable to open file %s for writing\n", argv[2]);
        exit(1);
    }

    // read each line of input file, then count and print tokens
    line_count = 0;
    while( fgets(line, MAX_LEN, in) != NULL)  {
        line_count++;
    }
    if (line_count == 0) {
        return(0);
    }
    rewind(in);
    char** array = (char**)malloc(sizeof(char*)*line_count);
    while( fgets(line, MAX_LEN, in) != NULL)  {
        array[index1] = (char*)malloc(sizeof(char)*MAX_LEN);
        strcpy(array[index1], line);
        index1++;
    }
    prepend(newL, 0);
    for (int i = 1; i < line_count; i++) {
        moveFront(newL);
        for (int j = 0; j < i; j++) {
            if (strcmp(array[i], array[get(newL)]) < 0) {
                insertBefore(newL, i);
                break;
            } else if (index(newL) == i - 1) {
                append(newL, i);
                break;
            } else {
                moveNext(newL);
            }
        }
    }
    // Node N = NULL;
    // for (N = newL->front; N != NULL; N = N->next) {
    //   fprintf(out, "%s ", N->data);
    // }
    moveFront(newL);
    while(length(newL) != 0) {
        fprintf(out, "%s", array[get(newL)]);
        moveNext(newL);
        deleteFront(newL);
    }
    clear(newL);
    freeList(&newL);
    for (int k = 0; k < line_count; k++) {
        free(array[k]);
        array[k] = NULL;
    }
    free(array);
    array = NULL;
    // close files 
    fclose(in);
    fclose(out);

    return(0);
}
