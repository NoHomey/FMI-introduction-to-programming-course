#include <iostream>
#include <iomanip>

const double EPSILON = -0.0001;

template<typename T = double>
T input();

int main() {
    size_t N = input<size_t>();
    double D = input();
    double halfSquareOfD = D * D / 2;
    double S = 0;
    double v = 0;
    double a = 0;
    double Sn = 0;
    for(size_t i = 0; i < N; ++i) {
        a = input();
        Sn = (v * D) + (a * halfSquareOfD);
        if(Sn < EPSILON) {
            Sn = 0;
        }
        S += Sn;
        v += a * D;
        if(v < EPSILON) {
            v = 0;
        }
    }
    std::cout << std::fixed << std::setprecision(5) << (S < EPSILON ? 0 : S) << '\n';

    return 0;
}

template<typename T>
T input() { 
    T value; 
    std::cin >> value; 
    return value; 
}