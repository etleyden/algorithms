#include <stdio.h>
#include <math.h>
#include "ethans_utility.c"

// Strategy: Divide and Conquer

/*
 * Finds **A** peak if it exists, and returns the first peak found. 
 * This one dimensional version utilizes a binary search pattern to
 * find the peak. 
 * T(n) = T(n / 2) + Theta(1)
 */
int one_dimensional_find_peak(int* arr, int low, int high) {
    //only looking at one element, done. 
    if(high - low == 1) return arr[low];

    //pick middle
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

/*
 * Naive solution is greedy ascent (Theta(n^2)), and it is wrong. Correct solution below
 * Finds the peak of a two dimensional array of width m and height n
 * 1. Pick column
 * 2. Find max in column
 * 3. Compare left and right, which ever is larger 
 * T(n, m) = T(n, m/2) + Theta(n)
 */
// int** 2d array to be searched, int n height, int m width, int lm (lower bound for m), int um (upper bound for m)
int two_dimensional_find_peak(int** arr, int n, int m, int lm, int um) {
    int j = lm + (um - lm) / 2; // pick middle col
    // find max in column
    int i = 0;
    int max = 0;
    for(i = 0; i < n; i++) {
        if(arr[i][j] < arr[max][j]) {
            max = i;
        }
    }
    
    //base case: we have one column, so we just find our maximum value 
    if(lm - um == 1) {
        return arr[max][j];
    }
    //compare left, if bigger try left half
    if(arr[max][j - 1] > arr[max][j]) {
        return two_dimensional_find_peak(arr, n, m, lm, j);
    //compare right, if bigger try right half
    } else if(arr[max][j + 1] > arr[max][j]) {
        return two_dimensional_find_peak(arr, n, m, j, um);
    } else {
        // if left half is not bigger, and right is not bigger, and we are at max
        // this must be peak
        return arr[max][j];
    }
    return 0;
}

int main() {
    //1D 
    printf("1D Peak Finding: Divide and Conquer\n");
    int verbose_example[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int verbose_size = 10;
    print_array(verbose_example, verbose_size);
    clock_t *start = start_time();
    printf("solution: %d\n", one_dimensional_find_peak(verbose_example, 0, verbose_size));
    printf("time: %dms\n", end_time(start));

    int orders_of_magnitude = 1; //temporary set to 1 so we can test 2d
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
    

    //2D
    printf("2D Peak Finding\n");
    int **twod_verbose_example = (int**) malloc(sizeof(int) * 16);
    int row_one[]   = {10,  8, 10, 10}; twod_verbose_example[0] = row_one;
    int row_two[]   = {14, 13, 12, 11}; twod_verbose_example[1] = row_two;
    int row_three[] = {15,  9, 11, 21}; twod_verbose_example[2] = row_three;
    int row_four[]  = {16, 17, 19, 20}; twod_verbose_example[3] = row_four;
    int twod_n = 4;
    print2d_array(twod_verbose_example, twod_n, twod_n);
    start = start_time();
    int solution = two_dimensional_find_peak(twod_verbose_example, twod_n, twod_n, 0, twod_n);
    printf("solution: %d\ntime: %dms", solution, end_time(start));

    orders_of_magnitude = 4;
    // to generate a worst case 2d array, each cell is the distance from the center 
}

 
