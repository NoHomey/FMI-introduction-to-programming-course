#include <iostream>
using namespace std;

#define NUMBER(name, value) number name = value

#define CONST_NUMBER(name, value) const NUMBER(name, value)

#define DEFINE_CHAR(name) char name = '\0'

#define DEFINE_NUMBER(name) NUMBER(name, 0)

#define READ(input) cin >> input

#define CONVERT_TO_NUMBER(x) const NUMBER(x##N, 1 + (x - 'a'))

#define ABS(n) (n < 0 ? -n : n)

#define KNIGHT_TEST(end, change) ((figure##end + change) == king##end) || ((figure##end - change) == king##end)

#define CHECK_FROM_KNIGHT(x, y)\
if(KNIGHT_TEST(XN, x)) {\
    check = KNIGHT_TEST(Y, y);\
}\

/* @begin */
typedef short number;

enum Figure {
    Queen = 'Q',
    Bishop = 'B',
    Knight = 'N',
    Rook = 'R'
};

int main(void) {
    DEFINE_CHAR(figure);
    DEFINE_CHAR(figureX);
    DEFINE_NUMBER(figureY);
    DEFINE_CHAR(kingX);
    DEFINE_NUMBER(kingY);
    bool check = false;
    READ(figure);
    READ(figureX);
    READ(figureY);
    READ(kingX);
    READ(kingY);
    CONVERT_TO_NUMBER(figureX);
    CONVERT_TO_NUMBER(kingX);
    CONST_NUMBER(DIFF_X, kingXN - figureXN);
    CONST_NUMBER(DIFF_Y, kingY - figureY);
    switch(figure) {
        case Queen:
        case Bishop:
            check = ABS(DIFF_X) == ABS(DIFF_Y);
            if(figure == Bishop) {
                break;
            }
        case Rook:
            if(!check) {
                check = (kingXN == figureXN) || (kingY == figureY);
            }
            break;
        case Knight:
            CHECK_FROM_KNIGHT(1, 2)
            CHECK_FROM_KNIGHT(2, 1)
    }
    cout << (check ?  "Yes" : "No") << '\n';

    return 0;
}