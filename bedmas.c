#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "arithmeticOperations.h"
#include "bedmas.h"

// Identify numbers, supporting decimals and negative numbers
double createNumbers(const char** expression) {
    char* endPtr;
    double number = strtod(*expression, &endPtr);
    *expression = endPtr;
    return number;
}

void seperateExpression(const char* expression, double* numbers, char* operators, int* numberCount, int* operatorCount) {
    *numberCount = 0;
    *operatorCount = 0;
    const char* ptr = expression;
    
    while (*ptr) {
        if (isdigit(*ptr)) {
            numbers[(*numberCount)++] = createNumbers(&ptr);
        }
        else if (strchr("+-*/", *ptr)) {
            operators[(*operatorCount)++] = *ptr++;
        }
        else {
            ptr++;
        }
    }
}

void multiDiv(double* numbers, char* operators, int* numberCount, int* operatorCount) {
    for (int operator = 0; operator <*operatorCount; operator++) {
        //multiplication check
        if (operators[operator] == '*'){
            numbers[operator] = multiplication(numbers[operator], numbers[operator + 1]);
        }
        //division check
        else if (operators[operator] == '/'){
            numbers[operator] = division(numbers[operator], numbers[operator + 1]);
        }
        //check to see if expression is valid
        if (operators[operator] == '*' || operators[operator] == '/'){
            // shift numbers left to overwrite the operand just used
            for (int i = operator + 1; i < (*numberCount-1); i++){
                numbers[i] = numbers[i + 1];
            }
            //shift operators left to overwrite the operator that was just processsed
            for (int i = operator; i < (*operatorCount-1); i++){
                operators[i] = operators[i + 1];
            }
            //decrease the total count of number and total count of operators by one
            (*numberCount) = (*numberCount) - 1;
            (*operatorCount) = (*operatorCount) - 1;
            operator = operator - 1; //revaluate the current index as it now represents another part of the expression
        }
    }
}

double addSub(double* numbers, char* operators, int operatorCount) {
    double result = numbers[0];
    for (int operator = 0; operator < operatorCount; operator++) {
        if (operators[operator] == '+') {
            result = addition(result, numbers[operator + 1]);
        } else if (operators[operator] == '-') {
            result = subtraction(result, numbers[operator + 1]);
        }
    }
    return result;
}

double bedmasCalculation(char* expression) {
    //create storage for our number list and operator lists
    double numbers[99];
    char operators[99];
    //count of the amount of numbers and the amount of operators
    int numberCount = 0;
    int operatorCount = 0;
    //divides the expression into operators and numbers, return these lists through pointer parameters
    seperateExpression(expression, numbers, operators, &numberCount, &operatorCount);
    //iterates through numbers and operators and for each multiplication or division operator the appropriate calulcation is performed
    multiDiv(numbers, operators, &numberCount, &operatorCount);
    //iterates through numbers and operators and for each addition or subtraction operator the appropriate calulcation is performed
    double result = addSub(numbers, operators, operatorCount);

    return result;
}

int main() {
    char expression[] = "61*2/3+4";

    double equals = bedmasCalculation(expression);
    printf("Sums to be %.2f\n", equals);

    char expression[] = "61*2/3+4";

    double equals = bedmasCalculation(expression);
    printf("Sums to be %.2f\n", equals);

    char expression[] = "61*2/3+4";

    double equals = bedmasCalculation(expression);
    printf("Sums to be %.2f\n", equals);
    return 0;
}
