/***************************
*  pa2 : Graph.c
*  Lucais Sanderson
*  lzsander
***************************/

#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

// prototype private visit() function
void visit(Graph G, List S, int x, int* t);

// prototype push(),pop()
void push(List L, int x);
int pop(List L);

/* Constructors/Destructors */
// allocate and create memory for graph
Graph newGraph(int n){
    Graph g = malloc(sizeof(GraphObj));
    g->color = calloc(n+1, sizeof(int));
    g->parent = calloc(n+1, sizeof(int));
    g->distance = calloc(n+1, sizeof(int));
    g->discover = calloc(n+1, sizeof(int));
    g->finish = calloc(n+1, sizeof(int));
    g->neighbors = calloc(n+1, sizeof(List*));
    for(int i = 1; i <= n; i++){
        g->color[i] = white;
        g->parent[i] = NIL;
        g->neighbors[i] = newList();
        g->discover[i] = UNDEF;
        g->finish[i] = UNDEF;
    }
    g->order = n;
    g->edges = 0;
    g->source = NIL;
    return g;
}

// free all associated memory with G
void freeGraph(Graph* pG){
    for(int i = 0; i <= (*pG)->order; i++){
        freeList(&((*pG)->neighbors[i]));
    }
    free((*pG)->color);
    free((*pG)->parent);
    free((*pG)->distance);
    free((*pG)->neighbors);
    free((*pG)->discover);
    free((*pG)->finish);
    free(*pG);
    *pG = NULL;
}

/* Access functions */
// return number of vertices (order)
int getOrder(Graph G){
    return G->order;
}

// return number of edges of G
int getSize(Graph G){
    return G->edges;
}

// returns source vertex of G
int getSource(Graph G){
    return G->source;
}

// obtain parent of u
// 1 ≤ 𝑢 ≤ getOrder(𝐺)
int getParent(Graph G, int u){
    if(u < 1 || u > getOrder(G)){
        fprintf(stderr, "Graph Error: calling getParent(), u out of range\n");
        exit(EXIT_FAILURE);
    }
    return G->parent[u];
}

// finds distance from source to u
// 1 ≤ 𝑢 ≤ getOrder(𝐺)
int getDist(Graph G, int u){
    if(u < 1 || u > getOrder(G)){
        fprintf(stderr, "Graph Error: calling getDist(), u out of range\n");
        exit(EXIT_FAILURE);
    }
    return G->distance[u];
}

// returns discover time of u in G
// pre: 1<=u<=n=getOrder(G)
int getDiscover(Graph G, int u){
    if(u > getOrder(G) || u < 1){
        fprintf(stderr, "Graph Error: calling getDiscover(), invalid range for u.\n");
        exit(EXIT_FAILURE);
    }
    return G->discover[u];
}

// returns finish time of u in G
// pre: 1<=u<=n=getOrder(G)
int getFinish(Graph G, int u){
    if(u > getOrder(G) || u < 1){
        fprintf(stderr, "Graph Error: calling getFinish(), invalid range for u.\n");
        exit(EXIT_FAILURE);
    }
    return G->finish[u];
}

// find a shortest path from source to u of graph G
// Pre: getSource()!=NIL and 1 ≤ 𝑢 ≤ getOrder(𝐺)
void getPath(List L, Graph G, int u){
    if(u < 1 || u > getOrder(G)){
        fprintf(stderr, "Graph Error: calling getPath(), u out of range\n");
        exit(EXIT_FAILURE);
    }
    if(getSource(G)==NIL){
        fprintf(stderr, "Graph Error: calling getPath(), getSource() is NIL\n");
        exit(EXIT_FAILURE);
    }
    // check if at source vertex
    if(getParent(G, u)==NIL){
        if(u==getSource(G)){
            append(L, u);
        } else {
            append(L, NIL);
        }
        return;
    } else {
        getPath(L, G, getParent(G, u));
        append(L, u);
        return;
    }
}

/* Manipulation procedures */
// clear G
void makeNull(Graph G){
    for(int i = 1; i <= G->order; i++){
        clear(G->neighbors[i]);
    }
    G->edges = 0;
}

// add undirected edge between vertex u and v
void addEdge(Graph G, int u, int v){
    // use temp name for u adjacency list for conciseness
    List temp = G->neighbors[u];

    // check if u's list empty
    if(length(temp) > 0){
        moveFront(temp);
        // add v to u's list
        // ensure list is in increasing order
        while(get(temp) < v && index(temp) < length(temp) - 1){
            // check if v in u's neighbors already
            if(get(temp)==v){
                return;
            }
            moveNext(temp);
        }
        if(get(temp) < v){
            insertAfter(G->neighbors[u], v);
        } else {
            insertBefore(G->neighbors[u], v);
        }
    } else {
        append(temp, v);
    }

    // add v to u's list
    temp = G->neighbors[v];

    if(length(temp) > 0){
        moveFront(temp);
        // add u to v's list
        // ensure list is in increasing order
        while(get(temp) < u && index(temp) < length(temp) - 1){
            // check if u in v's neighbors already
            if(get(temp)==v){
                return;
            }
            moveNext(temp);
        }
        if(get(temp) < u){
            insertAfter(G->neighbors[v], u);
        } else {
            insertBefore(G->neighbors[v], u);
        }
    } else {
        append(temp, u);
    }

    G->edges++;
}

// add directed edge from u to v
void addArc(Graph G, int u, int v){
     // use temp name for u adjacency list for conciseness
    List temp = G->neighbors[u];

    // check if u's list empty
    if(length(temp) > 0){
        moveFront(temp);
        // add v to u's list
        // ensure list is in increasing order
        while(get(temp) < v && index(temp) < length(temp) - 1){
            // check if v already in u's neighbors
            if(get(temp)==v){
                return;
            }
            moveNext(temp);
        }
        if(get(temp) < v){
            insertAfter(G->neighbors[u], v);
        } else {
            insertBefore(G->neighbors[u], v);
        }
    } else {
        append(temp, v);
    }
    G->edges++;
}

// execute BFS algorithm
// S both input and output
// pre: length(S)==n and S some permuatation of {1,2,...,n} for n = getOrder(G)
void DFS(Graph G, List S){
    if(length(S)!=getOrder(G)){
        fprintf(stderr, "Graph Error: calling DFS with inconsistent list and graph size.\n");
        exit(EXIT_FAILURE);
    }
    // initialize vertex attributes
    for(int x = 1; x <= getOrder(G); x++){
        G->color[x] = white;
        G->parent[x] = NIL;
    }
    int t = 0;
    // copy stack and clear S for finish times
    List S_copy = copyList(S);
    clear(S);
    // main loop, iterate through S
    while(length(S_copy)>0){
        int x = pop(S_copy);
        if(G->color[x]==white){
            visit(G, S, x, &t);
        }
    }
    freeList(&S_copy);
}

// private helper for recursion in DFS
void visit(Graph G, List S, int x, int* t){
    G->discover[x] = (++(*t));
    G->color[x] = grey;
    int y;
    moveFront(G->neighbors[x]);

    for(int i = 0;
        i < length(G->neighbors[x]);
        moveNext(G->neighbors[x]), i++){

        y = get(G->neighbors[x]);
        if(G->color[y]==white){
            G->parent[y] = x;
            visit(G, S, y, t);
        }
    }

    G->color[x] = black;
    G->finish[x] = (++(*t));
    push(S, x);

}

// pop helper function
int pop(List L){
    moveFront(L);
    int item = get(L);
    deleteFront(L);
    return item;
}

// push helper function
void push(List L, int x){
    prepend(L, x);
}

/* other operations */
// print G
void printGraph(FILE* out, Graph G){
    for(int i = 1; i <= getOrder(G); i++){
        moveFront(G->neighbors[i]);
        fprintf(out, "%d:", i);
        for(int j = 0; j < length(G->neighbors[i]); j++){
            fprintf(out, " %d", get(G->neighbors[i]));
            moveNext(G->neighbors[i]);
        }
        fprintf(out, "\n");
    }
}

// return new graph which is transpose of G
Graph transpose(Graph G){
    Graph new_graph = newGraph(G->order);
    // iterate through each vertex in G
    for(int i = 1; i <= G->order; i++){
        // check that current neighborhood isn't emtpy
        if(length(G->neighbors[i])<=0){
            continue;
        }
        // iterate through neighbors of vertex,
        // adding given vertex to given neighbor's neighbor list
        int j;
        for(j = 0, moveFront(G->neighbors[i]); 
            j < length(G->neighbors[i]);
            j++, moveNext(G->neighbors[i])){

            // reverse edge direction from i to i's neighbor
            addArc(new_graph, get(G->neighbors[i]), i);

        }
    }

    return new_graph;
}

// copy G and return new graph
Graph copyGraph(Graph G){
    Graph new_graph = newGraph(G->order);
    // iterate through each vertex in G
    for(int i = 1; i <= G->order; i++){
        // check that current neighborhood isn't emtpy
        if(length(G->neighbors[i])<=0){
            continue;
        }
        // iterate through neighbors of vertex,
        // adding given vertex to given neighbor's neighbor list
        int j;
        for(j = 0, moveFront(G->neighbors[i]); 
            j < length(G->neighbors[i]);
            j++, moveNext(G->neighbors[i])){

            // reverse edge direction from i to i's neighbor
            addArc(new_graph, i, get(G->neighbors[i]));

        }
    }

    return new_graph;

}


