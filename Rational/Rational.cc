#include "Rational.h"

#include <stdexcept>

bool isNegative(const int n) {
    return n < 0;
}

int abs(const int n) {
    return (!isNegative(n)) ? n : -n;
}

std::ostream& operator<<(std::ostream& out, const Rational& r) {
    out << r.nominator << '/' << r.denominator;

    return out;
}

int Rational::gcd(const int a, const int b) {
    if(isNegative(a) || isNegative(b)) {
        return gcd(abs(a), abs(b));
    }

    return b == 0 ? a : gcd(b, a % b);
}


Rational::Rational(const int nomi, const int denomi)
: nominator(0), denominator(1) {
    if(denomi == 0) {
        throw std::invalid_argument("Devison by zero");
    }
    const bool isMinus = isNegative(nomi) ^ isNegative(denomi);
    nominator = abs(nomi);
    denominator = abs(denomi);
    const int d = gcd(nominator, denominator);
    nominator /= d;
    denominator /= d;
    if(isMinus) {
        nominator *= -1;
    }
}

Rational& Rational::operator+=(const Rational& other) {
    const int nomi = (nominator * other.denominator) + (other.nominator * denominator);
    const int denomi = denominator * other.denominator;
    *this = Rational(nomi, denomi);
    
    return *this;
}


Rational Rational::operator+(const Rational& other) const {
    Rational result = *this;
    result += other;
    return result;
}

Rational& Rational::operator*=(const Rational& other) {
    const int nomi = nominator * other.nominator;
    const int denomi = denominator * other.denominator;
    *this = Rational(nomi, denomi);
    
    return *this;
}

Rational Rational::operator*(const Rational& other) const {
    Rational result = *this;
    result *= other;
    return result;
}

Rational Rational::operator+() const {
    return *this;
}

Rational Rational::operator-() const {
    return Rational(denominator, nominator);
}

Rational& Rational::operator/=(const int denomi) {
    return operator*=(Rational(1, denomi));
}

Rational Rational::operator/(const int denomi) const {
    Rational result = *this;
    result /= denomi;
    return result;
}

Rational::operator float() const {
    return static_cast<float>(nominator) / static_cast<float>(denominator);
}
