/********************************************************************************* 
* ListTest.c 
* Test cases for List ADT 
*********************************************************************************/
#include "List.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    List A = newList();
    List B = newList();
    List C = newList();
    int X[] = {1,3,5,7,9,11,13,15,17,19,21,23,25,27,29,31};
    int i;
    int u = -4;
    int v = -8;
    int w = -10;
    int equal = 0;

    for (i = 1; i <= 15; i++) {
        append(A, &X[i]);
        prepend(B, &X[i]);
    }
    // print both lists of integers in forward direction
    for(moveFront(A); index(A)>=0; moveNext(A)){
        printf("%d ", *(int*)get(A));
    }
    printf("\nA front: %d", *(int*)front(A));
    printf("\n");
    for(moveFront(B); index(B)>=0; moveNext(B)){
        printf("%d ", *(int*)get(B));
    }
    printf("\nB front: %d", *(int*)front(B));
    printf("\n");

    // print both lists of integers in backward direction
    for(moveBack(A); index(A)>=0; movePrev(A)){
        printf("%d ", *(int*)get(A));
    }
    printf("\nA back: %d", *(int*)back(A));
    printf("\n");
    for(moveBack(B); index(B)>=0; movePrev(B)){
        printf("%d ", *(int*)get(B));
    }
    printf("\nB back: %d", *(int*)back(B));
    printf("\n");

    // make a shallow copy of A
    moveFront(A);
    while( index(A)>=0 ){
        append(C, get(A));
        moveNext(A);
    }

    // print the copy in forward direction
    for(moveFront(C); index(C)>=0; moveNext(C)){
        printf("%d ", *(int*)get(C));
    }
    printf("\nC front: %d", *(int*)front(C));
    printf("\nC back: %d", *(int*)back(C));
    printf("\n");

    // check shallow equality of A and C by comparing pointers
    equal = (length(A)==length(C));
    moveFront(A);
    moveFront(C);
    while( index(A)>=0 && equal){
        equal = ( get(A)==get(C) );
        moveNext(A);
        moveNext(C);
    }
    printf("A equals C is %s\n", (equal?"true":"false") );
    
    moveFront(A);
    insertAfter(A, &u);
    moveNext(A);
    moveNext(A);
    insertBefore(A, &v);
    delete(A);
    deleteFront(A);
    deleteBack(A);
    for(moveFront(A); index(A)>=0; moveNext(A)){
        printf("%d ", *(int*)get(A));
    }
    printf("\n");
    moveFront(A);
    moveNext(A);
    set(A, &w);
    for(moveFront(A); index(A)>=0; moveNext(A)){
        printf("%d ", *(int*)get(A));
    }
    printf("\n");

    clear(A);
    printf("%d\n", length(A));
    printf("%d\n", length(B));
    freeList(&A);
    freeList(&B);
    freeList(&C);
    return(0);
}
/*
Output of this program:
3 5 7 9 11 13 15 17 19 21 23 25 27 29 31 
A front: 3
31 29 27 25 23 21 19 17 15 13 11 9 7 5 3 
B front: 31
31 29 27 25 23 21 19 17 15 13 11 9 7 5 3 
31A back: 
3 5 7 9 11 13 15 17 19 21 23 25 27 29 31 
B back: 3
3 5 7 9 11 13 15 17 19 21 23 25 27 29 31 
C front: 3
C back: 31
A equals C is true
-4 -8 7 9 11 13 15 17 19 21 23 25 27 29 
-4 -10 7 9 11 13 15 17 19 21 23 25 27 29 
0
15
*/