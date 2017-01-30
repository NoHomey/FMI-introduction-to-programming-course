#include <iostream>
#include <new>

#define PRINT_BOOL(val) (val ? "Yes" : "No")

void sort(int* array, const size_t length) {
    const size_t lengthMinusOne = length - 1;
    size_t minIndex = 0;
    int tmp = 0;
    for(size_t i = 0; i < lengthMinusOne; ++i) {
        minIndex = i;
        for(size_t j = i; j < length; ++j) {
            if(array[j] < array[minIndex]) {
                minIndex = j;
            }
        }
        if(minIndex != i) {
            tmp = array[minIndex];
            array[minIndex] = array[i];
            array[i] = tmp;
        }
    }
}

bool areVectorsInPermutation(int* vector1, int* vector2, const size_t length) {
    sort(vector1, length);
    sort(vector2, length);
    for(size_t i = 0; i < length; ++i) {
        if(vector1[i] != vector2[i]) {
            return false;
        }
    }

    return true;
}

void destoryMatrix(int** matrix, const size_t n) {
    for(size_t i = 0; i < n; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

int** readSquareMatrix(const size_t n) {
    int** matrix = new(std::nothrow) int*[n];
    if(matrix == NULL) {
        return NULL;
    }
    for(size_t i = 0; i < n; ++i) {
        matrix[i] = new(std::nothrow) int[n];
        if(matrix[i] == NULL) {
            destoryMatrix(matrix, i);
            return NULL;
        }
        for(size_t j = 0; j < n; ++j) {
            std::cin >> matrix[i][j];
        }
    }
    return matrix;
}

bool matrixHasTwoLineInPermutation(int** matrix, const size_t n) {
    for(size_t i = 1; i < n; ++i) {
        if(areVectorsInPermutation(matrix[0], matrix[i], n)) {
            return true;
        }
    }

    return false;
}

bool matrixDiagonalsAreInPermutation(int** matrix, const size_t n) {
    int* mainDiag = new(std::nothrow) int[n];
    if(mainDiag == NULL) {
        return false;
    }
    int* secDiag = new(std::nothrow) int[n];
    if(secDiag == NULL) {
        delete[] mainDiag;
        return false;
    }
    for(size_t i = 0, j = n - 1; i < n; ++i, --j) {
        mainDiag[i] = matrix[i][i];
        secDiag[i] = matrix[i][j];
    }
    const bool areInPermutation = areVectorsInPermutation(mainDiag, secDiag, n);
    delete[] mainDiag;
    delete[] secDiag;

    return areInPermutation;
}

int main() {
    size_t n = 0;
    std::cin >> n;
    int** matrix = readSquareMatrix(n);
    if(matrix == NULL) {
        return 0;
    }
    std::cout << "There are lines in permutation: " << PRINT_BOOL(matrixHasTwoLineInPermutation(matrix, n)) << std::endl;
    std::cout << "Diagonals are in permutation: " << PRINT_BOOL(matrixDiagonalsAreInPermutation(matrix, n)) << std::endl;
    destoryMatrix(matrix, n);

    return 0;
}
