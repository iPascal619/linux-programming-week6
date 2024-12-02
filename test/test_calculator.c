#include <assert.h>
#include "calculator.h"

void test_calculator() {
    CalcResult result;

    // Test addition
    result = perform_calculation(5, 3, ADD);
    assert(result.result == 8);

    // Test subtraction
    result = perform_calculation(10, 4, SUBTRACT);
    assert(result.result == 6);

    // Test multiplication
    result = perform_calculation(6, 7, MULTIPLY);
    assert(result.result == 42);

    // Test division
    result = perform_calculation(15, 3, DIVIDE);
    assert(result.result == 5);

    // Test division by zero
    result = perform_calculation(10, 0, DIVIDE);
    assert(result.error == 1);
}

int main() {
    test_calculator();
    printf("All calculator tests passed!\n");
    return 0;
}