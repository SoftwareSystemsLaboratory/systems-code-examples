//
// Created by gkt on 10/16/20.
//

#include <string.h>
#include <stdlib.h>
#include <pthread.h>

#include "diners.h"
#include "millisleep.h"

void fork_init(fork_t *fork, int value)
{
    fork->id = '0' + value;
    pthread_mutex_init(&fork->lock, NULL);
}

void fork_pickup(fork_t *fork)
{
    pthread_mutex_lock(&fork->lock);
}

void fork_putdown(fork_t *fork)
{
    pthread_mutex_unlock(&fork->lock);
}

void fork_free_resources(fork_t *fork)
{
    pthread_mutex_destroy(&fork->lock);
}

void diner_init(diner_t *diner, int id, fork_t *left, fork_t *right)
{
    diner->id = '0' + id;
    diner->state = 't';
    diner->left = left;
    diner->right = right;
}

void diner_start(diner_t *diner)
{
    pthread_attr_t attr;

    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    pthread_create(&diner->thread, &attr, diner_run, (void *)diner);
    pthread_attr_destroy(&attr);
}

void diner_await(diner_t *diner)
{
    void *result;
    pthread_join(diner->thread, &result);
}

void diner_think(diner_t *diner)
{
    diner->state = 't';
    millisecond_sleep(rand() % MAX_THINK_TIME);
}

void diner_eat(diner_t *diner)
{
    diner->state = 'e';
    millisecond_sleep(rand() % MAX_EAT_TIME);
}

void *diner_run(void *tsd)    /* tsd should be the diner object */
{
    diner_t *diner = (diner_t *) tsd;

    for (int i = 0; i < 1000; i++)
    {

        diner_think(diner);
        diner->state = diner->left->id;
        millisecond_sleep(1);
        fork_pickup(diner->left);
        diner->state = diner->right->id;
        millisecond_sleep(1);
        fork_pickup(diner->right);
        diner_eat(diner);
        fork_putdown(diner->left);
        fork_putdown(diner->right);
    }
    diner->state = 'd';
    pthread_exit(diner);
}

enum dining_policy_t get_dining_policy()
{
    char *dining_policy = getenv("DINING_POLICY");
    if (dining_policy == NULL)
        return NO_FORK_REORDERING;

    if (strcmp(dining_policy, "avoid_deadlock") == 0)
        return FORK_REORDERING;

    return NO_FORK_REORDERING;
}
