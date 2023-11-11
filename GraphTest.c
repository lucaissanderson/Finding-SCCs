/***************************
*  pa2 : GraphTest.c
*  Lucais Sanderson
*  lzsander
***************************/

#include <assert.h>
#include <stdio.h>
#include "Graph.h"

int main(void){
    // test constructors/destructors
    Graph g = newGraph(5);
    assert(g!=NULL);
    assert(g->source==NIL);
    assert(g->order==5);
    assert(g->edges==0);
    freeGraph(&g);
    assert(g==NULL);

    // test access functions
    g = newGraph(6);
    Graph h = newGraph(5);
    assert(getOrder(g)==6);
    assert(getOrder(h)==5);
    assert(getSize(g)==0);
    assert(getSize(h)==0);
    assert(getSource(g)==NIL);
    assert(getSource(h)==NIL);


    // test manipulation functions
    addEdge(g, 1, 3);
    addEdge(g, 1, 2);
    addEdge(g, 3, 4);
    addEdge(g, 2, 4);
    addEdge(g, 2, 5);
    addEdge(g, 2, 6);
    addEdge(g, 4, 5);
    addEdge(g, 5, 6);
    assert(getSize(g)==8);
    assert(getOrder(g)==6);

    freeGraph(&g);
    freeGraph(&h);

    // test DFS
    g = newGraph(8);
    addArc(g, 1, 2);
    addArc(g, 2, 3);
    addArc(g, 2, 5);
    addArc(g, 2, 5);
    addArc(g, 3, 4);
    addArc(g, 3, 7);
    addArc(g, 4, 3);
    addArc(g, 4, 8);
    addArc(g, 5, 1);
    addArc(g, 5, 6);
    addArc(g, 6, 7);
    addArc(g, 7, 6);
    addArc(g, 7, 8);
    addArc(g, 8, 8);

    List l = newList();
    for(int i = 1; i <= getOrder(g); i++){
        append(l, i);
    }
    printList(stdout, l);
    printf("\n");
    printGraph(stdout, g);
    printf("\n");

    DFS(g, l);

    printList(stdout, l);
    printf("\n");

/* expected out:
 */

    // traspose
    Graph gt = transpose(g);
    printGraph(stdout, gt);

    clear(l);
    makeNull(g);
    makeNull(gt);

    // test SCC
    addArc(g, 1, 2);
    addArc(g, 2, 3);
    addArc(g, 2, 5);
    addArc(g, 2, 6);
    addArc(g, 3, 4);
    addArc(g, 3, 7);
    addArc(g, 4, 3);
    addArc(g, 4, 8);
    addArc(g, 5, 1);
    addArc(g, 5, 6);
    addArc(g, 6, 7);
    addArc(g, 7, 6);
    addArc(g, 7, 8);
    addArc(g, 8, 8);

    for(int i = 1; i <= getOrder(g); i++){
        append(l, i);
    }

    printf("\n");
    printGraph(stdout, g);

    // first DFS
    DFS(g, l);
    // get transpose
    gt = transpose(g);
    // second DFS on Gt
    DFS(gt, l);
    printList(stdout, l);
    printf("\n");
    // obtain SCC from l
    moveFront(l);
    while(index(l)>-1){

        if(index(l)==0){
            printf("{");
        }

        if(getParent(gt, get(l))==NIL && !(index(l)==0)){
            printf("} {");
        }

        printf(" %d ", get(l));
        moveNext(l);
    }
    printf("}\n");

    freeGraph(&g);
    freeGraph(&gt);
    freeList(&l);

    // tests from examples page
    int i, n=8;
   List S = newList();
   Graph G = newGraph(n);
   Graph T=NULL, C=NULL;

   for(i=1; i<=n; i++) append(S, i);

   addArc(G, 1,2);
   addArc(G, 1,5);
   addArc(G, 2,5);
   addArc(G, 2,6);
   addArc(G, 3,2);
   addArc(G, 3,4);
   addArc(G, 3,6);
   addArc(G, 3,7);
   addArc(G, 3,8);
   addArc(G, 6,5);
   addArc(G, 6,7);
   addArc(G, 8,4);
   addArc(G, 8,7);
   printGraph(stdout, G);

   DFS(G, S);
   fprintf(stdout, "\n");
   fprintf(stdout, "x:  d  f  p\n");
   for(i=1; i<=n; i++){
      fprintf(stdout, "%d: %2d %2d %2d\n", i, getDiscover(G, i), getFinish(G, i), getParent(G, i));
   }
   fprintf(stdout, "\n");
   printList(stdout, S);
   fprintf(stdout, "\n");

   T = transpose(G);
   C = copyGraph(G);
   fprintf(stdout, "\n");
   printGraph(stdout, C);
   fprintf(stdout, "\n");
   printGraph(stdout, T);
   fprintf(stdout, "\n");

   DFS(T, S);
   fprintf(stdout, "\n");
   fprintf(stdout, "x:  d  f  p\n");
   for(i=1; i<=n; i++){
      fprintf(stdout, "%d: %2d %2d %2d\n", i, getDiscover(T, i), getFinish(T, i), getParent(T, i));
   }
   fprintf(stdout, "\n");
   printList(stdout, S);
   fprintf(stdout, "\n");

   freeList(&S);
   freeGraph(&G);
   freeGraph(&T);
   freeGraph(&C);

    return 0;
}


