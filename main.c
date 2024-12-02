#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "evaluateWithParentheses.h"
#include "bedmas.h"



int main() {
    // set of data received from the GUI functions
    //char data[] = {'(', '9', '+', '8', ')', '*', '3', '6'};
    int maxSize = 100;
    char data[100];
    fgets(data, maxSize, stdin);

    data[strcspn(data, "\n")] = '\0';

    int size = strlen(data);

    // adjusts the values of the inputted array
    char* adjustedArray = adjustValues(data, &size);
    
    //printf("Adjusted array: %s\n", adjustedArray);

    // evaluates data to extract parentheses
    char* evaluatedArray = evaluateWithParentheses(adjustedArray, &size);
    //printf("Expression after evaluating parentheses: %s\n", evaluatedArray);
    
    double result = bedmasCalculation(evaluatedArray);   // calulcates final result
    printf("Final result: %.2f\n", result);

    free(adjustedArray);
    if (evaluatedArray != adjustedArray) {
        free(evaluatedArray);
    }
    return 0;
}