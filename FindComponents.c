/***************************
*  pa3 : FindComponents.c
*  Lucais Sanderson
*  lzsander
***************************/

#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

int main(int argc, char** argv){

    FILE* in;
    FILE* out;
    int counter = 0, size, scc = 0, v1, v2; // intermittent vertices 

    // check number of args
    if(argc != 3){
        fprintf(stderr, "Usage: %s <input file> <output file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    in = fopen(argv[1], "r");
    out = fopen(argv[2], "w");

    // check file errors
    if(in == NULL) {
        fprintf(stderr, "Unable to open file %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    if(out == NULL) {
        fprintf(stderr, "Unable to open file %s\n", argv[2]);
        exit(EXIT_FAILURE);
    }

    // get first line for number of vertices
    if(fscanf(in, "%d\n", &size) != 1){
        fprintf(stderr, "Error reading graph size (first line not formatted correctly)\n");
        exit(EXIT_FAILURE);
    }

    // graph G and transpose(G) = Gt
    Graph G = newGraph(size);
    Graph Gt;
    // stack, fill with order(G) entries {1, 2, ..., size}
    List S = newList();
    // list for printing sets of components
    List L = newList();
    for(int i = 1; i <= size; i++) append(S, i);

    // add vertex entries
    while(fscanf(in, "%d %d\n", &v1, &v2)!=EOF){
        if(!(v1 && v2)) break;
        addArc(G, v1, v2);
    }

    // print graph
    fprintf(out, "Adjacency list representation of G:\n");
    printGraph(out, G);
    fprintf(out, "\n");

    // execute DFS and SCC algorithm
    DFS(G, S);
    Gt = transpose(G);
    DFS(Gt, S);

    // count strongly connnected components of G
    for(int i = 1; i <= size; i++){
        if(getParent(Gt, i)==NIL) scc++;
    }

    // print results
    fprintf(out, "G contains %d strongly connected components:", scc);
    moveBack(S);
    while(index(S)>-1){
        prepend(L, get(S));
        if(getParent(Gt, get(S))==NIL){
            counter++;
            fprintf(out, "\nComponent %d: ", counter);
            printList(out, L);
            clear(L);
        }
        movePrev(S);
    }
    fprintf(out, "\n");


    freeGraph(&G);
    freeGraph(&Gt);
    freeList(&S);

    fclose(in);
    fclose(out);

    return 0;
}
