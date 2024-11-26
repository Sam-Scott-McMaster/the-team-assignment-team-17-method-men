#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "evaluateWithParentheses.h"
#include "bedmas.h"

// adjusts the values of the inpuuted array, to merge multi-digit numbers
char* adjustValues(char* data, int *size) {
    char* newArray = (char*)malloc(*size*sizeof(char));    // allocates memory for the adjusted array
    if (newArray == NULL) {
        printf("Memory allocation failed!\n");
        return NULL;
    }
    int newArrayIndex = 0;

    // iterates through each element in the given array
    for (int i = 0; i < *size; i++) {
        // checks if the char index is a number, and not an operation
        if (data[i] >= '0') {
            int result = 0; // resets the result variable for each integer found

            // loops while indeces are valid integers
            while (i < *size && data[i] >= '0') {
                result = result * 10 + (data[i] - '0'); // logic to transform consecutive digits to its proper number
                i++;    // moves index over after each number iteration
            }
            sprintf(&newArray[newArrayIndex], "%d", result);   // stores the number in the updated array as chars
            newArrayIndex += sprintf(&newArray[newArrayIndex], "%d", result);   // updates the index aftering adding the value
            i--;    // decrements i since while loop adds extra increment
        } 
        // if index is not a digit, simply append it to the array, and increment the new array index
        else {
            newArray[newArrayIndex] = data[i];
            newArrayIndex++;
        }
    }
    newArray[newArrayIndex] = '\0'; // appends the null terminator to the end of the array
    *size = newArrayIndex;  // updates the size
    return newArray;
}

char* evaluateWithParentheses(char* data, int *dataSize) {
    // loops until one of our conditions is met 
    while(1) {
        // intializes two variables to hold the position of the parantheses
        int openPosition = -1;
        int closedPosition = -1;

        // iterates through each element in the array of chars
        for (int i = 0; i < *dataSize; i++) {
            char currentIndex = data[i];
            // assigns value of openPosition to the index of the open bracket
            if (currentIndex == '(') {
                openPosition = i;
            }
            // if the second bracket is found, assign the index and break the loop
            else if (currentIndex == ')') {
                closedPosition = i;
                break;
            }
        }

        // if no parentheses were found, break out of the loop
        if (openPosition == -1 || closedPosition == -1) {
            break;
        }

        int subExpressionLength = closedPosition - openPosition - 1;  // assigns value to represent size of the new array
        // allocates memory for the sub expression
        char* subExpression = (char*)malloc((subExpressionLength + 1) * sizeof(char));    // adds an extra element for string terminator
        if (subExpression == NULL) {
            printf("Memory allocation failed.\n");
            return NULL;
        }

        strncpy(subExpression, &data[openPosition + 1], subExpressionLength); // copies over all of the data within the parantheses to the sub expression
        subExpression[subExpressionLength] = '\0';    // assigns string terminator

        // passes data array, with parentheses positions to other method to perform calculation 
        double parenthesesResult = bedmasCalculation(subExpression); // performs the calculation using the sub expression
        free(subExpression);    // frees memory for the sub expression after it's done being used

        char resultString[10];  // allocates space for the result string
        int resultLength = sprintf(resultString, "%.2f", parenthesesResult);  // writes parenthesesResult to resultString, and stores the length
        
        int newArraySize = *dataSize - (closedPosition - openPosition + 1) + resultLength; // adjusts new array size
        // allocates memory for array to hold the values inside the parantheses
        char* finalArray = (char*)malloc(newArraySize * sizeof(char));   
        if (finalArray == NULL) {
            printf("Memory allocation failed!\n");
            return NULL;
        }

        // copies everything before the open paranthesis
        int newArrayIndex = 0;
        for (int i = 0; i < openPosition; i++) {
            finalArray[newArrayIndex] = data[i];
            newArrayIndex++;
        }

        // copies the result string from between the parentheses
        for (int i = 0; i < resultLength; i++) {
            finalArray[newArrayIndex] = resultString[i];
            newArrayIndex++;
        }

        // copies everything after the close parenthesis
        for (int i = closedPosition + 1; i < *dataSize; i++) {
            finalArray[newArrayIndex] = data[i];
            newArrayIndex++;
        }

        finalArray[newArrayIndex] = '\0';    // appends the null terminator to the end of the array
        data = finalArray; // updates it after applying the parentheses
        *dataSize = newArraySize;   // updates the size
    }
    return data;
}