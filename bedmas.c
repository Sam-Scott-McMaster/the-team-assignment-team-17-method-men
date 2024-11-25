#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "arithmeticOperations.h"
#include "bedmas.h"


double bedmasCalculation(char* expression){
    int length = expressionLength(expression);
    double equals = 0;
    for(int element = 0; element < length; element++){
        switch (expression[element]) {
            case '+':
                equals= addition(expression[element-1] - '0', expression[element+1] - '0');
                break;
            case '-':
                subtraction(expression[element-1] - '0', expression[element+1] - '0');
                break;
            case '*':
                mutliplication(expression[element-1] - '0', expression[element+1] - '0');
                break;
            case '/':
                division(expression[element-1] - '0', expression[element+1] - '0');
                break;
        }
    }
    return equals;
}

int expressionLength(char* expression){
    int length = sizeof(expression) / sizeof(expression[0]);
    return length;
}

int main(){
    //alternatively we could build our own personal bedmas system with the arithmaticOperations file and some logic
    char expression[] = {'1','+','3'};

    double equals = bedmasCalculation(expression);
    printf("Sums to be %.0f\n", equals);
    return 0;
}