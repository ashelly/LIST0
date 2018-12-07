# LIST0 
## A Generic Linked-List Header-only Library for C 

_By AShelly  (https://github.com/ashelly)_

Notable Features

- True generics in C.
 - `listof(AnyType)` works.
 - Still typesafe.
- Non-invasive. No need to embed `next` members in data structures
- Support for usage as stack or queue.
- Under 50 lines of code (excluding comments).
- The source file doubles as a markdown file

### Usage:

Include this header.    
 
    #include "l0.h"

Typedef'ing specific types can make declarations cleaner;  

    typedef l0_listof(int) intlist;

You can create a list of any type.  

    l0_listof(struct tm) timelist = NULL;

Declare a list.

    intlist my_list = NULL;  //must initialize;

Check that it is empty.  

    bool isEmpty = l0_isempty(my_list) ; //true

Add items to the back (like a queue).

    l0_add(my_list,1);

_Adding allocates a node and copies the value into it_.

    l0_add(my_list,2);

 Add items to the front (like a stack).

    l0_push(my_list, 0);

Iterate, Dereference the head to get the value.  
   
    for (intlist i = my_list;i!=NULL;i=l0_next(i)) { 
      printf("%d,", *i);  
    }  // prints "0,1,2"

 Remove nodes from front only. The node is freed. No value is returned.
 
    l0_pop(my_list);

 Peek at the front value (equiv to *my_list)

    int first = l0_peek(my_list);

 Get number of nodes

    size_t n_items = l0_size(my_list); 
  
 _Some compilers do not support this usage, use this alternate_.

     size_t n_items;
     l0_size(my_lilst,&nitems); 


