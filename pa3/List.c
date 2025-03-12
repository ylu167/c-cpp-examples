/********************************************************************************* 
* List.c
* Implementation file for List ADT
*********************************************************************************/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<assert.h>
#include<stdbool.h>
#include "List.h"
// structs --------------------------------------------------------------------

// private Node type
typedef struct NodeObj* Node;

// private NodeObj type
typedef struct NodeObj{
   int data;
   Node next;
   Node previous;
} NodeObj;

// private ListObj type
typedef struct ListObj{
   Node front;
   Node back;
   Node cursor;
   int length;
   int index;
} ListObj;


// Constructors-Destructors ---------------------------------------------------

// newNode()
// Returns reference to new Node object. Initializes next and data fields.
Node newNode(int data){
   Node N = malloc(sizeof(NodeObj));
   assert(N != NULL);
   memset(N,0,sizeof(NodeObj));
   N->data = data;
   N->next = N->previous = NULL;
   return(N);
}

// freeNode()
// Frees heap memory pointed to by *pN, sets *pN to NULL.
void freeNode(Node* pN){
   if(pN != NULL && *pN != NULL){
      free(*pN);
      *pN = NULL;
   }
}

// newList()
// Returns reference to new empty List object.
List newList(){
   List L;
   L = malloc(sizeof(ListObj));
   assert(L != NULL);
   L->front = L->back = L->cursor = NULL;
   L->length = 0;
   L->index = -1;
   return(L);
}

// freeList()
// Frees all heap memory associated with List *pL, and sets *pL to NULL.
void freeList(List* pL){
   if(pL != NULL && *pL != NULL) { 
    //   while(!isEmpty(*pL)) { 
    //      Dequeue(*pL); 
    //   }
      if ((*pL)->length > 0)
         clear(*pL);
      free(*pL);
      *pL = NULL;
   }
}

// Access functions -----------------------------------------------------------

// length()
// Returns the number of elements in L.
int length(List L){
   if(L == NULL){
      printf("List Error: calling length() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   return(L->length);
}

// index()
// Returns index of cursor element if defined, -1 otherwise.
int index(List L){
    if(L == NULL){
      printf("List Error: calling index() on NULL List reference\n");
      exit(EXIT_FAILURE);
    }
    return(L->index);
}

// front()
// Returns front element of L. Pre: length()>0
int front(List L){
    if(L == NULL){
      printf("List Error: calling front() on NULL List reference\n");
      exit(EXIT_FAILURE);
    }
    if((L->length) <= 0){
      printf("List Error: calling front() on an empty List\n");
      exit(EXIT_FAILURE);
    }
    return(L->front->data);
}

// back()
// Returns back element of L. Pre: length()>0
int back(List L){
    if(L == NULL){
      printf("List Error: calling back() on NULL List reference\n");
      exit(EXIT_FAILURE);
    }
    if((L->length) <= 0){
      printf("List Error: calling back() on an empty List\n");
      exit(EXIT_FAILURE);
    }
    return(L->back->data);
}

// get()
// Returns cursor element of L. Pre: length()>0, index()>=0
int get(List L){
    if(L == NULL){
      printf("List Error: calling get() on NULL List reference\n");
      exit(EXIT_FAILURE);
    }
    if((L->length) <= 0){
      printf("List Error: calling get() on an empty List\n");
      exit(EXIT_FAILURE);
    }
    if((L->index) < 0){
      printf("List Error: calling get() cursor element does not defined\n");
      exit(EXIT_FAILURE);
    }
    return(L->cursor->data);
}

// equals()
// Returns true iff Lists A and B are in same state, and returns false otherwise.
bool equals(List A, List B){
    if(A == NULL || B == NULL){
      printf("List Error: calling equals() on NULL List reference\n");
      exit(EXIT_FAILURE);
    }
    bool eq;
    Node N, M;

    eq = (A->length == B->length);
    N = A->front;
    M = B->front;
    while(eq && N!=NULL){
      eq = (N->data == M->data);
      N = N->next;
      M = M->next;
    }
    return eq;
}


// Manipulation procedures ----------------------------------------------------

// clear()
// Resets L to its original empty state
void clear(List L){
    if(L == NULL){
      printf("List Error: calling clear() on NULL List reference\n");
      exit(EXIT_FAILURE);
    }
    while (L->length > 0) {
      deleteFront(L);
    }
    L->length = 0;
    L->index = -1;
}

// set()
// Overwrites the cursor element’s data with x. Pre: length()>0, index()>=0
void set(List L, int x){
    if(L == NULL){
      printf("List Error: calling set() on NULL List reference\n");
      exit(EXIT_FAILURE);
    }
    if((L->length) <= 0){
      printf("List Error: calling set() on an empty List\n");
      exit(EXIT_FAILURE);
    }
    if((L->index) < 0){
      printf("List Error: calling set() cursor element does not defined\n");
      exit(EXIT_FAILURE);
    }
    L->cursor->data = x;
}

// moveFront()
// If L is non-empty, sets cursor under the front element, otherwise does nothing.
void moveFront(List L){
    if(L == NULL){
      printf("List Error: calling moveFront() on NULL List reference\n");
      exit(EXIT_FAILURE);
    }
    // if((L->length) <= 0){
    //   printf("List Error: calling set() on an empty List\n");
    //   exit(EXIT_FAILURE);
    // }
    if (L->length > 0) {
      L->cursor = L->front;
      L->index = 0;
    }
}

// moveBack()
// If L is non-empty, sets cursor under the back element, otherwise does nothing.
void moveBack(List L){
    if(L == NULL){
      printf("List Error: calling moveBack() on NULL List reference\n");
      exit(EXIT_FAILURE);
    }
    if (L->length > 0) {
      L->cursor = L->back;
      L->index = L->length - 1;
    }
}

// movePrev()
// If cursor is defined and not at front, move cursor one step toward the front of L;
// if cursor is defined and at front, cursor becomes undefined;
// if cursor is undefined, do nothing
void movePrev(List L){
    if(L == NULL){
      printf("List Error: calling movePrev() on NULL List reference\n");
      exit(EXIT_FAILURE);
    }
    if(L->cursor != NULL) {
      if(L->cursor != L->front) {
        L->cursor = L->cursor->previous;
      } else {
        L->cursor = NULL;
      }
      L->index--;
    }
}

// moveNext()
// If cursor is defined and not at back, move cursor one step toward the back of L;
// if cursor is defined and at back, cursor becomes undefined;
// if cursor is undefined, do nothing
void moveNext(List L){
    if(L == NULL){
      printf("List Error: calling moveNext() on NULL List reference\n");
      exit(EXIT_FAILURE);
    }
    if(L->cursor != NULL) {
      if(L->cursor != L->back) {
        L->cursor = L->cursor->next;
        L->index++;
      } else {
        L->cursor = NULL;
        L->index = -1;
      }
    }
}

// prepend()
// Insert new element into L. If L is non-empty, insertion takes place before front element.
void prepend(List L, int x){
    if(L == NULL){
      printf("List Error: calling prepend() on NULL List reference\n");
      exit(EXIT_FAILURE);
    }
    Node N = newNode(x);
    if (L->length == 0) {
      L->front = L->back = N;
    } else {
      N->next = L->front;
      L->front->previous = N;
      L->front = N;
    }
    L->length++;
    if (L->index != -1) {
      L->index++;
    }

}

// append()
// Insert new element into L. If L is non-empty, insertion takes place after back element.
void append(List L, int x){
    if(L == NULL){
      printf("List Error: calling append() on NULL List reference\n");
      exit(EXIT_FAILURE);
    }
    Node N = newNode(x);
    if (L->length == 0) {
      L->front = L->back = N;
    } else {
      L->back->next = N;
      N->previous = L->back;
      L->back = N;
    }
    L->length++;
}

// insertBefore()
// Insert new element before cursor. Pre: length()>0, index()>=0
void insertBefore(List L, int x){
    if(L == NULL){
      printf("List Error: calling insertBefore() on NULL List reference\n");
      exit(EXIT_FAILURE);
    }
    if((L->length) <= 0){
      printf("List Error: calling insertBefore() on an empty List\n");
      exit(EXIT_FAILURE);
    }
    if((L->index) < 0){
      printf("List Error: calling insertBefore() cursor element does not defined\n");
      exit(EXIT_FAILURE);
    }
    if(L->cursor == L->front) {
      prepend(L, x);
    } else {
      Node N = newNode(x);
      N->previous = L->cursor->previous;
      L->cursor->previous->next = N;
      N->next = L->cursor;
      L->cursor->previous = N;
      L->length++;
      L->index++;
    }
}

// insertAfter()
// Insert new element after cursor. Pre: length()>0, index()>=0
void insertAfter(List L, int x){
    if(L == NULL){
      printf("List Error: calling insertAfter() on NULL List reference\n");
      exit(EXIT_FAILURE);
    }
    if((L->length) <= 0){
      printf("List Error: calling insertAfter() on an empty List\n");
      exit(EXIT_FAILURE);
    }
    if((L->index) < 0){
      printf("List Error: calling insertAfter() cursor element does not defined\n");
      exit(EXIT_FAILURE);
    }
    if(L->cursor == L->back) {
      append(L, x);
    } else {
      Node N = newNode(x);
      N->next = L->cursor->next;
      L->cursor->next->previous = N;
      N->previous = L->cursor;
      L->cursor->next = N;
      L->length++;
    }
}

// deleteFront()
// Delete the front element. Pre: length()>0
void deleteFront(List L){
    Node N = NULL;
    if(L == NULL){
      printf("List Error: calling deleteFront() on NULL List reference\n");
      exit(EXIT_FAILURE);
    }
    if((L->length) <= 0){
      printf("List Error: calling deleteFront() on an empty List\n");
      exit(EXIT_FAILURE);
    }
    N = L->front;
    if(length(L) > 1) { 
      L->front = L->front->next;
      L->front->previous = NULL;
    }else{ 
      L->front = L->back = NULL; 
    }
    L->length--;
    freeNode(&N);
    // cursor defined
    if ((L->index) != -1) {
      L->index--;
    }
    // first element
    if ((L->index) == -1) {
      L->cursor = NULL;
    }
}

// deleteBack()
// Delete the back element. Pre: length()>0
void deleteBack(List L){
    Node N = NULL;
    if(L == NULL){
      printf("List Error: calling deleteBack() on NULL List reference\n");
      exit(EXIT_FAILURE);
    }
    if((L->length) <= 0){
      printf("List Error: calling deleteBack() on an empty List\n");
      exit(EXIT_FAILURE);
    }
    N = L->back;
    if(length(L) > 1) {
      L->back = L->back->previous;
      L->back->next = NULL;
    }else{ 
      L->front = L->back = NULL; 
    }
    L->length--;
    freeNode(&N);
    // last element
    if ((L->index) == length(L)) {
      L->cursor = NULL;
      L->index = -1;
    }
}

// delete()
// Delete cursor element, making cursor undefined. Pre: length()>0, index()>=0
void delete(List L){
    Node N = NULL;
    if(L == NULL){
      printf("List Error: calling delete() on NULL List reference\n");
      exit(EXIT_FAILURE);
    }
    if((L->length) <= 0){
      printf("List Error: calling delete() on an empty List\n");
      exit(EXIT_FAILURE);
    }
    if((L->index) < 0){
      printf("List Error: calling delete() cursor element does not defined\n");
      exit(EXIT_FAILURE);
    }
    N = L->cursor;
    // first element
    if (L->index == 0) {
      deleteFront(L);
    } else if (L->index == length(L) - 1) { // last element
      deleteBack(L);
    } else {  // otherwise
      L->cursor->next->previous = L->cursor->previous;
      L->cursor->previous->next = L->cursor->next;
      L->cursor = NULL;
      L->index = -1;
      L->length--;
      freeNode(&N);
    }
}

// Other operations -----------------------------------------------------------

// printList()
// Prints to the file pointed to by out, a string representation of L consisting
// of a space separated sequence of integers, with front on left.
void printList(FILE* out, List L){
    Node N = NULL;
    if(L == NULL){
      printf("List Error: calling printList() on NULL List reference\n");
      exit(EXIT_FAILURE);
    }
    for (N = L->front; N != NULL; N = N->next) {
      fprintf(out, "%d ", N->data);
    }
    // printf("\n");
}

// copyList()
// Returns a new List representing the same integer sequence as L.
// The cursor in the new list is undefined, regardless of the state of the cursor in L.
// The state of L is unchanged.
List copyList(List L){
    Node N = NULL;
    if(L == NULL){
      printf("List Error: calling copyList() on NULL List reference\n");
      exit(EXIT_FAILURE);
    }
    List newL = newList();
    for (N = L->front; N != NULL; N = N->next) {
      append(newL, N->data);
    }
    return newL;
}
