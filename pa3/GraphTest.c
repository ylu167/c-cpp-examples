/********************************************************************************* 
* ListTest.c 
* Test cases for Graph ADT 
*********************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

int main(int argc, char *argv[]) {
    int n=35;
    List  L = newList();
    Graph G = NULL;

    // Build graph G 
    // Test newGraph
    G = newGraph(n);
    for(int i=1; i<=n; i++) append(L, i);
    for(int i=1; i<n; i++){
        if( i%7!=0 ) addEdge(G, i, i+1);
        if( i<=28  ) addEdge(G, i, i+7);
    }
    // Test addEdge
    addEdge(G, 9, 31);
    addEdge(G, 17, 13);
    // Test addArc
    addArc(G, 14, 33);

    // Print adjacency list representation of G
    // Test printGraph
    printf("Graph G: \n");
    printGraph(stdout, G);

    // Test getOrder
    printf("Order: %d\n", getOrder(G));
    // Test getSize
    printf("Size: %d\n", getSize(G));

    addArc(G, 14, 33);
    printf("Size: %d\n", getSize(G));
    
    // Test DFS
    DFS(G, L);
    fprintf(stdout, "\n");
    fprintf(stdout, "x:  d  f  p\n");
    for(int i=1; i<=n; i++){
        fprintf(stdout, "%d: %2d %2d %2d\n", i, getDiscover(G, i), getFinish(G, i), getParent(G, i));
    }
    fprintf(stdout, "\n");
    printList(stdout, L);
    fprintf(stdout, "\n");

    // Test copyGraph
    Graph C = copyGraph(G);
    fprintf(stdout, "\n");
    printf("Graph C: \n");
    printGraph(stdout, C);
    fprintf(stdout, "\n");
    // Test getOrder
    printf("Order for G: %d; Order for C: %d\n", getOrder(G), getOrder(C));
    // Test getSize
    printf("Size for G: %d; Size for C: %d\n", getSize(G), getSize(C));

    // Test transpose
    Graph T = transpose(G);
    fprintf(stdout, "\n");
    printf("Graph T: \n");
    printGraph(stdout, T);
    fprintf(stdout, "\n");
    DFS(T, L);
    fprintf(stdout, "x:  d  f  p\n");
    for(int i=1; i<=n; i++){
        fprintf(stdout, "%d: %2d %2d %2d\n", i, getDiscover(T, i), getFinish(T, i), getParent(T, i));
    }
    fprintf(stdout, "\n");
    printList(stdout, L);
    fprintf(stdout, "\n");
    
    // Test getParent
    printf("Parent: %d\n", getParent(G, 1));
    printf("Parent: %d\n", getParent(G, 2));

    // Free objects 
    freeList(&L);
    freeGraph(&G);
    freeGraph(&C);
    freeGraph(&T);

    return(0);
}
