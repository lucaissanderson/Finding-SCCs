#ifndef GRAPH_H_INCLUDE_
#define GRAPH_H_INCLUDE_
#endif

#include "List.h"

/* define NIL and UNDEF */
#define NIL 0
#define UNDEF -1

/* enumerate colors */
enum colors { white, grey, black };

/* define GraphObj and Graph*/
typedef struct GraphObj {
    List* neighbors;
    int* color;
    int* parent;
    int* distance;// unneeded for DFS
    int* discover;
    int* finish;
    int order;
    int edges;
    int source;
} GraphObj;

typedef GraphObj* Graph;

/* Constructors/Destructors */
Graph newGraph(int n);
void freeGraph(Graph* pG);

/* Access functions */
int getOrder(Graph G);
int getSize(Graph G);
int getParent(Graph G, int u);
int getDist(Graph G, int u);
int getDiscover(Graph G, int u);
int getFinish(Graph G, int u);
void getPath(List L, Graph G, int u);
int getSource(Graph G);// unneeded for DFS

/* Manipulation procedures */
void makeNull(Graph G);
void addEdge(Graph G, int u, int v);
void addArc(Graph G, int u, int v);
void DFS(Graph G, List S);

/* other operations */
Graph transpose(Graph G);
Graph copyGraph(Graph G);
void printGraph(FILE* out, Graph G);


