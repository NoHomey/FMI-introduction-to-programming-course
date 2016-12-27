#include <iostream>
#include <stdexcept>
#include <string>

typedef unsigned long long Number;

Number input();

template<typename T, typename S>
class Generator {
protected:
virtual T yield(const S state) const = 0;

public:
virtual T next() = 0;
};

class NumberRaisedOnPower {
protected:
Number numberBeeingRaisedOnPower;
Number numberRaisedOnPower;

public:
NumberRaisedOnPower(const Number numberToBeRaised);

operator Number() const;

NumberRaisedOnPower& operator++();

NumberRaisedOnPower operator++(int);

template<typename C>
Number operator+(const C n) const;
};

class NumberDigitStriker: public Generator<Number, NumberRaisedOnPower> {
protected:
Number numberWithEachDigitBeeingStriked;
NumberRaisedOnPower base10RaisedOnPower;

Number yield(const NumberRaisedOnPower curretValueOfBase10RaisedOnPower) const;

public:
class NoDigitToStrikeFrom: public std::out_of_range {
public:
NoDigitToStrikeFrom(const Number numberWithStrikedDigits);
};

NumberDigitStriker(const Number numberTarget);

Number next();
};

bool strikeEqual(const Number biggerNumber, const Number smallerNumber);

void printBool(const bool result);

int main() {
    const Number biggerNumber = input();
    const Number smallerNumber = input();
    printBool(strikeEqual(biggerNumber, smallerNumber));
    
    return 0;
}

Number input() {
    Number value;
    std::cin >> value;
    return value;
}


NumberRaisedOnPower::NumberRaisedOnPower(const Number numberToBeRaised)
: numberBeeingRaisedOnPower{numberToBeRaised}, numberRaisedOnPower{1} {}

NumberRaisedOnPower::operator Number() const {
    return numberRaisedOnPower;
}

NumberRaisedOnPower& NumberRaisedOnPower::operator++() {
    numberRaisedOnPower *= numberBeeingRaisedOnPower;
    return *this;
}

NumberRaisedOnPower NumberRaisedOnPower::operator++(int) {
    NumberRaisedOnPower current = *this;
    ++(*this);
    return current;
}

template<typename C>
Number NumberRaisedOnPower::operator+(const C n) const {
    NumberRaisedOnPower current = *this;
    for(C counter = 0; counter < n; ++counter) {
        ++current;
    }
    return current;
}

Number NumberDigitStriker::yield(const NumberRaisedOnPower curretValueOfBase10RaisedOnPower) const {
    return ((numberWithEachDigitBeeingStriked / (curretValueOfBase10RaisedOnPower + 1))
        * curretValueOfBase10RaisedOnPower)
        + (numberWithEachDigitBeeingStriked % curretValueOfBase10RaisedOnPower);
}

NumberDigitStriker::NoDigitToStrikeFrom::NoDigitToStrikeFrom(const Number numberWithStrikedDigits)
: std::out_of_range(
    "No more digits to strike from "
    + std::to_string(numberWithStrikedDigits)
    + "\nEach digit was striked!"
) {}

NumberDigitStriker::NumberDigitStriker(const Number numberTarget)
: numberWithEachDigitBeeingStriked{numberTarget}, base10RaisedOnPower{10} {}

Number NumberDigitStriker::next() {
    if(base10RaisedOnPower > numberWithEachDigitBeeingStriked) {
        throw NoDigitToStrikeFrom(numberWithEachDigitBeeingStriked);
    }
    const Number targetWithStrikedDigit = yield(base10RaisedOnPower);
    base10RaisedOnPower++;

    return targetWithStrikedDigit;
}

bool strikeEqual(const Number biggerNumber, const Number smallerNumber) {
    NumberDigitStriker digitStriker = {biggerNumber};
    try{
        Number biggerNumberWithStrikedDigit = digitStriker.next();
        while(true) {
            if(biggerNumberWithStrikedDigit == smallerNumber) {
                return true;
            }
            biggerNumberWithStrikedDigit = digitStriker.next();
        }
    } catch(NumberDigitStriker::NoDigitToStrikeFrom& error) {
        return false;
    }

    return false;
}

void printBool(const bool result) {
    std::cout << (result ? "Yes" : "No") << '\n';
}