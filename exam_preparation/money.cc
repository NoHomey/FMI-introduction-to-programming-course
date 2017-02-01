#include <iostream>

typedef unsigned short Number;

int main() {
    float money = 0;
    std::cin >> money;
    const Number banknotes = (Number)money;
    Number cents = (Number)(money * 100) - (banknotes * 100);
    std::cout << banknotes << '.' << cents << std::endl;
    const Number centsFrom20 = cents / 20;
    cents %= 20;
    const Number centsFrom5 = cents / 5;
    cents %= 5;
    std::cout << money << " = " << banknotes << ' ' << centsFrom20 << ' ' << centsFrom5 << ' ' << cents << std::endl;

    return 0;
}
