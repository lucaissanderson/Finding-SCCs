//******************************************
//  List.c
//  Lucais Sanderson - lzsander
//  List ADT implementation
//******************************************

//******************************************
//  Citation:
//    Much of the basis of this program is 
//    based on the Queue and Stack exmaples
//    found at:
//  https://people.ucsc.edu/~ptantalo/cse101/Spring23/Examples/C/
//******************************************

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "List.h"

// structs ------------------------------------------------------------------

// private Node type
typedef struct NodeObj* Node;

// private Node type
typedef struct NodeObj{
    int data;
    Node next;
    Node prev;
} NodeObj;

// private ListObj type
typedef struct ListObj{
    Node front;
    Node back;
    Node cursor;
    int length;
    int cindex;
} ListObj;


// Constructors-Destructors ----------------------------------------------------

// initialize a Node
Node newNode(int data){
//    Node N = malloc(sizeof(NodeObj));
    Node N = malloc(sizeof(struct NodeObj));
    assert(N != NULL);
    N->data = data;
    N->next = NULL;
    N->prev = NULL;
    return(N);
}

// free a Node
void freeNode(Node* pN){
    if(pN != NULL && *pN != NULL){
        free(*pN);
        *pN = NULL;
    }
}

// initialize a List
List newList(void){
    List L;
    L = malloc(sizeof(ListObj));
    assert(L != NULL);
    L->front = L->back = L->cursor = NULL;
    L->length = 0;
    L->cindex = -1;
    return(L);
}

// free list L
void freeList(List* pL){
    if(pL != NULL && *pL != NULL){
        clear(*pL);
        free(*pL);
        *pL = NULL;
    }
}


// Access functions -----------------------

// get length of L
int length(List L){
    return L->length;
}

// get index of cursor on L
int index(List L){
    return L->cindex;
}

// get front entry of L
// Pre: length()>0
int front(List L){
    if(length(L) <= 0){
        fprintf(stderr, "List Error: calling front() on empty List\n");
        exit(EXIT_FAILURE);
    }
    return L->front->data;
}

// get back entry of L
// Pre: length()>0
int back(List L){
    if(length(L) <= 0){
        fprintf(stderr, "List Error: calling back() on empty List\n");
        exit(EXIT_FAILURE);
    }
    return L->back->data;
}

// get entry of cursor element
// Pre: length()>0, index()>=0
int get(List L){
    if(length(L) <= 0){
        fprintf(stderr, "List Error: calling get() on empty List\n");
        exit(EXIT_FAILURE);
    }
    if(index(L) < 0){
        fprintf(stderr, "List Error: calling get(), index out of range\n");
        exit(EXIT_FAILURE);
    }
    return L->cursor->data;
}

// Pre: both lists not empty
// test equallity of two Lists
bool equals(List A, List B){
    if(A == NULL || B == NULL){
        fprintf(stderr, "List Error: calling equals() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    bool eq;
    Node N, M;

    eq = (A->length == B->length);
    N = A->front;
    M = B->front;
    while(eq && N != NULL){
        eq = (N->data == M->data);
        N = N->next;
        M = M->next;
    }
    return eq;
}


// Manipulation functions -------

// remove all Nodes and reset List to clean slate
void clear(List L){
    // iterate delete() for length()
    if(L != NULL){
        while(length(L) > 0){
            deleteFront(L);
        }
        L->front = L->back = L->cursor = NULL;
        L->cindex = -1;
        L->length = 0;
    }
}

// set element for L the cursor is on to x
// Pre: length()>0, index()>=0
void set(List L, int x){
    if(length(L) <= 0 || index(L) < 0){
        fprintf(stderr, "List Error: calling set() on empty List\n");
        exit(EXIT_FAILURE);
    }
    (L->cursor)->data = x;
}

// move cursor to front
void moveFront(List L){
    if(L->length > 0){
        L->cursor = L->front;
        L->cindex = 0;
    }
    return;
}

// move cursor to back
void moveBack(List L){
    if(L->length > 0){
        L->cursor = L->back;
        L->cindex = L->length - 1;
    }
    return;
}

// move cursor one backward
void movePrev(List L){
    if(L->cursor == L->front){
        L->cindex = -1;
        L->cursor = NULL;
    }
    if(L->cursor != NULL){
        L->cursor = (L->cursor)->prev;
        L->cindex -= 1;
    }
}

// move cursor one forward
void moveNext(List L){
    if(L->cursor == L->back){
        L->cindex = -1;
        L->cursor = NULL;
    }
    if(L->cursor != NULL){
        L->cursor = (L->cursor)->next;
        L->cindex += 1;
    }
}

// prepend list L with x
// Pre: L != NULL
void prepend(List L, int x){
    Node n = newNode(x);
    if(L == NULL){
        fprintf(stderr, "List Error: calling prepend() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if(length(L) > 0){
        L->front->prev = n;
        n->next = L->front;
        L->front = n;
    } else {
        L->front = L->back = n;
    }
    L->length += 1;
    L->cindex++;
}

// append list L with x
// Pre: L != NULL
void append(List L, int x){
    Node n = newNode(x);
    if(L == NULL){
        fprintf(stderr, "List Error: calling append() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if(length(L) > 0){
        L->back->next = n;
        n->prev = L->back;
        L->back = n;
    } else {
        L->back = L->front = n;
    }
    L->length += 1;
}

// insert x before cursor
// Pre: length()>0, index()>=0, L != NULL
void insertBefore(List L, int x){
    if(L == NULL){
        fprintf(stderr, "List Error: calling insertBefore() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if(length(L) <= 0){
        fprintf(stderr, "List Error: calling insertBefore() on empty List\n");
        exit(EXIT_FAILURE);
    }
    if(index(L) < 0){
        fprintf(stderr, "List Error: calling insertBefore() with undefined cursor\n");
        exit(EXIT_FAILURE);
    }
    if(index(L)==0){
        prepend(L, x);
        return;
    }
    Node n = newNode(x);
    Node temp_curs = L->cursor;
    movePrev(L);
    L->cursor->next = n;
    n->prev = L->cursor;
    L->cursor = temp_curs;
    L->cursor->prev = n;
    n->next = L->cursor;
    L->length++;
    L->cindex += 2;
}

// insert x after cursor
// Pre: length()>0, index()>=0, L != NULL
void insertAfter(List L, int x){
     if(L == NULL){
        fprintf(stderr, "List Error: calling insertAfter() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if(length(L) <= 0){
        fprintf(stderr, "List Error: calling insertAfter() on empty List\n");
        exit(EXIT_FAILURE);
    }
    if(index(L) < 0){
        fprintf(stderr, "List Error: calling insertAfter() with undefined cursor\n");
        exit(EXIT_FAILURE);
    }
    if(index(L)==length(L)-1){
        append(L, x);
        return;
    }
    Node n = newNode(x);
    Node temp_curs = L->cursor;
    moveNext(L);
    L->cursor->prev = n;
    n->next = L->cursor;
    L->cursor = temp_curs;
    L->cursor->next = n;
    n->prev = L->cursor;
    L->length++;
    L->cindex -= 1;
}

// delete front element from list
// pre: length()>0
void deleteFront(List L){
    if(length(L) <= 0){
        fprintf(stderr, "List Error: calling deleteFront() on an empty List\n");
        exit(EXIT_FAILURE);
    }
    Node temp = L->front;
    L->front = temp->next;
    if(L->front != NULL){
        L->front->prev = NULL;
    }
    freeNode(&temp);
    L->length--;
    L->cindex--;
    if(L->cursor == L->front){
    //    L->cindex = -1;
    }
}

// delete back element from list
// pre: length()>0
void deleteBack(List L){
    if(length(L) <= 0){
        fprintf(stderr, "List Error: calling deleteBack() on an empty List\n");
        exit(EXIT_FAILURE);
    }
    // if deleting last element, reset list 
    // if at cursor at back of list, update index
    if(L->cursor==L->back){
        L->cindex = -1;
    }
    Node temp = L->back;
    L->back = temp->prev;
    if(L->back != NULL){
        L->back->next = NULL;
    }
    freeNode(&temp);
    L->length--;
}

// delete element under cursor
// pre: length()>0 && index>=0
void delete(List L){
    if(length(L) <= 0){
        fprintf(stderr, "List Error: calling delete() on empty List\n");
        exit(EXIT_FAILURE);
    }
    if(index(L) < 0){
        fprintf(stderr, "List Error: calling delete() with undefined cursor\n");
        exit(EXIT_FAILURE);
    }
    if(L->cursor == L->front){
        deleteFront(L);
        return;
    }
    if(L->cursor == L->back){
        deleteBack(L);
        return;
    }
    if(L->back == L->front){
        freeNode(&(L->front));
        freeNode(&(L->back));
        freeNode(&(L->cursor));
        L->front = L->back = L->cursor = NULL;
        L->length = 0;
        L->cindex = -1;
        return;
    }
    L->cursor->prev->next = L->cursor->next;
    L->cursor->next->prev = L->cursor->prev;
    freeNode(&(L->cursor));
    L->length--;
}

// other operations -------

// printList
void printList(FILE* out, List L){
    Node N = NULL;
    for(N = L->front; N != NULL; N = N->next){
        fprintf(out, " %d", N->data);
    }
}

// copyList
List copyList(List L){
    List nL= newList();
    Node N = NULL;
    for(N = L->front; N != NULL; N = N->next){
        append(nL, N->data);
    }
    return nL;
}
