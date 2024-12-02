#include <stdio.h>
#include <math.h>
#include "calculator.h"

CalcResult perform_calculation(double num1, double num2, Operation op) {
    CalcResult result = {num1, num2, op, 0, 0};

    switch(op) {
        case ADD:
            result.result = num1 + num2;
            break;
        case SUBTRACT:
            result.result = num1 - num2;
            break;
        case MULTIPLY:
            result.result = num1 * num2;
            break;
        case DIVIDE:
            if (num2 == 0) {
                result.error = 1;
                fprintf(stderr, "Error: Division by zero\n");
            } else {
                result.result = num1 / num2;
            }
            break;
        default:
            result.error = 1;
            fprintf(stderr, "Error: Invalid operation\n");
    }

    return result;
}

void print_calculation_result(CalcResult result) {
    if (result.error) {
        printf("Calculation failed\n");
        return;
    }

    const char* op_symbols[] = {"+", "-", "*", "/"};
    printf("%.2f %s %.2f = %.2f\n", 
           result.num1, 
           op_symbols[result.op], 
           result.num2, 
           result.result);
}