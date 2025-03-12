/********************************************************************************* 
* Sparse.c
* Implementation of representing non-zero entries of matrix and performing matrix operations by using Matrix ADT
*********************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include "List.h"
#include "Matrix.h"

#define MAX_LEN 300

int main(int argc, char* argv[]) {

    FILE *in, *out;
    int n;
    int nonzeroA;
    int nonzeroB;
    Matrix A;
    Matrix B;
    int i, j;
    double x;
    Matrix scalar;
	Matrix add;
	Matrix add_same;
	Matrix minus;
	Matrix minus_same;
	Matrix trans;
	Matrix multiply;
	Matrix multiply_same;
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
    // get n
    fscanf(in, "%d %d %d", &n, &nonzeroA, &nonzeroB);
    // fprintf(out,"%d %d %d",n,nonzeroA,nonzeroB);
    A = newMatrix(n);
    B = newMatrix(n);
    // get all edges
    for(int a = 0; a < nonzeroA; a++)  {
        fscanf(in, "%d %d %lf\n", &i, &j, &x);
        changeEntry(A, i, j, x);
    }
    for(int a = 0; a < nonzeroB; a++)  {
        fscanf(in, "%d %d %lf\n", &i, &j, &x);
        changeEntry(B, i, j, x);
    }

	fprintf(out, "A has %d non-zero entries:\n", nonzeroA);
	printMatrix(out, A);
	fprintf(out, "\n");

	fprintf(out, "B has %d non-zero entries:\n", nonzeroB);
	printMatrix(out, B);
	fprintf(out, "\n");

	fprintf(out, "(1.5)*A =\n");
	scalar = scalarMult(1.5, A);
	printMatrix(out, scalar);
	fprintf(out, "\n");

	fprintf(out, "A+B =\n");
	add = sum(A, B);
	printMatrix(out, add);
	fprintf(out, "\n");

	fprintf(out, "A+A =\n");
	add_same = sum(A, A);
	printMatrix(out, add_same);
	fprintf(out, "\n");

	fprintf(out, "B-A =\n");
	minus = diff(B, A);
	printMatrix(out, minus);
	fprintf(out, "\n");

	fprintf(out, "A-A =\n");
	minus_same = diff(A, A);
	printMatrix(out, minus_same);
	fprintf(out, "\n");

	fprintf(out, "Transpose(A) =\n");
	trans = transpose(A);
	printMatrix(out, trans);
	fprintf(out, "\n");

	fprintf(out, "A*B =\n");
	multiply = product(A, B);
	printMatrix(out, multiply);
	fprintf(out, "\n");

	fprintf(out, "B*B =\n");
	multiply_same = product(B, B);
	printMatrix(out, multiply_same);
	fprintf(out, "\n");

	freeMatrix(&A);
	freeMatrix(&B);
	freeMatrix(&scalar);
	freeMatrix(&add);
	freeMatrix(&add_same);
	freeMatrix(&minus);
	freeMatrix(&minus_same);
	freeMatrix(&trans);
	freeMatrix(&multiply);
	freeMatrix(&multiply_same);

	fclose(in);
	fclose(out);

	return(0);
}
