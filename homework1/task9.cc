#include <iostream>
using namespace std;

#define NUMBER(name, value) number name = value

#define DEFINE_VARAIBLE(name) NUMBER(name, 0)

#define READ(variable) cin >> variable

#define SIMULATE_OPERAND_4BIT_OVERFLOW(value) value &= MAX_4BIT_VALUE

#define DIRECT_OPERATION_CASE(oprtn, oprtr)\
case oprtn:\
result = leftOperand oprtr rightOperand;\
break\

#define PRINT(value) cout << value

/* @begin */
typedef unsigned short number;

const NUMBER(MAX_4BIT_VALUE, 15);

int main(void) {
    DEFINE_VARAIBLE(leftOperand);
    DEFINE_VARAIBLE(rightOperand);
    DEFINE_VARAIBLE(result);
    char operation = '\0';
    bool divisionAllowed = true;
    READ(leftOperand);
    READ(operation);
    READ(rightOperand);
    SIMULATE_OPERAND_4BIT_OVERFLOW(leftOperand);
    SIMULATE_OPERAND_4BIT_OVERFLOW(rightOperand);
    switch(operation) {
        DIRECT_OPERATION_CASE('+', +);
        DIRECT_OPERATION_CASE('-', -);
        DIRECT_OPERATION_CASE('*', *);
        case '/':
        case '%':
            divisionAllowed = rightOperand != 0;
            if(divisionAllowed) {
                result = operation == '/' ? (leftOperand / rightOperand) : (leftOperand % rightOperand);
            }
    }
    if(divisionAllowed) {
        PRINT((result & MAX_4BIT_VALUE));
    } else {
        PRINT("Division by zero!");
    }
    PRINT('\n');

    return 0;
}