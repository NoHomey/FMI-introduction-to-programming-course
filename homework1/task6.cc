#include <iostream>
using namespace std;

#define INT(name, value) int name = value

#define DEFINE_VARIABLE(name) INT(name, 0)

#define DEFINE_CONST(name, value) const INT(name, value)

#define DEFINE_RECTANGLE(rec)\
DEFINE_VARIABLE(x##rec##1);\
DEFINE_VARIABLE(y##rec##1);\
DEFINE_VARIABLE(height##rec);\
DEFINE_VARIABLE(width##rec)\

#define READ_RECTANGLE(rec)\
cin >> x##rec##1;\
cin >> y##rec##1;\
cin >> height##rec;\
cin >> width##rec\

#define CALCULATE_AXIS2(axis, adder, rec)\
DEFINE_CONST(axis##rec##2, axis##rec##1 + adder##rec)

#define MIN(a, b) (a < b ? a : b)

#define MAX(a, b) (a > b ? a : b)

#define CALCULATE(axis, adder)\
CALCULATE_AXIS2(axis, adder, 1);\
CALCULATE_AXIS2(axis, adder, 2);\
DEFINE_CONST(adder, MIN(axis##12, axis##22) - MAX(axis##11, axis##21))\

/* @begin */
int main(void) {
    DEFINE_RECTANGLE(1);
    DEFINE_RECTANGLE(2);
    READ_RECTANGLE(1);
    READ_RECTANGLE(2);
    CALCULATE(x, width);
    CALCULATE(y, height);
    cout << (((width > 0) && (height > 0)) ? (width * height) : 0) << '\n';

    return 0;
}