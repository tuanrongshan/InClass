/* include all the headers you need */
#include <stdlib.h>
#include <limits.h>
#include <memory.h>

/* Please note that for every questions asking what does the codes do, please explain the reasons of doing so rather than what the code actually does. */

int isSorted(int *idx, int *value, int len) {
    while (--len >= 1 ) {
        if (value[idx[len]] < value[idx[len-1]]) return 0;
    }
    return 1;
}

void bozo_sort(int *idx, int *value, int len) {     
    while(!isSorted(idx, value, len)) {
        int l = rand() % len;
        int r = rand() % len;
        int t = idx[l];
        idx[l] = idx[r];
        idx[r] = t;
    }
}

#define N_DIGIT(a,n) (((a)/(n))%10)                 /* TODO 1: what does this macro do? */
void radix_sort(int *idx, int *value, int len) {    /* TODO 2: what do the parameters mean and what result will be produced after executing this function? */
    int* bucket;
    bucket = malloc(len*sizeof(*bucket));
    int currDigit = 1;

    int max = INT_MIN;
    for(int i = 0; i < len; i++) {                  /* TODO 3: why do you need this for loop? */
        if(value[idx[i]] > max) {
            max = value[idx[i]];
        }
    }

    while(max / currDigit > 0) {                    /* TODO 4: when will the while loop stop? */
        int counter[10] = {0};
        for(int i = 0; i < len; i++) {              /* TODO 5: what does this for loop do? */
            counter[N_DIGIT(value[idx[i]], currDigit)]++;
        }
        for(int i = 1; i < 10; i++) {               /* TODO 6: what does this for loop do? */
            counter[i] += counter[i-1];
        }
        for(int i = len-1; i >= 0; i--) {           /* TODO 7: what does this for loop do? */
            bucket[--counter[N_DIGIT(value[idx[i]], currDigit)]] = idx[i];
        }
        memcpy(idx, bucket, len*sizeof(*idx)); 
        currDigit *= 10;                            /* TODO 8: what does this line do? */
    }

    free(bucket);
}

void cocktail_sort(int *idx, int *value, int len) {
    int l = 0, r = len-1;
    do {
        for(int i = l; i < r; i++) {                /* TODO 9: why does i starts from l but not 0? */
            if(value[idx[i]] > value[idx[i+1]]) {
                /* TODO 10: please describe what this line does. */
                /* TODO 11: show the step-by-step procedures of: "x = x ^ y ^ (y = x)" , where x=10, y=20 initially. */
                idx[i] = idx[i] ^ idx[i+1] ^ (idx[i+1] = idx[i]);
            }
        }
        r--;
        for(int i = r; i > l; i--) {                /* TODO 12: why does i starts from r but not len-1? */
            if(value[idx[i]] < value[idx[i-1]]) {
                idx[i] = idx[i] ^ idx[i-1] ^ (idx[i-1] = idx[i]);
            }
        }
        l++;
    } while(r);  
    /* TODO 13: when will the while loop ends and why is this correct? */
    /* TODO 14: Can you optimize this while loop end condition to reduce the runtime? (Note that the time complexity won't necessarily be reduced after the optimization.) */
}

/* This section is for 6 people groups. If you're in a 5 people group, you don't need to answer the following TODOs. */
/* You may assume all the omitted codes are correct. */
/* You may also ignore the potentially off-by-1 errors in the code. */

void insertion_sort(int *idx, int *value, int left, int right) {
    /* omitted */
    /* This function will do the same thing as all sorting algorithms above using insertion sort. */
}

void heap_sort(int *idx, int *value, int left, int right) {
    /* omitted */
    /* This function will do the same thing as all sorting algorithms above using heap sort. */
}

int find_pivot(int *idx, int *value, int left, int right) {
    /* omitted */
    /* This function will return a pivot value just like in quicksort. */
    /* TODO 15: What technique can be apply to find a relatively efficient pivot. You only have to give the name of one technique. */
}
  
int partition(int *idx, int *value, int pivot, int left, int right) {
    /* omitted */
    /* This function will do the partition as in quicksort and then return the index of the place where the partition occurs. */
}

void intro_sort(int *idx, int *value, int left, int right, int depth) { /* TODO 16: What is the worst time complexity of introsort if applying the optimal pivot selection? */
    int size = right - left;

    if (size < 16) {    /* TODO 17: Why do introsort switch to insertion sort when the size is lower than a threshold? In other words, why is insertion sort faster than other sorting algorithms for a small size array? */
        insertion_sort(idx, value, left, right);
        return;
    }

    int X;
    if (depth == X) {  /* TODO 18: In introsort, people often use X as the threshold of depth to switch to heap sort when the original input size is n. Give a math expression of X using the variable n. */
        heap_sort(idx, value, left, right);
        return;
    }

    int pivot = find_pivot(idx, value, left, right);

    int partitionPoint = partition(idx, value, pivot, left, right);
    intro_sort(idx, value, partitionPoint+1, right, depth+1);
    intro_sort(idx, value, left, partitionPoint-1, depth+1);

    return;
}
/* TODO 19: There's a vulnerability if you apply the random pivot selection algorithm on quicksort since true randomness in the world of computers is hard to achieve and the pseudorandomness can be predicted if the random seed has leaked.
            How can you DoS (Denial of Service) attack a quicksort using random pivot selection if you have captured the random seed of the algorithm?
            Please answer from the perspective of time complexity. You don't need to elaborate on the details. */
/* TODO 20: Please briefly explain how the bozo sort works. */

/* After you have done reviewing the legacy code, you should start implementing the testbench for RD's functions. */
/* The function interfaces should be the same as the legacy code, and the names of functions are: */
/* 1. bubble_sort() */
/* 2. bucket_sort() */
/* 3. quick_sort() */

/* And don't forget to design some testcases to validate the correctness of the functions implemented by your coworkers. */