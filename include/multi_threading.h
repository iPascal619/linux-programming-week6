#ifndef MULTI_THREADING_H
#define MULTI_THREADING_H

#define MAX_THREADS 10
#define MAX_ELEMENTS 2000

typedef struct {
    int* array;
    int total_elements;
    int num_threads;
    long long total_sum;
} SumData;

int initialize_sum_data(SumData* data, int n);
long long single_threaded_sum(SumData* data);
long long multi_threaded_sum(SumData* data);
void free_sum_data(SumData* data);

#endif