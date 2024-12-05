#!/bin/bash
#
# A simple framework for testing the bn scripts
#
# Returns the number of failed test cases.
#
# Format of a test:
#     test 'command' expected_return_value 'stdin text' 'expected stdout' 'expected stderr'
#
# Some example test cases are given. You should add more test cases.
#
# Sam Scott, McMaster University, 2024


# GLOBALS: tc = test case number, fails = number of failed cases
declare -i tc=0
declare -i fails=0

############################################
# Run a single test. Runs a given command 3 times
# to check the return value, stdout, and stderr
#
# GLOBALS: tc, fails
# PARAMS: $1 = command
#         $2 = expected return value
#         $3 = standard input text to send
#         $4 = expected stdout
#         $5 = expected stderr
# RETURNS: 0 = success, 1 = bad return, 
#          2 = bad stdout, 3 = bad stderr
############################################
test() {
    tc=tc+1

    local COMMAND=$1
    local RETURN=$2
	local STDIN=$3
    local STDOUT=$4
    local STDERR=$5

    # CHECK RETURN VALUE
    $COMMAND <<< "$STDIN" >/dev/null 2>/dev/null
    local A_RETURN=$?

    if [[ "$A_RETURN" != "$RETURN" ]]; then
        echo "Test $tc Failed"
        echo "   $COMMAND"
        echo "   Expected Return: $RETURN"
        echo "   Actual Return: $A_RETURN"
        fails=$fails+1
        return 1
    fi

    # CHECK STDOUT
    local A_STDOUT=$($COMMAND <<< "$STDIN" 2>/dev/null)

    if [[ "$STDOUT" != "$A_STDOUT" ]]; then
        echo "Test $tc Failed"
        echo "   $COMMAND"
        echo "   Expected STDOUT: $STDOUT"
        echo "   Actual STDOUT: $A_STDOUT"
        fails=$fails+1
        return 2
    fi
    
    # CHECK STDERR
    local A_STDERR=$($COMMAND <<< "$STDIN" 2>&1 >/dev/null)

    if [[ "$STDERR" != "$A_STDERR" ]]; then
        echo "Test $tc Failed"
        echo "   $COMMAND"
        echo "   Expected STDERR: $STDERR"
        echo "   Actual STDERR: $A_STDERR"
        fails=$fails+1
        return 3
    fi
    
    # SUCCESS
    echo "Test $tc Passed"
    return 0
}

##########################################
# EXAMPLE TEST CASES
##########################################


# 1. addition test
test './cmain' 0 "1+2" 'Final result: 3.00' ''

# 2. subtraction test
test './cmain' 0 "5%3" 'Final result: 2.00' ''

# 3. multiplication test
test './cmain' 0 "4*2" 'Final result: 8.00' ''

# 4. division test
test './cmain' 0 "8/2" 'Final result: 4.00' ''

# 5. mixed operations
test './cmain' 0 "3+4*2" 'Final result: 11.00' ''

# 6. mixed operations 2
test './cmain' 0 '12*3/3' 'Final result: 12.00' ''

# 7. parenthese with higher precedence
test './cmain' 0 "(3+4)*2" 'Final result: 14.00' ''

# 8. nested parentheses
test './cmain' 0 "((2+3)%5)*2" 'Final result: 0.00' ''

# 9. zero as input
test './cmain' 0 "0" 'Final result: 0.00' ''

# 10. negative result
test './cmain' 0 "3%7" 'Final result: -4.00' ''

# 11. more complex parentheses I
test './cmain' 0 "((2+3)*(4%1))+(5*(6/2))" 'Final result: 30.00' ''

# 12. more complex parentheses II
test './cmain' 0 "((8%3)/(2+1))*(7%(3+2))" 'Final result: 3.34' ''

# 13. more complex parentheses III
test './cmain' 0 "(12/(3+(5%2)))+((6*2)%(4/2))" 'Final result: 12.00' ''

# 14. negative number input
test './cmain' 0 "-1+3" 'Final result: 2.00' ''

# 15. negative number input
test './cmain' 0 "(-3+5)*(4%2)" 'Final result: 4.00' ''

# 16. super complex calculation
test './cmain' 0 "((8*(3+2))/(10%(4/2)))+(6/(2+(8/4)))" 'Final result: 6.50' ''

# 17. super complex calculation II
test './cmain' 0 "((15/(3+(7%5)))*(6+(9/3)))%((8*2)/(4+2))" 'Final result: 24.33' ''

# 18. additional negative calculations
test './cmain' 0 "-2*3" 'Final result: -6.00' ''

# 19. additional negative calculations II
test './cmain' 0 "(2+1)*(-3%1)" 'Final result: -12.00' ''

# 20. additional negative calculations III
test './cmain' 0 "-4%(-3+7)" 'Final result: -8.00' ''

# 21. additional negative calculations III
test './cmain' 0 "-4/(-3+7)" 'Final result: -1.00' ''

# 22. complex negative calculations
test './cmain' 0 "((15/(3+(7%5)))*(6+(9/-3)))%((8*2)/(-4+2))" 'Final result: 17.00' ''

# return code
exit $fails