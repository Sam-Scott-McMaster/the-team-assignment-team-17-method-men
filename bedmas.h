double bedmasCalculation(char* expression);
double createNumbers(const char** expression, int* isNegative);
void separateExpression(const char* expression, double* numbers, char* operators, int* numberCount, int* operatorCount);
void multiDiv(double* numbers, char* operators, int* numberCount, int* operatorCount);
double addSub(double* numbers, char* operators, int operatorCount);
