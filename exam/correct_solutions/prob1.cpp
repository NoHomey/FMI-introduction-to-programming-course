#include <iostream>
#include <new>

int compare(const int a, const int b) {
    if(a > b) {
        return 1;
    }
    if(a < b) {
        return -1;
    }

    return 0;
}

int main() {
    size_t n = 0;
    std::cin >> n;
    int* numbers = new(std::nothrow) int[n];
    int prevCompare = 0;
    int nextCompare = 0;
    bool isSequence = true;
    const size_t last = n - 1;
    if(numbers == NULL) {
        return 0;
    }
    for(size_t i = 0; i < n; ++i) {
        std::cin >> numbers[i];
    }
    if((n == 2) && (numbers[0] == numbers[1])) {
       isSequence = false; 
    }
    for(size_t i = 1; i < last; ++i) {
        prevCompare = compare(numbers[i - 1], numbers[i]);
        nextCompare = compare(numbers[i + 1], numbers[i]);
        if((prevCompare != nextCompare) || (prevCompare == 0)) {
            isSequence = false;
            break;
        }
    }
    delete[] numbers;
    std::cout << (isSequence ? "yes" : "no");

    return 0;
}