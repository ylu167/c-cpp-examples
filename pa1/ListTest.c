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
  List C = NULL;
  List D = newList();
  List E = NULL;
  int i;

  for (i = 1; i <= 50; i++) {
    append(A, i);
    prepend(B, i);
  }
  printf("TEST 1-----------------------------------------------------\n");
  printList(stdout, A);
  printf("\n");
  printList(stdout, B);
  printf("\n");

  for (moveFront(A); index(A) >= 0; moveNext(A)) {
    printf("%d ", get(A));
  }
  printf("\n%d", front(A));
  printf("\n");
  for (moveBack(B); index(B) >= 0; movePrev(B)) {
    printf("%d ", get(B));
  }
  printf("\n%d", front(B));
  printf("\n");

  C = copyList(A);
  printf("%s\n", equals(A, B) ? "true" : "false");
  printf("%s\n", equals(B, C) ? "true" : "false");
  printf("%s\n", equals(C, A) ? "true" : "false");
  printf("%s\n", equals(C, C) ? "true" : "false");

  moveFront(A);
  for (i = 0; i < 5; i++)
    moveNext(A);       // at index 5
  insertBefore(A, 1); // at index 6
  for (i = 0; i < 9; i++)
    moveNext(A); // at index 15
  insertAfter(A, 2);
  for (i = 0; i < 5; i++)
    movePrev(A); // at index 10
  delete (A);
  printList(stdout, A);
  printf("\n");
  printf("%d\n", length(A));

  clear(A);
  printf("%d\n", length(A));
  moveBack(B);
  for (i = 0; i < 20; i++)
    deleteFront(B); // at index 10
  delete(B);
  deleteBack(B);
  printList(stdout, B);
  printf("\n");
  printf("%d\n", length(B));
  freeList(&A);
  freeList(&B);
  freeList(&C);

  printf("TEST 2-----------------------------------------------------\n");
  append(D, 0);
  append(D, 1);
  prepend(D, 2);
  append(D, 3);
  prepend(D, 4);
  printList(stdout, D);
  printf("\n");
  printf("%d\n", length(D));
  moveFront(D);
  printf("%d ",index(D));
  printf("%d\n",get(D));
  moveNext(D);
  moveNext(D);
  printf("%d ",index(D));
  printf("%d\n",get(D));
  movePrev(D);
  printf("%d ",index(D));
  printf("%d\n",get(D));
  moveBack(D);
  printf("%d ",index(D));
  printf("%d\n",get(D));
  set(D, 7);
  printf("%d ",index(D));
  printf("%d\n",get(D));
  E = copyList(D);
  printf("%s\n", equals(D, E) ? "true" : "false");
  moveFront(E);
  insertAfter(E, 8);
  moveNext(E);
  moveNext(E);
  insertBefore(E, 5);
  printList(stdout, E);
  printf("\n");
  delete(E);
  deleteFront(E);
  deleteBack(E);
  printList(stdout, E);
  printf("\n");
  printf("%s\n", equals(D, E) ? "true" : "false");
  printf("%d\n", front(E));
  printf("%d\n", back(E));
  printf("%d\n", length(E));
  return (0);
}

/*
Output of this program:
TEST 1-----------------------------------------------------
1 - 50
50 - 1
1 - 50
1
1 - 50
50
false
false
true
true
1 2 3 4 5 1 6 7 8 9 11 12 13 14 15 2 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49 50
51
0
30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3
28
TEST 2-----------------------------------------------------
4 2 0 1 3
5
0 4
2 0
1 2
4 3
4 7
true
4 8 5 2 0 1 7
8 5 0 1
false
8
1
4
*/