#include <stdio.h>
#include <stdlib.h>

#include "charlist.h"

void charlist_add_char(struct charlist_t* head_ptr, char c)
{
    struct charentry_t* my_entry = malloc(sizeof(struct charentry_t));
    my_entry->c = c;
    TAILQ_INSERT_TAIL(head_ptr, my_entry, entries);
}

void charlist_add_string(struct charlist_t* head_ptr, char* text)
{
    for (char* next_char=text; *next_char != '\0'; next_char++)
        charlist_add_char(head_ptr, *next_char);
}

void charlist_print(struct charlist_t* head_ptr)
{
    struct charentry_t* np;
    TAILQ_FOREACH(np, head_ptr, entries)
    {
        printf("%c\n", np->c);
    }
}

char* charlist_tostring(struct charlist_t* head_ptr)
{
    /* will cache size later */
    int size = charlist_size_slow(head_ptr);
    char* text = (char*)malloc(size * sizeof(char));
    struct charentry_t* np;
    int i=0;
    TAILQ_FOREACH(np, head_ptr, entries)
    {
        text[i++] = np->c;
    }
    text[i] = '\0';
    return text;
}

int charlist_size_slow(struct charlist_t* head_ptr)
{
    struct charentry_t* np;
    int size = 0;
    TAILQ_FOREACH(np, head_ptr, entries)
    {
        size++;
    }
    return size;
}

void charlist_delete(struct charlist_t* head_ptr)
{
    struct charentry_t* n1, *n2;
    n1 = TAILQ_FIRST(head_ptr);
    while (n1 != NULL)
    {
        n2 = TAILQ_NEXT(n1, entries);
        free(n1);
        n1 = n2;
    }
}

void charlist_init(struct charlist_t* head_ptr)
{
    struct charlist_t head = TAILQ_HEAD_INITIALIZER(head);
    *head_ptr = head;
    /* create a tail queue */
    TAILQ_INIT(head_ptr);
}

