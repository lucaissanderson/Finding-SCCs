//----------------------------------------------------------------------------
// List.h
// Header file for List ADT
//----------------------------------------------------------------------------

#ifndef LIST_H_INCLUDE_
#define LIST_H_INCLUDE_
#endif
#include <stdbool.h>

// Exported types
typedef int ListElement;
typedef struct ListObj* List;


// Constructors-Destructors

// newList()
List newList();

// freeList();
void freeList(List* pL);


// Access fuinctions
int length(List L);
int index(List L);
int front(List L);
int back(List L);
int get(List L);
bool equals(List A, List B);


// Manipulation functions
void clear(List L);
void set(List L, int x);
void moveFront(List L);
void moveBack(List L);
void movePrev(List L);
void moveNext(List L);
void prepend(List L, int x);
void append(List L, int x);
void insertBefore(List L, int x);
void insertAfter(List L, int x);
void deleteFront(List L);
void deleteBack(List L);
void delete(List L);


// Other operations
void printList(FILE* out, List L);
List copyList(List L);
