#include <iostream>

void print(int *array, unsigned int size) {
  std::cout << '[';
  for (size_t i = 0; i < size; ++i) {
    std::cout << array[i] << ((i + 1) == size ? "]\n" : ", ");
  }
}

void fill(int *array, unsigned int size, int fillValue, size_t start = 0) {
  for (size_t i = start; i < size; ++i) {
    array[i] = fillValue;
  }
}

void sort(int *array, unsigned int size) {
  size_t indexOfMinElement = 0;
  size_t i = 0;
  size_t j = 0;
  int tmp = 0;
  const unsigned int sizeMinusOne = size - 1;
  for (; i < sizeMinusOne; ++i) {
    indexOfMinElement = i;
    for (j = i + 1; j < size; ++j) {
      if (array[j] < array[indexOfMinElement]) {
        indexOfMinElement = j;
      }
    }
    if (indexOfMinElement != i) {
      tmp = array[i];
      array[i] = array[indexOfMinElement];
      array[indexOfMinElement] = tmp;
    }
  }
}

int find(int *array, unsigned int size, int element) {
  for (size_t i = 0; i < size; ++i) {
    if (array[i] == element) {
      return i;
    }
  }

  return -1;
}

void copy(int *arrayFrom, int *arrayTo, unsigned int size) {
  for (size_t i = 0; i < size; ++i) {
    arrayTo[i] = arrayFrom[i];
  }
}

int *resize(int *array, unsigned int size, unsigned int newSize) {
  int *newArray = new int[newSize];
  const size_t copySize = size < newSize ? size : newSize;
  copy(array, newArray, copySize);
  if (copySize == size) {
    fill(newArray, newSize, 0, size);
  }

  return newArray;
}

void insertElement(int *array, unsigned int size, unsigned int position,
                   int newElement) {
  for (size_t i = size - 1; i > position; --i) {
    array[i] = array[i - 1];
  }
  array[position] = newElement;
}

void deleteElement(int *array, unsigned int size, unsigned int position) {
  const unsigned int sizeMinusOne = size - 1;
  for (size_t i = position; i < sizeMinusOne; ++i) {
    array[i] = array[i + 1];
  }
  array[sizeMinusOne] = 0;
}

int main() {
  // Примери:
  int a[6];
  fill(a, 6, -9); // a = [-9, -9, -9, -9, -9, -9]
  print(a, 6);

  int b[] = {7, 5, 4, 8, 1, 6, 9, 4, 3, 2};
  sort(b, 10); // b = [1, 2, 3, 4, 4, 5, 6, 7, 8, 9]
  print(b, 10);

  std::cout << find(b, 10, 2) << std::endl;  // 1
  std::cout << find(b, 10, 9) << std::endl;  // 9
  std::cout << find(b, 10, 4) << std::endl;  // 3
  std::cout << find(b, 10, 42) << std::endl; // -1

  int c[10];
  copy(b, c, 10); // c = [1, 2, 3, 4, 4, 5, 6, 7, 8, 9]
  print(c, 10);
  copy(a, b, 6); // b = [-9, -9, -9, -9, -9, -9, 6, 7, 8, 9]
  print(b, 10);
  copy(c, b, 6); // b = [1, 2, 3, 4, 4, 5, 6, 7, 8, 9]
  print(b, 10);

  int *extendedB = resize(b, 10, 15);
  print(extendedB,
        15); // extendedB = [1, 2, 3, 4, 4, 5, 6, 7, 8, 9, 0, 0, 0, 0, 0]
  delete[] extendedB;

  int *shrinkedB = resize(b, 10, 5);
  print(shrinkedB, 5); // shrinkedB = [1, 2, 3, 4, 4]
  delete[] shrinkedB;

  print(b, 10);
  insertElement(b, 10, 0, -3); // b = [-3, 1, 2, 3, 4, 4, 5, 6, 7, 8]
  print(b, 10);
  insertElement(b, 10, 7, -13); // b = [-3, 1, 2, 3, 4, 4, 5, -13, 6, 7]
  print(b, 10);

  deleteElement(b, 10, 0); // b = [1, 2, 3, 4, 4, 5, -13, 6, 7, 0]
  print(b, 10);
  deleteElement(b, 10, 3); // b = [1, 2, 3, 4, 5, -13, 6, 7, 0, 0]
  print(b, 10);

  return 0;
}
