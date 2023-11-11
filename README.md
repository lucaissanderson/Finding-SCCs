# Finding Strongly Connected Components

## Files:

### Graph.c

Source code for graph ADT implementing constructor, destructor, access, and manipulation functions.

### Graph.h

Header interface for Graph.c.

### GraphTest.c

Rigourous testing for Graph ADT developed in Graph.c.

### FindComponents.c

Sample client code for using Graph ADT. Finds the strongly connected components of a graph  
given in a file.  
  
I ended up declaring the time variable (denoted `t`) for `visit()` in the scope of `DFS()` and passing the  
address to `visit()` as a parameter. 

### List.c

Source code for List ADT.

### List.h

Header interface for List ADT.


### Makefile

File for building executables and cleaning directory.

### README

*This* file. Contains simple descriptions of files included for this assignment.
