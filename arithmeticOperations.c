#include <stdlib.h>
#include <stdio.h>

/* The Method Men, Benjamin Bloomfield, 2024
 *
 * This program includes the four main operations that can be performed on user inputted numbers.
 * Each function handles the operation on two numbers that passed through upon function call.
 * Therefore, for numerous inputs of the user, these functions will repeately be called. 
 *
 * NOTE: waiting to discuss with group members how the GUI input will be handled.
*/

/* Function Name: addition
 * 
 * Paramters:
 *  double num1 --> first number received from GUI input
 *  double num2 --> second number received from GUI input
 * Function Description:
 *  Adds the two numbers that are passed through as arguments, and returns the sum.
*/
double addition(double num1, double num2) {
    double numberSum = num1 + num2;
    return numberSum;
}

/* Function Name: subtraction
 * 
 * Function Description:
 *  Subtracts the second number from the first, and returns the difference.
*/
double subtraction(double num1, double num2) {
    double numberDifference = num1 - num2;
    return numberDifference;
}

/* Function Name: multiplication
 * 
 * Function Description:
 *  Multiplies the two numbers that are passed through as arguments, and returns the product.
*/
double multiplication(double num1, double num2) {
    double numberProduct = num1 * num2;
    return numberProduct;
}

/* Function Name: division
 * 
 * Function Description:
 *  Divides the first number by the second number, and returns the quotient.
 *  If the second number is 0, send an error message to the GUI.
 *      User cannot continue entering numbers until clear is received
*/
double division(double num1, double num2) {
    double numberQuotient = num1 / num2;
    return numberQuotient;
}
