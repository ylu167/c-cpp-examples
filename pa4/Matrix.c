/********************************************************************************* 
* Matrix.c
* Implementation file for Matrix ADT
*********************************************************************************/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<assert.h>
#include<stdbool.h>
#include "List.h"
#include "Matrix.h"

// private Entry type
typedef struct EntryObj* Entry;

// private EentryObj type
typedef struct EntryObj{
   double data;
   int column;
} EntryObj;

// private MatrixObj type
typedef struct MatrixObj{
   List* row;   // list
   int nonzero; // number of non-zero elements in M
   int size;    // size of Matrix M
} MatrixObj;

// newEntry()
// Returns reference to new Entry object. Initializes column and data fields.
Entry newEntry(int column, double data){
   Entry E = malloc(sizeof(EntryObj));
   assert(E != NULL);
   E->data = data;
   E->column = column;
   return(E);
}

// freeEntry()
// Frees heap memory pointed to by *pN, sets *pN to NULL.
void freeEntry(Entry* pE){
    if(pE != NULL && *pE != NULL){
      free(*pE);
      *pE = NULL;
    }
}

// newMatrix()
// Returns a reference to a new nXn Matrix object in the zero state.
Matrix newMatrix(int n) {
    Matrix M;
    M = malloc(sizeof(MatrixObj));
    assert(M != NULL);
    M->row = malloc(sizeof(List) * (n+1));
    assert(M->row != NULL);
    for (int i = 1; i <= n; i++) {
        M->row[i] = newList();
    }
    M->size = n;
    M->nonzero = 0;
    return(M);
}

// freeMatrix()
// Frees heap memory associated with *pM, sets *pM to NULL.
void freeMatrix(Matrix* pM) {
    if(pM != NULL && *pM != NULL) { 
    //   while(!isEmpty(*pL)) { 
    //      Dequeue(*pL); 
    //   }
        makeZero(*pM);
        for (int i = 1; i <= (*pM)->size; i++) {
            freeList(&((*pM)->row[i]));
            (*pM)->row[i] = NULL;
        }
        free((*pM)->row);
        free(*pM);
        *pM = NULL;
    }
}

// Access functions
// size()
// Return the size of square Matrix M.
int size(Matrix M) {
    if(M == NULL){
      printf("Matrix Error: calling size() on NULL Matrix reference\n");
      exit(EXIT_FAILURE);
    }
    return(M->size);
}

// NNZ()
// Return the number of non-zero elements in M.
int NNZ(Matrix M) {
    if(M == NULL){
      printf("Matrix Error: calling NNZ() on NULL Matrix reference\n");
      exit(EXIT_FAILURE);
    }
    return(M->nonzero);
}

// equals()
// Return true (1) if matrices A and B are equal, false (0) otherwise.
int equals(Matrix A, Matrix B) {
    if(A == NULL || B == NULL){
      printf("Matrix Error: calling equals() on NULL Matrix reference\n");
      exit(EXIT_FAILURE);
    }
    int eq;
    List N, M;
    Entry X, Y;
    int i = 1;
    eq = (A->size == B->size);
    while(eq && i <= A->size){
        N = A->row[i]; 
        M = B->row[i];
        eq = (length(N) == length(M));
        moveFront(N);
        moveFront(M);
        while(eq && index(N) > -1) {
            X = get(N);
            Y = get(M);
            eq = (X->data == Y->data);
            moveNext(N);
            moveNext(M);
        }
        i++;
    }
    return eq;
}

// Manipulation procedures
// makeZero()
// Re-sets M to the zero Matrix state.
void makeZero(Matrix M) {
    if(M == NULL){
      printf("Matrix Error: calling makeZero() on NULL Matrix reference\n");
      exit(EXIT_FAILURE);
    }
    for (int i = 1; i <= M->size; i++) {
        List L = M->row[i];
        moveFront(L);
        while(index(L) > -1) {
            Entry E = get(L);
            freeEntry(&E);
            moveNext(L);
        }
        clear(M->row[i]);
    }
    M->nonzero = 0;
}

// changeEntry()
// Changes the ith row, jth column of M to the value x.
// Pre: 1<=i<=size(M), 1<=j<=size(M)
void changeEntry(Matrix M, int i, int j, double x) {
    if(M == NULL){
      printf("Matrix Error: calling changeEntry() on NULL Matrix reference\n");
      exit(EXIT_FAILURE);
    }
    if(i > M->size || i < 1)
	{
		printf("Matrix Error: calling changeEntry() on i out of bounds\n");
		exit(EXIT_FAILURE);
	}
	if(j > M->size || j < 1)
	{
		printf("Matrix Error: calling changeEntry() on j out of bounds\n");
		exit(EXIT_FAILURE);
	}
    List L = M->row[i];
    // all zero row
    if (length(L) == 0) {
        // nothing to change
        if (x == 0.0) {
            return;
        // add new data
        } else {
            append(L, newEntry(j, x));
            M->nonzero++;
        }
        return;
    }
    moveFront(L);
    for (int i = 1; i <= length(L); i++) {
        Entry E = get(L);
        // change this element
        if (E->column == j) {
            E->data = x;
            // detele exist element
            if (x == 0) {
                freeEntry(&E);
                delete(L);
                M->nonzero--;
            }
            return;
        // insert new element
        } else if (E->column > j) {
            if (x == 0) {
                return;
            }
            insertBefore(L, newEntry(j, x));
            M->nonzero++;
            return;
        // last one
        } else if (index(L) == length(L) - 1) {
            if (x == 0) {
                return;
            }
            append(L, newEntry(j, x));
            M->nonzero++;
            return;
        }
        moveNext(L);
    }
}

// Matrix Arithmetic operations
// copy()
// Returns a reference to a new Matrix object having the same entries as A.
Matrix copy(Matrix A) {
    if(A == NULL){
      printf("Matrix Error: calling copy() on NULL Matrix reference\n");
      exit(EXIT_FAILURE);
    }
    Matrix newM = newMatrix(A->size);
    for (int i = 1; i <= A->size; i++) {
        List L = A->row[i];
        moveFront(L);
        while (index(L) > -1) {
            Entry E = get(L);
            changeEntry(newM, i, E->column, E->data);
            moveNext(L);
        }
    }
    return newM;
}

// transpose()
// Returns a reference to a new Matrix object representing the transpose
// of A.
Matrix transpose(Matrix A) {
    if(A == NULL){
      printf("Matrix Error: calling transpose() on NULL Matrix reference\n");
      exit(EXIT_FAILURE);
    }
    Matrix newM = newMatrix(A->size);
    for (int i = 1; i <= A->size; i++) {
        List L = A->row[i];
        moveFront(L);
        while (index(L) > -1) {
            Entry E = get(L);
            changeEntry(newM, E->column, i, E->data);
            moveNext(L);
        }
    }
    return newM;
}

// scalarMult()
// Returns a reference to a new Matrix object representing xA.
Matrix scalarMult(double x, Matrix A) {
    if(A == NULL){
      printf("Matrix Error: calling transpose() on NULL Matrix reference\n");
      exit(EXIT_FAILURE);
    }
    Matrix newM = newMatrix(A->size);
    for (int i = 1; i <= A->size; i++) {
        List L = A->row[i];
        moveFront(L);
        while (index(L) > -1) {
            Entry E = get(L);
            changeEntry(newM, i, E->column, E->data * x);
            moveNext(L);
        }
    }
    return newM;
}

// sum()
// Returns a reference to a new Matrix object representing A+B.
// pre: size(A)==size(B)
Matrix sum(Matrix A, Matrix B) {
    if(A == NULL || B == NULL){
      printf("Matrix Error: calling sum() on NULL Matrix reference\n");
      exit(EXIT_FAILURE);
    }
    if(size(A) != size(B)){
      printf("Matrix Error: calling sum() on Matrix with different size\n");
      exit(EXIT_FAILURE);
    }
    if (A == B)
	{
		return scalarMult(2, A);
	}
    Matrix newM = newMatrix(A->size);
    for (int i = 1; i <= A->size; i++) {
        List M = A->row[i];
        List N = B->row[i];
        moveFront(M);
        moveFront(N);
        // printf("M%d ",index(M));
        // printf("N%d ",index(N));
        // printf("\n");
        while (index(M) > -1 && index(N) > -1) {
            // printf("m%d ",index(M));
            // printf("n%d ",index(N));
            Entry E = get(M);
            Entry F = get(N);
            // M has a zero on this column
            if (E->column > F->column) {
                // printf("1 ");
                // data (i,j) = data in N
                changeEntry(newM, i, F->column, F->data);
                moveNext(N);
            // N has a zero on this column
            } else if (E->column < F->column) {
                // printf("2 ");
                // data (i,j) = data in M
                changeEntry(newM, i, E->column, E->data);
                moveNext(M);
            // M N all have a non zero data on this point
            } else {
                // printf("3 ");
                changeEntry(newM, i, E->column, E->data + F->data);
                moveNext(M);
                moveNext(N);
                // printf("m%d ",index(M));
                // printf("n%d ",index(N));
            }
        }
        // M has remaining data
        while (index(M) > -1) {
            Entry E = get(M);
            changeEntry(newM, i, E->column, E->data);
            moveNext(M);
        }
        // N has remaining data
        while (index(N) > -1) {
            Entry F = get(N);
            changeEntry(newM, i, F->column, F->data);
            moveNext(N);
        }
    }
    // printf("%d\n",NNZ(newM));
    // printf("%d\n",NNZ(A));
    return newM;
}

// diff()
// Returns a reference to a new Matrix object representing A-B.
// pre: size(A)==size(B)
Matrix diff(Matrix A, Matrix B) {
    if(A == NULL || B == NULL){
      printf("Matrix Error: calling diff() on NULL Matrix reference\n");
      exit(EXIT_FAILURE);
    }
    if(size(A) != size(B)){
      printf("Matrix Error: calling diff() on Matrix with different size\n");
      exit(EXIT_FAILURE);
    }
    Matrix newM = newMatrix(A->size);
    for (int i = 1; i <= A->size; i++) {
        List M = A->row[i];
        List N = B->row[i];
        moveFront(M);
        moveFront(N);
        while (index(M) > -1 && index(N) > -1) {
            Entry E = get(M);
            Entry F = get(N);
            // M has a zero on this column
            if (E->column > F->column) {
                // data (i,j) = data in N
                changeEntry(newM, i, F->column, F->data * -1);
                moveNext(N);
            // N has a zero on this column
            } else if (E->column < F->column) {
                // data (i,j) = data in M
                changeEntry(newM, i, E->column, E->data);
                moveNext(M);
            // M N all have a non zero data on this point
            } else {
                // printf("3 ");
                changeEntry(newM, i, E->column, E->data - F->data);
                moveNext(M);
                moveNext(N);
            }
        }
        // M has remaining data
        while (index(M) > -1) {
            Entry E = get(M);
            changeEntry(newM, i, E->column, E->data);
            moveNext(M);
        }
        // N has remaining data
        while (index(N) > -1) {
            Entry F = get(N);
            changeEntry(newM, i, F->column, F->data * -1);
            moveNext(N);
        }
    }
    return newM;
}

// helper function for product()
double vectorDot(List P, List Q) {
    double sum = 0.0;
    moveFront(P);
    moveFront(Q);
    while (index(P) > -1 && index(Q) > -1) {
        Entry E = get(P);
        Entry F = get(Q);
        // M has a zero on this column
        if (E->column > F->column) {
            // * 0 = 0
            moveNext(Q);
        // N has a zero on this column
        } else if (E->column < F->column) {
            // * 0 = 0
            moveNext(P);
        // M N all have a non zero data on this point
        } else {
            sum += E->data * F->data;
            moveNext(P);
            moveNext(Q);
        }
    }
    return sum;
}

// product()
// Returns a reference to a new Matrix object representing AB
// pre: size(A)==size(B)
Matrix product(Matrix A, Matrix B) {
    if(A == NULL || B == NULL){
      printf("Matrix Error: calling product() on NULL Matrix reference\n");
      exit(EXIT_FAILURE);
    }
    if(size(A) != size(B)){
      printf("Matrix Error: calling product() on Matrix with different size\n");
      exit(EXIT_FAILURE);
    }
    Matrix newM = newMatrix(A->size);
    Matrix T = transpose(B);
    for (int i = 1; i <= A->size; i++) {
        List M = A->row[i];
        for (int j = 1; j <= A->size; j++) {
            List N = T->row[j];
            changeEntry(newM, i, j, vectorDot(M, N));
        }
    }
    freeMatrix(&T);
    return newM;
}

// printMatrix()
// Prints a string representation of Matrix M to filestream out. Zero rows
// are not printed. Each non-zero row is represented as one line consisting
// of the row number, followed by a colon, a space, then a space separated
// list of pairs "(col, val)" giving the column numbers and non-zero values
// in that row. The double val will be rounded to 1 decimal point.
void printMatrix(FILE* out, Matrix M) {
    if(M == NULL){
      printf("Matrix Error: calling printMatrix() on NULL List reference\n");
      exit(EXIT_FAILURE);
    }
    for (int i = 1; i <= M->size; i++) {
        List L = M->row[i];
        if(length(L) == 0) {
            continue;
        }
        fprintf(out, "%d:", i);
        moveFront(L);
        while (index(L) > -1) {
            Entry E = get(L);
            fprintf(out, " (%d, %.1f)", E->column, E->data);
            moveNext(L);
        }
        fprintf(out, "\n");
    }
}
