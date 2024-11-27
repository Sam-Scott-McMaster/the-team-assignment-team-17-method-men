main: main.c evaluateWithParentheses.c evaluateWithParentheses.h bedmas.c bedmas.h arithmeticOperations.c arithmeticOperations.h
	gcc -o main main.c evaluateWithParentheses.c bedmas.c arithmeticOperations.c

cmain: main.c evaluateWithParentheses.c evaluateWithParentheses.h bedmas.c bedmas.h arithmeticOperations.c arithmeticOperations.h
	gcc -o cmain --coverage main.c evaluateWithParentheses.c bedmas.c arithmeticOperations.c

evaluateWithParentheses: evaluateWithParentheses.c evaluateWithParentheses.h bedmas.c bedmas.h arithmeticOperations.c arithmeticOperations.h
	gcc -o evaluateWithParentheses evaluateWithParentheses.c bedmas.c arithmeticOperations.c

bedmas: bedmas.c bedmas.h arithmeticOperations.c arithmeticOperations.h
	gcc -o bedmas bedmas.c arithmeticOperations.c
