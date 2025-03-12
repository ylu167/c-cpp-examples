/********************************************************************************* 
* ListTest.c 
* Test cases for Graph ADT 
*********************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include "List.h"
#include "Graph.h"

int main(int argc, char* argv[]){
    int n=35;
    List  L = newList();
    Graph G = NULL;

    // Build graph G 
    // Test newGraph
    G = newGraph(n);
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
    printGraph(stdout, G);

    // Test getOrder
    printf("Order: %d\n", getOrder(G));
    // Test getSize
    printf("Size: %d\n", getSize(G));
    // Test BFS
    BFS(G, 7);
    // Test getSource
    printf("Source: %d\n", getSource(G));
    // Test BFS
    BFS(G, 9);
    // Test getSource
    printf("Source: %d\n", getSource(G));
    // Test getParent
    printf("Parent: %d\n", getParent(G, 1));
    printf("Parent: %d\n", getParent(G, 2));
    BFS(G, 3);
    // Test getDist
    printf("Distance: %d\n", getDist(G, 8));
    BFS(G, 1);
    // Test getPath
    getPath(L, G, 4);
    printList(stdout, L);
    printf("\n");
    
    // Test makeNull
    makeNull(G);
    printGraph(stdout, G);

    // Free objects 
    freeList(&L);
    freeGraph(&G);

    return(0);
}