#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "arithmeticOperations.h"
#include "bedmas.h"

/* Function Name: createNumbers
 * 
 * Parameters:
 * const char** expression --> double pointer to an expression
 * Function Description:
 *  Identify the numbers from a string as digits
 *  Return Value and Output: double number --> represented the string that was converted a number
 */
double createNumbers(const char** expression, int* isNegative) {
    char* endPtr;

    // learned about strtod from https://www.ibm.com/docs/ja/rdfi/9.6.0?topic=functions-strftime-convert-datetime-string
    //using to convert from string to a double
    double number = strtod(*expression, &endPtr);

    //update expression pointer
    *expression = endPtr;
    //if the number should be negative, return as negative
    if(*isNegative == 1){
        number = number*(-1);
        isNegative = 0;
    }
    return number;
}



/* Function Name: seperateExpression
 * 
 * Parameters:
 * const char* expression --> pointer to an expression
 *  double* numbers --> pointer to an array of numbers representing the operands of the expressions
 *  char* operators --> pointer to an array of operators in the expression
 *  int* numberCount --> pointer to an integer keeping count of the number of numbers in the expression
 *  int* operatorCount --> pointer to an integer keeping count of the number of operators in the expression
 * Function Description:
 *  divides the expression into operands and operators, both of these are storage as arrays.
 *  Return Value and Output: None, all variables are altered as pointer parameters
 */
void separateExpression(const char* expression, double* numbers, char* operators, int* numberCount, int* operatorCount) {
    *numberCount = 0;
    *operatorCount = 0;
    const char* ptr = expression;
    int isNegative=0;
    
    while (*ptr) {
        //if pointing to a digit, combine all sequential digits to form a number, store this in the numbers array 
        if (isdigit(*ptr)) {
            numbers[(*numberCount)++] = createNumbers(&ptr, &isNegative);
            isNegative = 0;
        }
        //if pointing to a operator, add the operator to the operators list
        else if (strchr("+%*/", *ptr)) {
            operators[(*operatorCount)++] = *ptr++;
            isNegative=0;
        }
        //check if a negative symbol is used, denoted by the percent operator
        else if (strchr("-", *ptr)) {
            ptr++;
            isNegative=1;
        }
    }
}


/* Function Name: multiDiv
 * 
 * Parameters:
 *  double* numbers --> pointer to an array of numbers representing the operands of the expressions
 *  char* operators --> pointer to an array of operators in the expression
 *  int* numberCount --> pointer to an integer keeping count of the number of numbers in the expression
 *  int* operatorCount --> pointer to an integer keeping count of the number of operators in the expression
 * Function Description:
 *  The multiDiv function is responsible for the performing the multiplication and division in the expression
 *  This happens before addition and subtraction as per bedmas
 *  Return Value and Output: None, all variables are altered as pointer parameters
 */
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

/* Function Name: addSub
 * 
 * Parameters:
 *  double* numbers --> pointer to an array of numbers representing the operands of the expressions
 *  char* operators --> pointer to an array of operators in the expression
 *  int* operatorCount --> pointer to an integer keeping count of the number of operators in the expression
 * Function Description:
 *  The addSub function is responsible for the adding and subtracting of the bedmas expression.
 *  Happens after multiDiv because of the order of bedmas.
 *  Return Value and Output: double result --> final value of the expression
 */
double addSub(double* numbers, char* operators, int operatorCount) {
    double result = numbers[0];
    //iterate through operators list
    for (int operator = 0; operator < operatorCount; operator++) {
        //if operator is +, add the result with the next number in the array
    if (operators[operator] == '+') {
        result = addition(result, numbers[operator + 1]);
    } else if (operators[operator] == '%') {
        result = subtraction(result, numbers[operator + 1]);
    }

    }
    return result;
}
/* Function Name: bedmasCalculation
 * 
 * Parameters:
 *  char* expression --> pointer to an expression
 * Function Description:
 *  Similar to a main method which will call all the above methods to evaluate an expression
 *  Will separate the expression, then call multiDiv to apply multiplication and division operators
 *  lastly addSub will be called which will apply the addition and subtraction operators returning a final result
 *  Return Value and Output: double result --> final value of the expression
 */
double bedmasCalculation(char* expression) {
    //create storage for our number list and operator lists
    double numbers[99];
    char operators[99];
    //count of the amount of numbers and the amount of operators
    int numberCount = 0;
    int operatorCount = 0;
    //divides the expression into operators and numbers, return these lists through pointer parameters
    separateExpression(expression, numbers, operators, &numberCount, &operatorCount);
    //iterates through numbers and operators and for each multiplication or division operator the appropriate calulcation is performed
    multiDiv(numbers, operators, &numberCount, &operatorCount);
    //iterates through numbers and operators and for each addition or subtraction operator the appropriate calulcation is performed
    double result = addSub(numbers, operators, operatorCount);

    return result;
}