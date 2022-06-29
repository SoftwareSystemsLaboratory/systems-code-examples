//
// Created by gkt on 10/16/20.
//

#ifndef DINERS_H
#define DINERS_H

#define MAX_DINERS 5
#define MAX_THINK_TIME 7
#define MAX_EAT_TIME 7
#define MAIN_THREAD_SLEEP_TIME 51

typedef struct
{
    char id;
    pthread_mutex_t lock;
} fork_t;

typedef struct
{
    char id;
    char state;
    fork_t *left;
    fork_t *right;
    pthread_t thread;
} diner_t;

extern void fork_init(fork_t *fork, int value);

extern void fork_pickup(fork_t *fork);

extern void fork_putdown(fork_t *fork);

extern void fork_free_resources(fork_t *fork);

extern void diner_init(diner_t *diner, int id, fork_t *left, fork_t *right);

extern void diner_think(diner_t *diner);

extern void diner_eat(diner_t *diner);

extern void diner_start(diner_t *diner);

extern void diner_await(diner_t *diner);

extern void *diner_run(void *tsd);

enum dining_policy_t
{
    NO_FORK_REORDERING, FORK_REORDERING
};

extern enum dining_policy_t get_dining_policy();

#endif //DINERS_DININGPHILOSOPHERS_H
