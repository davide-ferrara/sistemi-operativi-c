#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int counter = 0;

void *routine(void *args){
    int count_up_to = *((int *) args);
    for(int i = 0; i < count_up_to / 2; i++){
        counter ++;
    }
}

int main(int argc, char **argv){

    // ./race_condition 1000000 != ./race_condition 100
    
    if(argc < 2) {
        printf("Usage: ./race_condition <integer_value>\n");
        return -1;
    }

    int count_up_to = atoi(argv[1]);
    pthread_t T1_ID, T2_ID;
    
    if(pthread_create(&T1_ID, NULL, &routine, &count_up_to) != 0) return 1;

    if(pthread_create(&T2_ID, NULL, &routine, &count_up_to) != 0) return 2;

    if(pthread_join(T1_ID, NULL) != 0) return 3;

    if(pthread_join(T2_ID, NULL) != 0) return 4;

    printf("Counter value: %d\n", counter);

    return 0;
}