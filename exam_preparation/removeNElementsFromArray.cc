#include <iostream>

template<typename T>
void removeN(T* arr, const size_t begin, const size_t count, const size_t length) {
    size_t i = begin + count;
    for(; i < length; ++i) {
        arr[i - count] = arr[i];
        arr[i] = 0;
    }
    for(i -= count; i < length; ++i) {
        arr[i] = 0;
    }
}

int main() {
    int arr[5] = {9, 1, 2, 3, 4};
    removeN(arr, 1, 3, 5);
    for(size_t i = 0; i < 5; ++i) {
        std::cout << arr[i] << ' ';
    }
    std::cout << std::endl;
    
    return 0;
}
