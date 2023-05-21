#include "aux_functions.h"

Monitor monitor;

//all philosophers start at thinking
void start(Monitor *monitor){
    pthread_mutex_init(&monitor->mutex, NULL);
    for(int i = 0; i < NUM_PHI; i++){
        monitor->status[i] = THINKING;
        pthread_cond_init(&monitor->cond[i], NULL);
    }
}

//does the necessary tests to know if that id_phi can start eating
void test(int id_phi){
    if(monitor.status[id_phi] == HUNGRY &&
       monitor.status[(id_phi + NUM_PHI - 1)%NUM_PHI] != EATING &&
       monitor.status[(id_phi + 1)%NUM_PHI] != EATING){

        monitor.status[id_phi] = EATING;
        pthread_cond_signal(&monitor.cond[id_phi]);
    }
}

//make the id_phi take the fork if it is possible
void take_fork(Monitor *monitor, int id_phi){
    pthread_mutex_lock(&monitor->mutex);
    monitor->status[id_phi] = HUNGRY;
    test(id_phi);
    while(monitor->status[id_phi] != EATING){
        pthread_cond_wait(&monitor->cond[id_phi], &monitor->mutex);
    }
    pthread_mutex_unlock(&monitor->mutex);
}

//when finished eating, the id_phi drop his forks
void drop_fork(Monitor *monitor, int id_phi){
    pthread_mutex_lock(&monitor->mutex);
    monitor->status[id_phi] = THINKING;
    test((id_phi + NUM_PHI - 1) % NUM_PHI);
    test((id_phi + 1)% NUM_PHI);
    pthread_mutex_unlock(&monitor->mutex);
}

void destroy_monitor(){
    pthread_mutex_destroy(&monitor.mutex);
    for(int i = 0; i < NUM_PHI; i++){
        pthread_cond_destroy(&monitor.cond[i]);
    }
}

//This function does 100 iterations of the problem
void *philosopher(void *arg){
    int id = *((int *) arg);
    int left_fork = id;
    int right_fork = (id + 1) % NUM_PHI;

    int i = 0;
    while(i < 100){
        printf("\n\n");
        printf("%d", i);
        printf("The %dth is thinking\n", (id+1));
        sleep(5);

        printf("The %dth is hungry\n", (id+1));
        take_fork(&monitor, id);

        printf("The %dth is eating\n", (id+1));
        sleep(7);

        printf("The %dth is not eating anymore\n", (id+1));
        drop_fork(&monitor, id);

        i++;
    }
    destroy_monitor();
}