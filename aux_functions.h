#ifndef __AUX_FUNCTIONS_H__
#define __AUX_FUNCTIONS_H__

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>

//number of philosophers
#define NUM_PHI 5

//three status that each philosopher can be
#define THINKING 0
#define HUNGRY 1
#define EATING 2

//responsable to prevent concurrent access
typedef struct {
    int status[NUM_PHI];
    pthread_mutex_t mutex;
    pthread_cond_t cond[NUM_PHI];
} Monitor;

void start(Monitor *monitor);
void test(int id_phi);
void take_fork(Monitor *monitor, int phi_id);
void drop_fork(Monitor *monitor, int id_phi);
void *philosopher(void *arg);

#endif