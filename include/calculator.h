#ifndef CALCULATOR_H
#define CALCULATOR_H

typedef enum {
    ADD,
    SUBTRACT,
    MULTIPLY,
    DIVIDE
} Operation;

typedef struct {
    double num1;
    double num2;
    Operation op;
    double result;
    int error;
} CalcResult;

CalcResult perform_calculation(double num1, double num2, Operation op);
void print_calculation_result(CalcResult result);

#endif