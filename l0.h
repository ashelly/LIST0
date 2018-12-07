/*~~~   
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


~~~*/
#ifndef L0__H_
#define L0__H_

#include <stdlib.h>  //for calloc/free

/* PRIVATE helpers, start l0__ (double underscore). Here be dragons. */
#define l0__nexta(hd)  (void **)((hd)+1)   //address of next ptr
#define l0__nextv(hd) (*l0__nexta((hd)))   //value of next ptr
#define l0__create(hd, val) (((hd)=calloc(1,sizeof(*(hd))+sizeof((hd))))?*(hd)=(val):(val))
#define l0__gototail(hd) do {} while ((l0_next((hd)))&&((hd)=l0__nextv((hd))))

/* Public Interface */
#define l0_next(head) ((head) ? l0__nextv(head) : NULL)
#define l0_peek(head) (*(head))

#define l0_add(head, value) do {                  \
      if (!(head)) { l0__create((head), value); } \
      else { void *save__0l = (head);             \
         l0__gototail(head);                      \
         void **next__0l = l0__nexta(head);       \
         l0__create((head), value);               \
         *next__0l = (head);                      \
         (head) = save__0l;                       \
      } } while (0)

#define l0_push(head, value) do {               \
      void *rest__0l = (head);                  \
      l0__create((head), value);                \
      l0__nextv(head) = rest__0l;               \
   } while (0)

#define l0_pop(head) do {                       \
      void *dead__0l = (head);                  \
      (head) = l0_next(head);                   \
      free(dead__0l);                           \
   } while (0)

#define l0_isempty(head) ((head)==NULL)
#define l0_listof(type) type *

#if defined(___GNUC__) || defined(__clang__)
//return val version.  //needs "statement expression" support
#define l0_size(head) ({int len__0l=0; void* head__0l=(head);   \
         for (; (head); (head)=l0__nextv(head) ) { ++len__0l; } \
         (head)=head__0l; len__0l;})
#else
//getter version, pass &int;
#define l0_size(head, sz_out) do { void* head__0l=(head);                \
      for (*sz_out=0; (head); (head)=l0__nextv(head) ) { (*sz_out)+=1; } \
      (head)=head__0l;                                                   \
   } while (0)
#endif

#endif
