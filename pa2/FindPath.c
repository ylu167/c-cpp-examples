/********************************************************************************* 
* FindPath.c
* Implementation of representing a graph and finding shortest paths between pairs of vertices in a file by using Graph ADT
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
        addEdge(G, left, right);
    }
    printGraph(out, G);
    // get vertices to find path
    while(fgets(line, MAX_LEN, in) != NULL){
        List L = newList();
        fprintf(out, "\n");
        left = atoi(strtok(line, " \n"));
        right = atoi(strtok(NULL, " \n"));
        if (left == 0 && right == 0 ){
            break;
        }
        BFS(G, left);
        int distance = getDist(G, right);
        if( distance != INF ){
            fprintf(out, "The distance from %d to %d is %d\n", left, right, distance); 
            fprintf(out, "A shortest %d-%d path is: ", left, right);
            getPath(L, G, right);
            printList(out, L);
        }
        else{
            fprintf(out, "The distance from %d to %d is infinity\n", left, right);
            fprintf(out, "No %d-%d path exists", left, right);
        }
        fprintf(out, "\n");
        freeList(&L);
    }
    freeGraph(&G);
    fclose(in);
    fclose(out);
    return(0);
}