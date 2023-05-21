#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

#include "aux_functions.h"

int main(void){
    pthread_t threads[NUM_PHI];
    int ids[NUM_PHI];

    //create one thread for each philosopher
    for(int i = 0; i < NUM_PHI; i++){
        ids[i] = i;
        pthread_create(&threads[i], NULL, philosopher, &ids[i]);        
    }

    for(int i = 0; i < NUM_PHI; i++){
        pthread_join(threads[i], NULL);
    }

    printf("Finished the Dining Filosophers Problemn\n");

    return 0;
}