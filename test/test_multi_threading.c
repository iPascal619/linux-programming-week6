#include <assert.h>
#include <stdio.h>
#include "multi_threading.h"

void test_multi_threading() {
    SumData data;
    
    // Test initialization
    assert(initialize_sum_data(&data, 1000) == 0);

    // Compare single and multi-threaded results
    long long single_result = single_threaded_sum(&data);
    long long multi_result = multi_threaded_sum(&data);

    assert(single_result == multi_result);
    printf("Single result: %lld\n", single_result);
    printf("Multi-threaded result: %lld\n", multi_result);

    free_sum_data(&data);
}

int main() {
    test_multi_threading();
    printf("Multi-threading tests passed!\n");
    return 0;
}