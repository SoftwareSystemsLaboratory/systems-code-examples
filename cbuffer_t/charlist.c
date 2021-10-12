#include <stdio.h>
#include <stdlib.h>

#include "charlist.h"

void charlist_add(struct charlist_t* head_ptr, char* c) {
   struct charentry_t* my_entry = malloc(sizeof(struct charentry_t));
   my_entry->c = c;
   TAILQ_INSERT_TAIL(head_ptr, my_entry, entries);
}

void charlist_print(struct charlist_t* head_ptr) {
   struct charentry_t* np;
   TAILQ_FOREACH(np, head_ptr, entries) {
      printf("%c\n", np->c;
   }
}

void charlist_delete(struct charlist_t* head_ptr) {
   struct charentry_t* n1, *n2;
   n1 = TAILQ_FIRST(head_ptr);      
   while (n1 != NULL) {
      n2 = TAILQ_NEXT(n1, entries);
      free(n1);
      n1 = n2;
   }
}

void charlist_init(struct charlist_t* head_ptr) {
   struct charlist_t head = TAILQ_HEAD_INITIALIZER(head);
   *head_ptr = head;
   /* create a tail queue */
   TAILQ_INIT(head_ptr);
}

