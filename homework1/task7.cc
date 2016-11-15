#include <iostream>
using namespace std;

#define FLOAT(name, value) float name = value

#define CONST_FLOAT(name, value) const FLOAT(name, value)

#define VAR_FLOAT(name) FLOAT(name, 0)

#define READ(input) cin >> input

#define SQUARE(v) (v * v)

#define SQUARE_OF(name, value) CONST_FLOAT(SQUARE_OF_##name, SQUARE(value))

#define RADIUS(n, r) SQUARE_OF(R##n, r)

#define DISTANCE_FROM_K2(operation)\
y1 = y operation R2;\
SQUARE_OF_DISTANCE = SQUARE_OF_X + SQUARE(y1)\

#define IS_POSITIVE(v) v > 0

#define IS_DISTANCE_LESS_THAN_R(r) SQUARE_OF_DISTANCE < SQUARE_OF_R##r

#define IS_DISTANCE_GREATER_THAN_R(r) SQUARE_OF_DISTANCE > SQUARE_OF_R##r

#define IS_DISTANCE_BETWEEN_R1_AND_R2() (IS_DISTANCE_GREATER_THAN_R(1)) && (IS_DISTANCE_LESS_THAN_R(2))

#define EVIL() point = Evil

#define GOOD() point = Good

#define IF_DISTANCE_IS__THAN_R1(comparsion, action)\
if(IS_DISTANCE_##comparsion##_THAN_R(1)) {\
    action();\
}\

#define IF_IS_DISTANCE_BETWEEN_R1_AND_R2_ELSE_IF_GREATER_THAN_R2(action1, action2)\
if(IS_DISTANCE_BETWEEN_R1_AND_R2()) {\
    action1();\
} else if(IS_DISTANCE_GREATER_THAN_R(2)) {\
    action2();\
}\

#define PRINT(value) cout << value

#define CASE(status)\
case status:\
    PRINT(#status);\
    break\

/* @begin */
CONST_FLOAT(R2, 3);
RADIUS(1, 1);
RADIUS(2, R2);
RADIUS(3, 6);

enum YinYang {
    Good,
    Evil,
    Neutral
};

int main() {
    VAR_FLOAT(x);
    VAR_FLOAT(y);
    VAR_FLOAT(y1);
    VAR_FLOAT(SQUARE_OF_DISTANCE);
    YinYang point = Neutral;
    READ(x);
    READ(y);
    SQUARE_OF(X, x);
    DISTANCE_FROM_K2(-);
    if((SQUARE_OF_X + SQUARE(y)) < SQUARE_OF_R3) {
        if(IS_POSITIVE(y)) {
            IF_DISTANCE_IS__THAN_R1(LESS, EVIL)
            if(IS_POSITIVE(x)) {
                IF_IS_DISTANCE_BETWEEN_R1_AND_R2_ELSE_IF_GREATER_THAN_R2(GOOD, EVIL)
            } else IF_DISTANCE_IS__THAN_R1(GREATER, GOOD)
        } else {
            DISTANCE_FROM_K2(+);
            IF_DISTANCE_IS__THAN_R1(LESS, GOOD)
            if(IS_POSITIVE(x)) {
                IF_DISTANCE_IS__THAN_R1(GREATER, EVIL)
            } else {
                IF_IS_DISTANCE_BETWEEN_R1_AND_R2_ELSE_IF_GREATER_THAN_R2(EVIL, GOOD)
            }
        }   
    }
    switch(point) {
        CASE(Good);
        CASE(Evil);
        CASE(Neutral);
    }
    PRINT('\n'); 

    return 0;
}