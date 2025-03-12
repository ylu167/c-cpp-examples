/********************************************************************************* 
* Graph.c
* Implementation file for Graph ADT
*********************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include "List.h"
#include "Graph.h"

int time = 0;
typedef struct GraphObj{
    List* neighbor;  // array of lists contains neighbors
    int* color;  // array of ints contains color
    int* parent; // array of ints contains parents
    int* discover; // discover time
    int* finish; // finish time
    int order;   // num of vertices
    int size;    // num of edges
} GraphObj;

Graph newGraph(int n) {
    Graph G;
    G = malloc(sizeof(GraphObj));
    assert(G != NULL);
    G->order = n;
    G->size = 0;
    G->neighbor = malloc(sizeof(List) * (n + 1));
    G->color = malloc(sizeof(int) * (n + 1));
    G->parent = malloc(sizeof(int) * (n + 1));
    G->discover = malloc(sizeof(int) * (n + 1));
    G->finish = malloc(sizeof(int) * (n + 1));
    for (int i = 1; i <= n; i++) {
        G->neighbor[i] = newList();
        G->color[i] = 0;
        G->parent[i] = NIL;
        G->discover[i] = UNDEF;
        G->finish[i] = UNDEF;
    }
    return(G);
}

void freeGraph(Graph* pG) {
    if(pG != NULL && *pG != NULL) {
        // delete all edges
        for (int i = 1; i <= getOrder(*pG); i++) {
            List free_neighbor = (*pG)->neighbor[i];
            freeList(&free_neighbor);
        }
        free((*pG)->neighbor);
        free((*pG)->color);
        free((*pG)->parent);
        free((*pG)->discover);
        free((*pG)->finish);
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

int getDiscover(Graph G, int u) {
    if(G == NULL){
        printf("Graph Error: calling getDiscover() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    // vertex u not in the Graph's vertices
    if(u < 1 || u > getOrder(G)) {
        printf("Graph Error: calling getDiscover() on out of bound vertex\n");
        exit(EXIT_FAILURE);
    }
    return G->discover[u];
}

int getFinish(Graph G, int u) {
    if(G == NULL){
        printf("Graph Error: calling getFinish() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    // vertex u not in the Graph's vertices
    if(u < 1 || u > getOrder(G)) {
        printf("Graph Error: calling getFinish() on out of bound vertex\n");
        exit(EXIT_FAILURE);
    }
    return G->finish[u];
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
        if (v == get(G->neighbor[u])) {
            G->size--;
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

void Visit(Graph G, int x, List L)
{
    // follow the pseudocode
	++time;
	G->discover[x] = time;
	G->color[x] = 1;
    moveFront(G->neighbor[x]);
    for (int i = 1; i <= length(G->neighbor[x]); i++) {
        int y = get(G->neighbor[x]);
        if (G->color[y] == 0) {
            G->parent[y] = x;
            Visit(G, y, L);
        }
        moveNext(G->neighbor[x]);
    }
    G->color[x] = 2;
	++time;
	G->finish[x] = time;
    prepend(L, x);
}
    
void DFS(Graph G, List S) {
    if(G == NULL){
        printf("Graph Error: calling DFS() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    if (length(S)!=getOrder(G)) {
        printf("Graph Error: calling DFS on List length doesn't equal to Graph order\n");
		exit(EXIT_FAILURE);
    }
    // follow the pseudocode
    List newL = newList();
    for (int i = 1; i <= getOrder(G); i++) {
        G->color[i] = 0;    // white
        G->parent[i] = NIL;
    }
	time = 0;
	moveFront(S);
    for (int i = 1; i <= length(S); i++) {
        int x = get(S);
        if (G->color[x] == 0) {
            Visit(G, x, newL);
        }
        moveNext(S);
    }
    moveFront(S);
    moveFront(newL);
    for (int i = 1; i <= length(S); i++) {
        if (i <= length(newL)) {
            int x = get(newL);
            set(S, x);
            moveNext(S);
            moveNext(newL);
        } else {
            delete(S);
        }
    }
    freeList(&newL);
}

Graph transpose(Graph G) {
    if( G==NULL ){
      fprintf(stderr,"Graph Error: calling transpose() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
   }
   Graph newG = newGraph(G->order);
   for( int i = 1; i <= G->order; i++){
        moveFront(G->neighbor[i]);
        for (int j = 1; j <= length(G->neighbor[i]); j++) {
            addArc(newG, get(G->neighbor[i]), i);
            moveNext(G->neighbor[i]);
        }
   }
   return newG;
}

Graph copyGraph(Graph G) {
    if(G == NULL){
      printf("Graph Error: calling copyGraph() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
    }
    Graph newG = newGraph(G->order);
    for (int i = 1; i <= G->order; i++) {
        newG->neighbor[i] = copyList(G->neighbor[i]);
        newG->color[i] = G->color[i];
        newG->parent[i] = G->parent[i];
        newG->discover[i] = G->discover[i];
        newG->finish[i] = G->finish[i];
    }
    newG->order = G->order;
    newG->size = G->size;
    return newG;
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
