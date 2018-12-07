#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "l0.h"

int main(int argc, const char* argv[]) {

   typedef l0_listof(float) float_list;

   float_list listp = NULL;
   
   // Initial list is empty
   assert(l0_size(listp) == 0);
   assert(l0_isempty(listp));

   //add an element - it is there
   l0_add(listp, 1);
   assert(l0_size(listp) == 1);
   assert(!l0_isempty(listp));
   assert(l0_peek(listp) == 1.0);

   //add a second element - the list grows, the head does not change
   l0_add(listp, 2.1f);
   assert(l0_size(listp) == 2);
   assert(!l0_isempty(listp));
   assert(l0_peek(listp) == 1.0);

   //pop the head - the list shrinks, the head changes
   l0_pop(listp);
   assert(l0_size(listp) == 1);
   assert(!l0_isempty(listp));
   assert(l0_peek(listp) == 2.1f);

   //pop the head - the list is empty again
   l0_pop(listp);
   assert(l0_size(listp) == 0);
   assert(l0_isempty(listp));

   //pop an empty list, no change
   l0_pop(listp);
   assert(l0_size(listp) == 0);
   assert(l0_isempty(listp));

   //push onto a list - element is present
   l0_push(listp, 3.3f);
   assert(l0_size(listp) == 1);
   assert(!l0_isempty(listp));
   assert(l0_peek(listp) == 3.3f);

   //push again onto a list - list grows, new element is front
   l0_push(listp, 4.4f);
   assert(l0_size(listp) == 2);
   assert(!l0_isempty(listp));
   assert(l0_peek(listp) == 4.4f);

   //push again onto a list - list grows, new element is front
   l0_push(listp, 5.5f);
   assert(l0_size(listp) == 3);
   assert(!l0_isempty(listp));
   assert(l0_peek(listp) == 5.5);

   //walk the list
   float expected[] = {5.5f, 4.4f, 3.3f};
   int n=0;
   for (float_list i = listp; i!=NULL; i=l0_next(i))
   {
      printf("%f ",*i);
      assert(*i == expected[n++]);
   }
   printf("\n");

   //pop the head - the list shrinks, the head changes
   l0_pop(listp);
   assert(l0_size(listp) == 2);
   assert(!l0_isempty(listp));
   assert(l0_peek(listp) == 4.4f);

   //arbitrary things can be in lists
   typedef struct {
      int n;
      float f;
   } blob;
   #define BLOB(name, n) blob name = {n,n}
   #define BLOBEQ(a,b) (a.n==b.n && a.f == b.f)

   l0_listof(blob) sl;
   assert(l0_size(sl)==0);

   BLOB(one,1);
   BLOB(two,2);
   BLOB(three,3);

   // Initial list is empty
   assert(l0_size(sl) == 0);
   assert(l0_isempty(sl));

   //add an element - it is there
   l0_add(sl, one);
   assert(l0_size(sl) == 1);
   assert(!l0_isempty(sl));
   assert(BLOBEQ(l0_peek(sl), one));

   //push onto a list - list grows, new element is front
   l0_push(sl, two);
   assert(l0_size(sl) == 2);
   assert(!l0_isempty(sl));
   assert(BLOBEQ(l0_peek(sl), two));
          
   //add to end - the list grows, the head does not change
   l0_add(sl, three);
   assert(l0_size(sl) == 3);
   assert(!l0_isempty(sl));
   assert(BLOBEQ(l0_peek(sl), two));

   //pop the head - the list shrinks, the head changes
   l0_pop(sl);
   assert(l0_size(sl) == 2);
   assert(!l0_isempty(sl));
   assert(BLOBEQ(l0_peek(sl), one));

   //pop the head - the list shrinks, the head changes
   l0_pop(sl);
   assert(l0_size(sl) == 1);
   assert(!l0_isempty(sl));
   assert(BLOBEQ(l0_peek(sl), three));
          
   //pop the head - the list is empty again
   l0_pop(sl);
   assert(l0_size(sl) == 0);
   assert(l0_isempty(sl));

   printf(" PASS! \n");
}
