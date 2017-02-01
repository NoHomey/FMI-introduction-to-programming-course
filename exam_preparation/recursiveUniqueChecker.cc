#include <iostream>

typedef unsigned int Number;

bool checkForDigit(const Number number, const Number checkFor) {
    if(number == 0) {
        return false;
    }
    if((number % 10) == checkFor) {
        return true;
    }

    return checkForDigit(number / 10, checkFor);
}

bool isNumberOfUniqueDigits(const Number number) {
    const Number numberWithoutADigit = number / 10;
    if(number == 0) {
        return true;
    }
    if(checkForDigit(numberWithoutADigit, number % 10)) {
        return false;
    }

    return isNumberOfUniqueDigits(numberWithoutADigit);
}

int main() {
    Number input = 0;
    std::cin >> input;
    std::cout << (isNumberOfUniqueDigits(input) ? "yes" : "no") << std::endl;

    return 0;
}
