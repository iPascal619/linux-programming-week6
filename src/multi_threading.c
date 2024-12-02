#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "multi_threading.h"

typedef struct {
    int thread_id;
    SumData* shared_data;
    int start;
    int end;
    long long partial_sum;
} ThreadArgs;

void* thread_sum_worker(void* arg) {
    ThreadArgs* thread_args = (ThreadArgs*)arg;
    thread_args->partial_sum = 0;

    for (int i = thread_args->start; i < thread_args->end; i++) {
        thread_args->partial_sum += thread_args->shared_data->array[i];
    }

    return NULL;
}

int initialize_sum_data(SumData* data, int n) {
    if (n < 200 || n > 2000) {
        fprintf(stderr, "Invalid input: n must be between 200 and 2000\n");
        return -1;
    }

    data->total_elements = n;
    data->array = malloc(n * sizeof(int));
    if (!data->array) {
        fprintf(stderr, "Memory allocation failed\n");
        return -1;
    }

    for (int i = 0; i < n; i++) {
        data->array[i] = i + 1;
    }

    data->num_threads = (n / 100 > MAX_THREADS) ? MAX_THREADS : n / 100;
    data->total_sum = 0;

    return 0;
}

long long single_threaded_sum(SumData* data) {
    long long total = 0;
    for (int i = 0; i < data->total_elements; i++) {
        total += data->array[i];
    }
    return total;
}

long long multi_threaded_sum(SumData* data) {
    pthread_t threads[MAX_THREADS];
    ThreadArgs thread_args[MAX_THREADS];

    for (int i = 0; i < data->num_threads; i++) {
        thread_args[i].thread_id = i;
        thread_args[i].shared_data = data;
        thread_args[i].start = i * (data->total_elements / data->num_threads);
        thread_args[i].end = (i == data->num_threads - 1) ? 
            data->total_elements : 
            thread_args[i].start + (data->total_elements / data->num_threads);

        if (pthread_create(&threads[i], NULL, thread_sum_worker, &thread_args[i]) != 0) {
            fprintf(stderr, "Thread creation failed\n");
            return -1;
        }
    }

    long long total_sum = 0;
    for (int i = 0; i < data->num_threads; i++) {
        pthread_join(threads[i], NULL);
        total_sum += thread_args[i].partial_sum;
    }

    return total_sum;
}

void free_sum_data(SumData* data) {
    free(data->array);
    data->array = NULL;
    data->total_elements = 0;
}