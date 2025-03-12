/********************************************************************************* 
* MatrixTest.c 
* Test cases for Matrix ADT 
*********************************************************************************/
#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include"Matrix.h"
     
int main(){
    int n=3;
    Matrix A = newMatrix(n);
    Matrix B = newMatrix(n);
    Matrix C = newMatrix(n);
    Matrix D1, D2, E1, E2, E3, F1, F2, G1, G2, H1, H2;

    changeEntry(A, 1,1,1); changeEntry(B, 1,1,1);
    changeEntry(A, 1,2,2); changeEntry(B, 1,2,0);
    changeEntry(A, 1,3,3); changeEntry(B, 1,3,1);
    changeEntry(A, 2,1,4); changeEntry(B, 2,1,0);
    changeEntry(A, 2,2,5); changeEntry(B, 2,2,1);
    changeEntry(A, 2,3,6); changeEntry(B, 2,3,0);
    changeEntry(A, 3,1,7); changeEntry(B, 3,1,1);
    changeEntry(A, 3,2,8); changeEntry(B, 3,2,1);
    changeEntry(A, 3,3,9); changeEntry(B, 3,3,1);

    // Test printMatrix and NNZ
    printf("Test printMatrix and NNZ:\n");
    printf("%d\n", NNZ(A));
    printMatrix(stdout, A);
    printf("\n");

    printf("%d\n", NNZ(B));
    printMatrix(stdout, B);
    printf("\n");

    printf("%d\n", NNZ(C));
    printMatrix(stdout, C);
    printf("\n");

    // Test size
    printf("Test size:\n");
    printf("%d\n", size(A));
    printf("%d\n", size(B));
    printf("%d\n", size(C));
    printf("\n");

    // Test copy
    printf("Test copy:\n");
    Matrix C_copy = copy(C);
    printf("%d\n", NNZ(C_copy));
    printMatrix(stdout, C_copy);
    printf("\n");
    Matrix B_copy = copy(B);
    printf("%d\n", NNZ(B_copy));
    printMatrix(stdout, B_copy);
    printf("\n");

    // Test equals
    printf("Test equals:\n");
    printf("%s\n", equals(A, A)?"true":"false" );
	printf("%s\n", equals(A, B)?"true":"false" );
	printf("%s\n", equals(C, C_copy)?"true":"false" );
    printf("%s\n", equals(B, B_copy)?"true":"false" );
    printf("\n");

    // Test makeZero
    printf("Test makeZero:\n");
    changeEntry(C, 1,1,1); 
    changeEntry(C, 1,3,1);
    changeEntry(C, 2,1,2); 
    changeEntry(C, 3,2,3);
    printf("%d\n", NNZ(C));
    printMatrix(stdout, C);
    printf("\n");
    makeZero(C);
    printf("%d\n", NNZ(C));
    printMatrix(stdout, C);
    printf("\n");
    
    // Test transpose
    printf("Test transpose:\n");
    D1 = transpose(B);
    printf("%d\n", NNZ(D1));
    printMatrix(stdout, D1);
    printf("\n");
    D2 = transpose(C);
    printf("%d\n", NNZ(D2));
    printMatrix(stdout, D2);
    printf("\n");

    // Test scalarMult
    printf("Test scalarMult:\n");
    E1 = scalarMult(1.5, A);
    printf("%d\n", NNZ(E1));
    printMatrix(stdout, E1);
    printf("\n");
    E2 = scalarMult(0, A);
    printf("%d\n", NNZ(E2));
    printMatrix(stdout, E2);
    printf("\n");
    E3 = scalarMult(-1, A);
    printf("%d\n", NNZ(E3));
    printMatrix(stdout, E3);
    printf("\n");

    // Test sum
    printf("Test sum:\n");
    F1 = sum(A, B);
    printf("%d\n", NNZ(F1));
    printMatrix(stdout, F1);
    printf("\n");
    F2 = sum(A, A);
    printf("%d\n", NNZ(F2));
    printMatrix(stdout, F2);
    printf("\n");

    // Test diff
    printf("Test diff:\n");
    G1 = diff(A, B);
    printf("%d\n", NNZ(G1));
    printMatrix(stdout, G1);
    printf("\n");
    G2 = diff(A, A);
    printf("%d\n", NNZ(G2));
    printMatrix(stdout, G2);
    printf("\n");

    // Test product
    printf("Test product:\n");
    H1 = product(A, A);
    printf("%d\n", NNZ(H1));
    printMatrix(stdout, H1);
    printf("\n");
    H2 = product(B, B);
    printf("%d\n", NNZ(H2));
    printMatrix(stdout, H2);
    printf("\n");

    freeMatrix(&A);
    freeMatrix(&B);
    freeMatrix(&C);
    freeMatrix(&D1);
    freeMatrix(&D2);
    freeMatrix(&E1);
    freeMatrix(&E2);
    freeMatrix(&E3);
    freeMatrix(&F1);
    freeMatrix(&F2);
    freeMatrix(&G1);
    freeMatrix(&G2);
    freeMatrix(&H1);
    freeMatrix(&H2);

    return EXIT_SUCCESS;
}

/*
Output of this program:
Test printMatrix and NNZ:
9
1: (1, 1.0) (2, 2.0) (3, 3.0)
2: (1, 4.0) (2, 5.0) (3, 6.0)
3: (1, 7.0) (2, 8.0) (3, 9.0)

6
1: (1, 1.0) (3, 1.0)
2: (2, 1.0)
3: (1, 1.0) (2, 1.0) (3, 1.0)

0

Test size:
3
3
3

Test copy:
0

6
1: (1, 1.0) (3, 1.0)
2: (2, 1.0)
3: (1, 1.0) (2, 1.0) (3, 1.0)

Test equals:
true
false
true
true

Test makeZero:
4
1: (1, 1.0) (3, 1.0)
2: (1, 2.0)
3: (2, 3.0)

0

Test transpose:
6
1: (1, 1.0) (3, 1.0)
2: (2, 1.0) (3, 1.0)
3: (1, 1.0) (3, 1.0)

0

Test scalarMult:
9
1: (1, 1.5) (2, 3.0) (3, 4.5)
2: (1, 6.0) (2, 7.5) (3, 9.0)
3: (1, 10.5) (2, 12.0) (3, 13.5)

0

9
1: (1, -1.0) (2, -2.0) (3, -3.0)
2: (1, -4.0) (2, -5.0) (3, -6.0)
3: (1, -7.0) (2, -8.0) (3, -9.0)

Test sum:
9
1: (1, 2.0) (2, 2.0) (3, 4.0)
2: (1, 4.0) (2, 6.0) (3, 6.0)
3: (1, 8.0) (2, 9.0) (3, 10.0)

9
1: (1, 2.0) (2, 4.0) (3, 6.0)
2: (1, 8.0) (2, 10.0) (3, 12.0)
3: (1, 14.0) (2, 16.0) (3, 18.0)

Test diff:
8
1: (2, 2.0) (3, 2.0)
2: (1, 4.0) (2, 4.0) (3, 6.0)
3: (1, 6.0) (2, 7.0) (3, 8.0)

0

Test product:
9
1: (1, 30.0) (2, 36.0) (3, 42.0)
2: (1, 66.0) (2, 81.0) (3, 96.0)
3: (1, 102.0) (2, 126.0) (3, 150.0)

7
1: (1, 2.0) (2, 1.0) (3, 2.0)
2: (2, 1.0)
3: (1, 2.0) (2, 2.0) (3, 2.0)

*/
