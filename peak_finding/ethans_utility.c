#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void print_array(int* array, int size) {
    int i = 0; 
    for(; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

clock_t* start_time() {
    clock_t *begin = (clock_t*) malloc(sizeof(clock_t));
    *begin = clock();
    return begin;
}

// returns the end time in ms
int end_time(clock_t* start_time) {
    double result = (double)(clock() - *start_time);
    free(start_time);
    return result;
}
