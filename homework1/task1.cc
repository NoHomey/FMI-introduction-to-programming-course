#include <iostream>
using namespace std;

#define NUMBER(name, value) number name = value

#define DEFINE_CONST(name, value) const NUMBER(name, value)

#define DEFINE_VARIABLE(name) NUMBER(name, 0)

#define EXTRACT_DIGIT(digit)\
digit = inputNumber % ONE_DIGIT;\
inputNumber /= ONE_DIGIT\

#define CASE_FOR_THOUSAND(digit) case digit: cout << 'M'

#define PRINT_AND_BREAK_IF(digit, print, value)\
cout << print;\
if(digit == value) {\
    break;\
}\

#define PRINT_ROMAN_CASE(digit, check, print, value)\
case check:\
PRINT_AND_BREAK_IF(digit, print, value)\

#define PRINT_ROMAN(digit, least, most, next)\
switch(digit) {\
    case 8:\
    case 7:\
    case 6:\
        PRINT_ROMAN_CASE(digit, 5, most, 5)\
    case 4:\
    case 3:\
        PRINT_AND_BREAK_IF(digit, least, 6)\
        if(digit == 4) {\
             cout << most;\
            break;\
        }\
        PRINT_ROMAN_CASE(digit, 2, least, 7)\
    case 9:\
    case 1:\
        cout << least;\
        if(digit == 9) {\
            cout << next;\
        }\
}\

/* @begin */
typedef unsigned short number;

DEFINE_CONST(MAX_INPUT_VALUE, 3000);
DEFINE_CONST(ONE_DIGIT, 10);

int main(void) {
    DEFINE_VARIABLE(inputNumber);
    DEFINE_VARIABLE(thousands);
    DEFINE_VARIABLE(hundreds);
    DEFINE_VARIABLE(tens);
    DEFINE_VARIABLE(ones);
    cin >> inputNumber;
    if((inputNumber > MAX_INPUT_VALUE) || (inputNumber == 0)) {
        cout << "Invalid number!";
    } else {
        EXTRACT_DIGIT(ones);
        EXTRACT_DIGIT(tens);
        EXTRACT_DIGIT(hundreds);
        EXTRACT_DIGIT(thousands);
        switch(thousands) {
            CASE_FOR_THOUSAND(3);
            CASE_FOR_THOUSAND(2);
            CASE_FOR_THOUSAND(1);
        }
        PRINT_ROMAN(hundreds, 'C', 'D', 'M')
        PRINT_ROMAN(tens, 'X', 'L', 'C')
        PRINT_ROMAN(ones, 'I', 'V', 'X')
    }
    cout << '\n';

    return 0;
}
