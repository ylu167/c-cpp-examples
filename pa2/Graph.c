/********************************************************************************* 
* Graph.c
* Implementation file for Graph ADT
*********************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include "List.h"
#include "Graph.h"

typedef struct GraphObj{
    List* neighbor;  // array of lists contains neighbors
    int* color;  // array of ints contains color
    int* parent; // array of ints contains parents
    int* distance;   // array of ints contains distance
    int order;   // num of vertices
    int size;    // num of edges
    int source;  // most recently used for BFS
} GraphObj;

Graph newGraph(int n) {
    Graph G;
    G = malloc(sizeof(GraphObj));
    assert(G != NULL);
    G->order = n;
    G->size = 0;
    G->source = NIL;
    G->neighbor = malloc(sizeof(List) * (n + 1));
    G->color = malloc(sizeof(int) * (n + 1));
    G->parent = malloc(sizeof(int) * (n + 1));
    G->distance = malloc(sizeof(int) * (n + 1));
    for (int i = 1; i <= n; i++) {
        G->neighbor[i] = newList();
        G->color[i] = 0;
        G->parent[i] = NIL;
        G->distance[i] = INF;
    }
    return(G);
}

void freeGraph(Graph* pG) {
    if(pG != NULL && *pG != NULL) {
        // delete all edges
        makeNull(*pG);
        for (int i = 1; i <= getOrder(*pG); i++) {
            List free_neighbor = (*pG)->neighbor[i];
            freeList(&free_neighbor);
        }
        free((*pG)->neighbor);
        free((*pG)->color);
        free((*pG)->parent);
        free((*pG)->distance);
        free(*pG);
        *pG = NULL;
    }
}

int getOrder(Graph G) {
    if(G == NULL){
        printf("Graph Error: calling getOrder() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    return G->order;
}

int getSize(Graph G){
    if(G == NULL){
        printf("Graph Error: calling getSize() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    return G->size;
}

int getSource(Graph G){
    if(G == NULL){
        printf("Graph Error: calling getSource() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    return G->source;
}

int getParent(Graph G, int u){
    if(G == NULL){
        printf("Graph Error: calling getParent() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    // vertex u not in the Graph's vertices
    if(u < 1 || u > getOrder(G)) {
        printf("Graph Error: calling getParent() on out of bound vertex\n");
        exit(EXIT_FAILURE);
    }
    return G->parent[u];
}

int getDist(Graph G, int u){
    if(G == NULL){
        printf("Graph Error: calling getDist() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    // vertex u not in the Graph's vertices
    if(u < 1 || u > getOrder(G)) {
        printf("Graph Error: calling getDist() on out of bound vertex\n");
        exit(EXIT_FAILURE);
    }
    return G->distance[u];
}

void getPath(List L, Graph G, int u){
    if(G == NULL){
        printf("Graph Error: calling getPath() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    // vertex u not in the Graph's vertices
    if(u < 1 || u > getOrder(G)) {
        printf("Graph Error: calling getPath() on out of bound vertex\n");
        exit(EXIT_FAILURE);
    }
    if(getSource(G) == NIL) {
        printf("Graph Error: calling getPath() on source vertex not defined\n");
        exit(EXIT_FAILURE);
    }
    // first node
    if(getSource(G) == u) {
        append(L, u);
    } else if (getParent(G, u) == NIL) {
            append(L, NIL);    // no such path exists
    } else {
        // while(getSource(G) != u) {
        //     if (getParent(G, u) == NIL) {
        //         append(L, NIL);    // no such path exists
        //         break;
        //     }
        //     append(L, u);
        //     u = getParent(G, u);
        // }
        // append(L, u);
        getPath(L, G, getParent(G, u));
        append(L, u);
    }
}

void makeNull(Graph G) {
    if(G == NULL){
        printf("Graph Error: calling makeNull() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    // clear the list of neighbors
    for (int i = 1; i <= getOrder(G); i++) {
        clear(G->neighbor[i]);
        G->color[i] = 0;    // white
        G->parent[i] = NIL;
        G->distance[i] = INF;
    }
    G->size = 0;
}

void addEdge(Graph G, int u, int v) {
    if(G == NULL){
        printf("Graph Error: calling addEdge() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    // vertex u not in the Graph's vertices
    if(u < 1 || u > getOrder(G)) {
        printf("Graph Error: calling addEdge() on out of bound vertex\n");
        exit(EXIT_FAILURE);
    }
    // vertex v not in the Graph's vertices
    if(v < 1 || v > getOrder(G)) {
        printf("Graph Error: calling addEdge() on out of bound vertex\n");
        exit(EXIT_FAILURE);
    }
    addArc(G, u, v);
    addArc(G, v, u);
    // same edge adds twice
    G->size--;
}

void addArc(Graph G, int u, int v) {
    if(G == NULL){
        printf("Graph Error: calling addArc() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    // vertex u not in the Graph's vertices
    if(u < 1 || u > getOrder(G)) {
        printf("Graph Error: calling addArc() on out of bound vertex\n");
        exit(EXIT_FAILURE);
    }
    // vertex v not in the Graph's vertices
    if(v < 1 || v > getOrder(G)) {
        printf("Graph Error: calling addArc() on out of bound vertex\n");
        exit(EXIT_FAILURE);
    }
    moveFront(G->neighbor[u]);
    for (int i = 0; i <= length(G->neighbor[u]); i++) {
        if (i == length(G->neighbor[u])) {
            append(G->neighbor[u], v);
            break;
        }
        if (v < get(G->neighbor[u])) {
            insertBefore(G->neighbor[u], v);
            break;
        }
        moveNext(G->neighbor[u]);
    }
    G->size++;
}

void BFS(Graph G, int s) {
    if(G == NULL){
      printf("Graph Error: calling BFS() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
    }
     if(s < 1 || s > getOrder(G)) {
        printf("Graph Error: calling BFS() on out of bound vertex\n");
        exit(EXIT_FAILURE);
    }
    // follow the pseudocode
    // initialize all vertices
    for (int i = 1; i <= getOrder(G); i++) {
        G->color[i] = 0;    // white
        G->parent[i] = NIL;
        G->distance[i] = INF;
    }
    // set source vertex
    G->color[s] = 1;    // gray
    G->parent[s] =  NIL;
    G->distance[s] = 0;
    G->source = s;
    // construct a new empty list
    List L = newList();
    append(L, s);
    while(length(L) != 0) {
        int x = front(L);
        deleteFront(L);
        moveFront(G->neighbor[x]);
        for (int i = 1; i <= length(G->neighbor[x]); i++) {
            int y = get(G->neighbor[x]);
            if (G->color[y] == 0) {
                G->color[y] = 1;    // gray
                G->distance[y] = G->distance[x] + 1;
                G->parent[y] = x;
                append(L, y);
            }
            moveNext(G->neighbor[x]);
        }
        G->color[x] = 2;    // black
    }
    freeList(&L);
}

void printGraph(FILE* out, Graph G) {
    // List L = NULL;
    if(G == NULL){
      printf("Graph Error: calling printGraph() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
    }
    for (int i = 1; i <= getOrder(G); i++) {
        fprintf(out, "%d: ", i);
        // L = G->neighbor[i];
        printList(out, G->neighbor[i]);
        fprintf(out, "\n");
    }
}