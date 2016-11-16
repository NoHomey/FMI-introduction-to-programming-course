#include <iostream>
using namespace std;

#define FLOAT(name, value) float name = value

#define CONST_FLOAT(name, value) const FLOAT(name, value)

#define VAR_FLOAT(name) FLOAT(name, 0)

#define VAR_INT(name) int name = 0

#define DEFINE_LINEAR_EQUATION(n)\
VAR_FLOAT(a##n);\
VAR_FLOAT(b##n);\
VAR_FLOAT(c##n)\

#define READ(input) cin >> input

#define IS_LESS_THAN_EPSILON(diff) ((diff < EPSILON) && (diff > -EPSILON))

#define READ_LINEAR_EQUATION(n)\
READ(a##n);\
READ(b##n);\
READ(c##n)\

#define IS_ZERO(value) IS_LESS_THAN_EPSILON(value)

#define IS_NOT_ZERO(value) (!IS_LESS_THAN_EPSILON(value))

#define IS_NOT_ZERO_LINE(line) (IS_NOT_ZERO(a##line) || IS_NOT_ZERO(b##line) || IS_NOT_ZERO(c##line))

#define SOLUTION_PART_1(n, divisor) c##n / divisor##n

#define SOLUTION_PART_2(n, multiplier, found, divisor) (c##n - (multiplier##n * found)) / divisor##n

#define ONE_SOLUTION() solution = One

#define NO_SOLUTION() solution = No

#define GAUSE(n1, n2, n3, cnt , calc)\
CONST_FLOAT(k##n1, (-cnt##n2) / cnt##n1);\
CONST_FLOAT(calc##n3, (calc##n1 * k##n1) + calc##n2);\
CONST_FLOAT(c##n3, (c##n1 * k##n1) + c##n2)\

#define IF_ZERO_AND_NO_SOLUTION_THAN_SOLVE(zero, first, second, divisor1, divisor2, n1, n2)\
if(IS_ZERO(zero) && (solution == Many)) {\
    if IS_ZERO(divisor1##n1) {\
        NO_SOLUTION();\
    } else {\
        first = SOLUTION_PART_1(n1, divisor1);\
        second = SOLUTION_PART_2(n2, divisor1, first, divisor2);\
        ONE_SOLUTION();\
    }\
}\

#define FIND_SOLUTION(n, first, second, k, divisor1, divisor2)\
CONST_FLOAT(first##n, SOLUTION_PART_1(k, divisor1));\
CONST_FLOAT(second##n, SOLUTION_PART_2(n, divisor1, first##n, divisor2))\

#define DIFF(F, f) CONST_FLOAT(DIFF_##F, f##1 - f##2)

#define PRINT(value) cout << value

#define PRINT_CASE(what, message)\
case what:\
    PRINT(message);\
    break\

#define IF_ABS_WHOLE_PART_BETWEEN_THAN_MULTIPLIER(a, b, m)\
if((absWholePart >= a) && (absWholePart < b)) {\
    multiplier = m;\
}\

#define FORMAT(num)\
sign = (num <= -EPSILON ? -1 : 1);\
wholePart = num + (sign * EPSILON);\
multiplier = 1;\
absWholePart = sign * wholePart;\
IF_ABS_WHOLE_PART_BETWEEN_THAN_MULTIPLIER(0, 10, 10000)\
IF_ABS_WHOLE_PART_BETWEEN_THAN_MULTIPLIER(10, 100, 1000)\
IF_ABS_WHOLE_PART_BETWEEN_THAN_MULTIPLIER(100, 1000, 100)\
IF_ABS_WHOLE_PART_BETWEEN_THAN_MULTIPLIER(1000, 10000, 10)\
floatPart = (int)((num + (sign * EPSILON)) * multiplier) - (wholePart * multiplier);\
num = ((float)floatPart / multiplier) + wholePart\

/* @begin */
enum Solution {
    No,
    One,
    Many
};

CONST_FLOAT(EPSILON, 0.00001);

int main() {
    DEFINE_LINEAR_EQUATION(1);
    DEFINE_LINEAR_EQUATION(2);
    VAR_FLOAT(x);
    VAR_FLOAT(y);
    Solution solution = Many;
    READ_LINEAR_EQUATION(1);
    READ_LINEAR_EQUATION(2);
    if(IS_NOT_ZERO_LINE(1) && IS_NOT_ZERO_LINE(2)) {
        IF_ZERO_AND_NO_SOLUTION_THAN_SOLVE(a1, y, x, b, a, 1, 2)
        IF_ZERO_AND_NO_SOLUTION_THAN_SOLVE(a2, y, x, b, a, 2, 1)
        IF_ZERO_AND_NO_SOLUTION_THAN_SOLVE(b1, x, y, a, b, 1, 2)
        IF_ZERO_AND_NO_SOLUTION_THAN_SOLVE(b2, x, y, a, b, 2, 1)
        if(solution == Many) {
            GAUSE(1, 2, 3, a, b);
            GAUSE(2, 1, 4, b, a);
            if((IS_ZERO(b3) && IS_NOT_ZERO(c3)) || (IS_ZERO(a4) && IS_NOT_ZERO(c4))) {
                NO_SOLUTION();
            } else {
                FIND_SOLUTION(1, y, x, 3, b, a);
                FIND_SOLUTION(2, x, y, 4, a, b);
                DIFF(X, x);
                DIFF(Y, y);
                if(IS_LESS_THAN_EPSILON(DIFF_X) && IS_LESS_THAN_EPSILON(DIFF_Y)) {
                    x = x1;
                    y = y1;
                    ONE_SOLUTION();
                }
            }
        }
    }
    switch(solution) {
        PRINT_CASE(No, "No solution");
        PRINT_CASE(Many, "Many solutions");
        case One:
            VAR_INT(sign);
            VAR_INT(wholePart);
            VAR_INT(absWholePart);
            VAR_INT(floatPart);
            VAR_INT(multiplier);
            FORMAT(x);
            FORMAT(y);
            PRINT(x) << ' ' << y;
            break;
    }
    PRINT('\n');

    return 0;
}