#include <cmath>
#include <cstdio>

#define PRINT_PAIR(first, second) std::printf("%llu %llu\n", first, second)

#define SETUP_PRIME_NUMBER_CHECKER()\
Number squareRootOfNumber = 0;\
Number divisor = 2

#define CHECH_IS_PRIME_NUMBER(tested)\
squareRootOfNumber = (Number)std::sqrt(tested);\
for(divisor = 2; divisor <= squareRootOfNumber; ++divisor) {\
    if((tested % divisor) == 0) {\
        break;\
    }\
}

#define IS_PRIME_NUMBER() divisor > squareRootOfNumber

typedef unsigned long long Number;

int main() {
    Number n = 0;
    Number middleNumber = 0;
    Number firstNumber = 0;
    Number secondNumber = 0;
    Number countOfTweenNumbers = 0;
    SETUP_PRIME_NUMBER_CHECKER();
    std::scanf("%llu", &countOfTweenNumbers);
    PRINT_PAIR((Number)3, (Number)5);
    while(countOfTweenNumbers > 1) {
        while(true) {
            ++n;
            middleNumber = 6 * n;
            firstNumber = middleNumber - 1;
            secondNumber = middleNumber + 1;
            CHECH_IS_PRIME_NUMBER(firstNumber);
            if(!(IS_PRIME_NUMBER())) {
                continue;
            }
            CHECH_IS_PRIME_NUMBER(secondNumber);
            if(IS_PRIME_NUMBER()) {
                PRINT_PAIR(firstNumber, secondNumber);
                break;
            }
        }
        --countOfTweenNumbers;
    }

    return 0;
}