#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "evaluateWithParameters.h"
#include "bedmas.h"

int main() {
    // set of data received from the GUI functions
    char data[] = {'(', '9', '1', '+', '8', ')', '*', '3', '5', '6'};
    int size = sizeof(data) / sizeof(data[0]);

    // adjusts the values of the inputted array
    char* adjustedArray = adjustValues(data, size);
    if (adjustedArray == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }
    printf("Adjusted array: %s\n", adjustedArray);
    adjustedArray = evaluateWithParentheses(adjustedArray, &size);
    printf("Expression after evaluating parentheses: %s\n", adjustedArray);

    free(adjustedArray);
    return 0;
}