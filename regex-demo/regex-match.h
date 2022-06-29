#include <regex.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/queue.h>

#ifndef _BASIC_MATCHINFO_T_
#define _BASIC_MATCHINFO_T_

typedef struct basic_matchinfo_t
{
    int start;
    int finish;
    char* matched_text;
    TAILQ_ENTRY(basic_matchinfo_t) entries;
} basic_matchinfo_t;

typedef struct basic_matchlist_t basic_matchlist_t;

TAILQ_HEAD(basic_matchlist_t, basic_matchinfo_t);


extern void basic_matchlist_add(basic_matchlist_t* head_ptr, int start, int finish, char* matched_text);
extern void basic_matchlist_print(basic_matchlist_t* head_ptr);
extern void basic_matchlist_delete(basic_matchlist_t* head_ptr);
extern void basic_matchlist_init(basic_matchlist_t* head_ptr);

extern int regex_compile (regex_t * r, const char * regex_text);
extern int regex_match (regex_t * r, const char * to_match, basic_matchlist_t *match_list);

#endif
