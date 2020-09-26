#include <stdio.h>
#include <stdlib.h>

#include <sys/queue.h>

int main(int argc, char* argv[]) {

   TAILQ_HEAD(wordlist_t, wordentry_t) head = TAILQ_HEAD_INITIALIZER(head);
   struct wordentry_t {
      char* text;
      TAILQ_ENTRY(wordentry_t) entries;
   };
   struct wordentry_t* my_entry;

   /* create a tail queue */
   TAILQ_INIT(&head);

   /* add each argument (after 0) to queue; just keep pointer */
   for (int i=1; i < argc; i++) {
     my_entry = malloc(sizeof(struct wordentry_t));
     my_entry->text = argv[i];
     TAILQ_INSERT_TAIL(&head, my_entry, entries);
   }

   /* print it out using the iterator */
   struct wordentry_t* np;
   TAILQ_FOREACH(np, &head, entries) {
      printf("%s\n", np->text);
   }

   /* clean up the list */
   struct wordentry_t* n1, *n2;
   n1 = TAILQ_FIRST(&head);      
   while (n1 != NULL) {
      n2 = TAILQ_NEXT(n1, entries);
      free(n1);
      n1 = n2;
   }
}
