#include <iostream>
using namespace std;

#define FLOAT(name, value) float name = value

#define CONST_FLOAT(name, value) const FLOAT(name, value)

#define VAR_FLOAT(input) FLOAT(input, 0)

#define INPUT(input1, input2)\
VAR_FLOAT(input1);\
VAR_FLOAT(input2)\

#define READ_VALUE(input) cin >> input

#define READ(input1, input2)\
READ_VALUE(input1);\
READ_VALUE(input2)\

#define SQUARE(v) (v * v)

#define SQUARE_OF(name, value) CONST_FLOAT(SQUARE_OF_##name, value)

#define RADIUS(n, r) SQUARE_OF(R##n, SQUARE(r))

#define LESS_THAN(a, b) (a <= (b - EPSILON))

#define GREATER_THAN(a, b) (a >= (b + EPSILON))

#define IF_DISTANCE_BETWEEN_RADIUS(r1, r2, points)\
if(GREATER_THAN(SQUARE_OF_DISTANCE, SQUARE_OF_R##r1) && LESS_THAN(SQUARE_OF_DISTANCE, SQUARE_OF_R##r2)) {\
    score = points;\
}\

/* @begin */
CONST_FLOAT(EPSILON, 0.001);
RADIUS(1, 8);
RADIUS(2, 3);
RADIUS(3, 1);

int main() {
    INPUT(x, y);
    INPUT(u, v);
    READ(x, y);
    READ(u, v);
    CONST_FLOAT(X, x + u);
    CONST_FLOAT(Y, y + v);
    SQUARE_OF(DISTANCE, SQUARE(X) + SQUARE(Y));
    VAR_FLOAT(score);
    if LESS_THAN(SQUARE_OF_DISTANCE, SQUARE_OF_R3) {
        score = 60;
    }
    IF_DISTANCE_BETWEEN_RADIUS(3, 2, 20)
    IF_DISTANCE_BETWEEN_RADIUS(2, 1, 10)
    cout << score << '\n';

    return 0;
}