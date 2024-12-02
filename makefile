main: main.c evaluateWithParentheses.c evaluateWithParentheses.h bedmas.c bedmas.h arithmeticOperations.c arithmeticOperations.h
	gcc -o main main.c evaluateWithParentheses.c bedmas.c arithmeticOperations.c

cmain: main.c evaluateWithParentheses.c evaluateWithParentheses.h bedmas.c bedmas.h arithmeticOperations.c arithmeticOperations.h
	gcc -o cmain --coverage main.c evaluateWithParentheses.c bedmas.c arithmeticOperations.c

evaluateWithParentheses: evaluateWithParentheses.c evaluateWithParentheses.h bedmas.c bedmas.h arithmeticOperations.c arithmeticOperations.h
	gcc -o evaluateWithParentheses evaluateWithParentheses.c bedmas.c arithmeticOperations.c

bedmas: bedmas.c bedmas.h arithmeticOperations.c arithmeticOperations.h
	gcc -o bedmas bedmas.c arithmeticOperations.c

calculator: calculator.c 
	gcc `pkg-config --cflags gtk4` -o calculator calculator.c `pkg-config --libs gtk4`

main-calculator: calculator.c evaluateWithParentheses.c evaluateWithParentheses.h bedmas.c bedmas.h arithmeticOperations.c arithmeticOperations.h
	gcc `pkg-config --cflags gtk4` -o calculator calculator.c `pkg-config --libs gtk4` evaluateWithParentheses.c bedmas.c arithmeticOperations.c