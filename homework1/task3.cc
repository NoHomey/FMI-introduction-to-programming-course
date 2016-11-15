#include <iostream>
using namespace std;

#define NUMBER(name, value) number name = value

#define DEFINE_CONST(name, value) const NUMBER(name, value)

#define DEFINE_VARIABLE(name) NUMBER(name, 0)

#define FIND_LAST_4BITS(shift)\
if((inputNumber & (HEX_F << shift)) != 0) {\
    digits = shift;\
}\

/* @begin */
typedef unsigned long long number;

DEFINE_CONST(HEX_F, 15);
DEFINE_CONST(HEX_DIGIT, 4);

int main() {
    DEFINE_VARIABLE(inputNumber);
    DEFINE_VARIABLE(digits);
    cin >> inputNumber;
    NUMBER(first4Bits, inputNumber & HEX_F);
    FIND_LAST_4BITS(4)
    FIND_LAST_4BITS(8)
    FIND_LAST_4BITS(12)
    FIND_LAST_4BITS(16)
    FIND_LAST_4BITS(20)
    FIND_LAST_4BITS(24)
    FIND_LAST_4BITS(28)
    FIND_LAST_4BITS(32)
    FIND_LAST_4BITS(36)
    FIND_LAST_4BITS(40)
    FIND_LAST_4BITS(44)
    FIND_LAST_4BITS(48)
    FIND_LAST_4BITS(52)
    FIND_LAST_4BITS(56)
    FIND_LAST_4BITS(60)
    cout << (((inputNumber >> HEX_DIGIT) | (first4Bits << digits)) == inputNumber ?  "Yes" : "No") << '\n';

    return 0;
}