/********************************************************************************* 
* FindComponents.c
* Implementation of representing a graph with its adjacency list and finding strongly connected components between pairs of vertices in a file by using the Depth First Search (DFS) algorithm
*********************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include "List.h"
#include "Graph.h"

#define MAX_LEN 300

int main(int argc, char* argv[]) {

    FILE *in, *out;
    char line[MAX_LEN];
    int num;
    int left;
    int right;
    int strong = 0;
    int index_scc = 1;
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
    // get num of vertices
    num = atoi(fgets(line, MAX_LEN, in));
    Graph G = newGraph(num);
    // get all edges
    while( fgets(line, MAX_LEN, in) != NULL)  {
        left = atoi(strtok(line, " \n"));
        right = atoi(strtok(NULL, " \n"));
        if (left == 0 && right == 0 ){
            break;
        }
        addArc(G, left, right);
    }
    fprintf(out, "Adjacency list representation of G:\n");
    printGraph(out, G);
    fprintf(out, "\n");
    Graph T = newGraph(num);
    List L = newList();
    List* component = malloc(sizeof(List) * (num + 1));
    for (int i = 1; i <= num; i++) {
        component[i] = newList();
    }
    for (int i = 1; i <= num; i++) {
        append(L, i);
    }
    DFS(G, L);
    // printList(out, L);
    // fprintf(out, "\n");
    T = transpose(G);
    DFS(T, L);
    // printList(out, L);
    // fprintf(out, "\n");
    moveFront(L);
    while (index(L) > -1) {
        if (getParent(T, get(L)) == NIL) {
            // fprintf(out, "%d\n", get(L));
            strong++;
            append(component[index_scc], get(L));
            moveNext(L);
            if (index(L) == -1) {
                index_scc++;
                break;
            }
            while (getParent(T, get(L)) != NIL) {
                append(component[index_scc], get(L));
                moveNext(L);
                // fprintf(out, "%d\n", index(L));
                if (index(L) == -1) {
                    break;
                }
            }
        }
        // fprintf(out, "index: %d\n", index_scc);
        index_scc++;
    }
    fprintf(out, "G contains %d strongly connected components:\n", strong);
    int j = 1;
    while (index_scc > 1) {
        fprintf(out, "Component %d: ", j);
        printList(out, component[index_scc - 1]);
        fprintf(out, "\n");
        index_scc--;
        j++;
    }
    for (int i = 1; i <= num; i++) {
        freeList(&component[i]);
    }
    freeGraph(&G);
    freeGraph(&T);
    freeList(&L);
    free(component);
    fclose(in);
    fclose(out);
    return(0);
}
