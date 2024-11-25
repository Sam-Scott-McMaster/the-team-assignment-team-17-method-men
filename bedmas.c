#include <stdlib.h>
#include <stdio.h>
#include "bedmas.h"
#include "arithmaticOperations.h"

double bedmas(char* expression){
    int length = expressionLength(expression);
    for(int element = 0; element < length; element++){
        printf("%c ", expression[element]);
    }
}

int expressionLength(char* expression){
    int length = sizeof(expression) / sizeof(expression[0]);
    return length;
}

int main(){
    //potential option as bedmas is already built in
    printf("%d\n", (1 + 3) * 4);

    //alternatively we could build our own personal bedmas system with the arithmaticOperations file and some logic
    char expression[] = {'1','2','3'};

    bedmas(expression);

    return 0;
}