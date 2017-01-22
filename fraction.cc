#include <iostream>
#include <stdexcept>
#include <string>
#include <cmath>

class Fraction {
private:
static void throwIfDenominatorIsZero(const int divider) {
    if(divider == 0) {
        throw std::domain_error("Division by zero");
    }
}

int _numerator;
int _denominator;

int getGreatestCommonDivider() const {
    const int numerator = std::abs(_numerator);
    int greatestCommonDivider = 1;
    for(int divider = 2; divider <= numerator; ++divider) {
        if(isDividible(divider)) {
            greatestCommonDivider = divider;
        }
    }

    return greatestCommonDivider;
}

public:
Fraction(const int numerator = 0, const int denominator = 1)
: _numerator(numerator), _denominator(denominator) {
    throwIfDenominatorIsZero(denominator);
}

~Fraction() {}

void setNumerator(const int numerator) {
    _numerator = numerator; 
}

int getNumerator() const {
    return _numerator;
}

void setDenominator(const int denominator) {
    throwIfDenominatorIsZero(denominator);
    _denominator = denominator; 
}

int getDenominator() const {
    return _denominator;
}

void print() const {
    std::cout << _numerator;
    if(_denominator != 1) {
        std::cout << '/' << _denominator;
    }
    std::cout << std::endl;
}

void print(const std::string& name) const {
    std::cout << name << " = ";
    print();
}

bool isInteger() const {
    return (_numerator % _denominator) == 0;
}

bool isDividible(const int divider) const {
    return (divider != 0) && ((_numerator % divider) == 0) && ((_denominator % divider) == 0);
}

Fraction operator+(const Fraction& fraction) const {
    return Fraction(
        ((_numerator * fraction._denominator) + (fraction._numerator * _denominator))
        , (_denominator * fraction._denominator));
}

Fraction normalizate() {
    if(isInteger()) {
        return Fraction((_numerator / _denominator), 1);
    }
    const int greatestCommonDivider = getGreatestCommonDivider();
    const int absNumerator = std::abs(_numerator);
    const int absDenominator = std::abs(_denominator);
    int sign = (_numerator / absNumerator) * (_denominator / absDenominator);
    if(greatestCommonDivider > 1) {
        return Fraction((sign * absNumerator / greatestCommonDivider), (absDenominator / greatestCommonDivider));
    }

    return Fraction((sign * absNumerator), absDenominator);
}
};

void printFractionType(const Fraction& fraction, const std::string& name) {
    std::cout << name << " is" << (fraction.isInteger() ? "" : " not") << " integer" << std::endl;
}

int main() {
    Fraction* f = new Fraction(1, 2);
    f->print();
    delete f;
    Fraction a(5, 6);
    Fraction b(6, -6);
    a.print("a");
    printFractionType(a, "a");
    b.print("b");
    printFractionType(b, "b");
    b.normalizate().print("normalization of b");
    Fraction added = a + b;
    added.print("a + b");
    added.normalizate().print("normalization of a + b");
    added.setNumerator(3);
    std::cout << added.getNumerator() << std::endl;
    added.setDenominator(4);
    std::cout << added.getDenominator() << std::endl;
    added.print();
    (Fraction(1, 2) + Fraction(7, 3)).print("1/2 + 7/3");

    return 0;
}