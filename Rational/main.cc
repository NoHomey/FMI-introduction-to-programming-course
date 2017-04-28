#include "Rational.h"

#include <iostream>

int main() {
    Rational r = Rational(99, -11);
    std::cout << Rational(1, 2) + Rational(-4, -3) << std::endl;
    std::cout << Rational(3, 2) * Rational(4, 12) << std::endl;
    std::cout << Rational(1, 2) / 3 << std::endl;
    std::cout << Rational(3, 2) / -3 << std::endl;
    std::cout << -Rational(-99, -89) << std::endl;
    std::cout << +r << std::endl;
    std::cout << -r << std::endl;
    std::cout << static_cast<float>(r) << std::endl;

    Rational one = Rational(1, 10);
    Rational result = 0;
    for(int i = 0; i < 10; ++i) {
        result += one;
    }
    std::cout << +result << std::endl;
    std::cout << (result == 1.0) << std::endl;

    {
        Rational r = Rational(1, 2);
        r += Rational(4, 3);
        std::cout << +r << std::endl;
    }
    {
        Rational r = Rational(1, 2);
        r *= Rational(4, 3);
        std::cout << +r << std::endl;
    }
    {
        Rational r = Rational(1, 2);
        r /= -9;
        std::cout << +r << std::endl;
    }

    std::cout << static_cast<float>(Rational(25, 30) * -Rational(3,-18)) << std::endl;
    std::cout << static_cast<float>(Rational(-3, 3) + -Rational(4, -3)) << std::endl;
    std::cout << static_cast<float>(Rational(-3, 3) * -Rational(4, -3)) << std::endl;

    try {
        r = Rational(9, 0);
    } catch(std::invalid_argument& error) {
        std::cout << error.what() << std::endl;
    }

    try {
        r = Rational(9, 89) / 0;
    } catch(std::invalid_argument& error) {
        std::cout << error.what() << std::endl;
    }

    return 0;
}
