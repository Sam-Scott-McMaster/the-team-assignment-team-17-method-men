int evaluateWithParentheses(char data[], int dataSize) {
    // loops until one of our conditions is met 
    while (true) {
        // intializes two variables to hold the position of the parantheses
        int openPosition = -1;
        int closedPosition = -1;

        // iterates through each element in the array of chars
        for (int i = 0; i < dataSize; i++) {
            char currentIndex = data[i]
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

        // passes data array, with parentheses positions to other method to perform calculation 
        int parenthesesResult = bedmasCalculation(data, openPosition + 1, closedPosition);
        // FIGURE OUT WAY TO TRIM DATA ARRAY
    }
    
    // iterates through each element in the parantheses
    for (int j = 0)
}