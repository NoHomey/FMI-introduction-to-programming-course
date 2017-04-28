#pragma once

#include <ostream>

class Rational {
public:
    friend std::ostream& operator<<(std::ostream& out, const Rational& r);

    Rational(const int nomi = 0, const int denomi = 1);

    Rational& operator+=(const Rational& other);

    Rational operator+(const Rational& other) const;

    Rational& operator*=(const Rational& other);

    Rational operator*(const Rational& other) const;

    Rational operator+() const;

    Rational operator-() const;

    Rational& operator/=(const int denomi);

    Rational operator/(const int denomi) const;

    operator float() const;

private:
    static int gcd(const int a, const int b);

    int nominator;

    int denominator;
};

std::ostream& operator<<(std::ostream& out, const Rational& r);
