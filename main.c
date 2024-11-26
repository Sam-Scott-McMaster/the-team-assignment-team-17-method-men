#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "evaluateWithParentheses.h"
#include "bedmas.h"

int main() {
    // set of data received from the GUI functions
    //char data[] = {'(', '9', '+', '8', ')', '*', '3', '6'};
    char data[] = "(13-8)*4";
    int size = sizeof(data) / sizeof(data[0]);

    // adjusts the values of the inputted array
    char* adjustedArray = adjustValues(data, &size);
    // checks if memory allocation failed
    if (adjustedArray == NULL) {
        return -1; 
    }
    printf("Adjusted array: %s\n", adjustedArray);

    // evaluates data to extract parentheses
    char* evaluatedArray = evaluateWithParentheses(adjustedArray, &size);
    // checks if memory allocation failed
    if (evaluatedArray == NULL) {
        free(adjustedArray); // Free adjustedData before exiting
        return -1; // Exit if memory allocation failed
    }
    printf("Expression after evaluating parentheses: %s\n", evaluatedArray);
    
    double result = bedmasCalculation(evaluatedArray);   // calulcates final result
    printf("Final result: %.2f\n", result);

    free(adjustedArray);
    free(evaluatedArray);
    return 0;
}