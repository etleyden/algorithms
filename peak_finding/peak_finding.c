#include <stdio.h>
#include <math.h>
#include "peak_finding.h"
#include "ethans_utility.c"

int main() {
    int verbose_example[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int verbose_size = 10;
    print_array(verbose_example, verbose_size);
    clock_t *start = start_time();
    printf("solution: %d\n", one_dimensional_find_peak(verbose_example, 0, verbose_size));
    printf("time: %dms\n", end_time(start));

    int orders_of_magnitude = 10;
    srand(time(NULL));
    int i;
    for(i = 1; i < orders_of_magnitude; i++) {
        int len = (int) pow(10, i);
        int *random_example = (int*)malloc(sizeof(int) * len);
        int j;
        for(j = 0; j < len; j++) {
            *(random_example + j) = j;
        }
        start = start_time();
        one_dimensional_find_peak(random_example, 0, len);
        printf("%dms to solve size %d\n", end_time(start), len);
    }
}

/*
 * Finds **A** peak if it exists, and returns the first peak found. 
 * This one dimensional version utilizes a binary search pattern to
 * find the peak. 
 * T(n) = T(n / 2) + Theta(1)
 */
int one_dimensional_find_peak(int* arr, int low, int high) {
    if(high - low == 1) return arr[low];
    int idx = low + ((high - low) / 2);
    
    //If the left side is greater, middle cannot be peak, but left one could be
    if(arr[idx] < arr[idx - 1]) {
        return one_dimensional_find_peak(arr, low, idx);
    //If right side is greater, likewise
    } else if(arr[idx] < arr[idx + 1]) {
        return one_dimensional_find_peak(arr, idx, high);
    //Both left and right are smaller (or equal to), this must be a peak. 
    } else {
        return arr[idx];
    }
}
 
