/**
*
* Solution to homework task
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2016/2017
*
* @author Ivo Stratev
* @idnumber 45342
* @task 8
* @compiler GCC
*
*/

#include <iostream>
#include <new>

int input();

int mod3(const int n);

bool compareIsSmaller(const int compared, const int comparator);

int main() {
  const int length = input();
  const int lengthMinusOne = length - 1;
  int* numbers = nullptr;
  try {
    numbers = new int[length];
  } catch (const std::bad_alloc& error) {
    throw error;
  }
  int tmp = 0;
  int i = 0;
  int j = 0;
  int indexOfMinElement = 0;
  int previusIndex = 0;
  for (i = 0; i < length; ++i) {
    numbers[i] = input();
  }
  for (i = 0; i < lengthMinusOne; ++i) {
    indexOfMinElement = i;
    for (j = i + 1; j < length; ++j) {
      if (compareIsSmaller(numbers[j], numbers[indexOfMinElement])) {
        indexOfMinElement = j;
      }
    }
    while (indexOfMinElement != i) {
      previusIndex = indexOfMinElement - 1;
      tmp = numbers[previusIndex];
      numbers[previusIndex] = numbers[indexOfMinElement];
      numbers[indexOfMinElement] = tmp;
      indexOfMinElement = previusIndex;
    }
  }
  for (i = 0; i < length; ++i) {
    std::cout << numbers[i] << (i == (length - 1) ? '\n' : ' ');
  }

  return 0;
}

int input() {
  int value;
  std::cin >> value;
  return value;
}

int mod3(const int n) { return n % 3; }

bool compareIsSmaller(const int compared, const int comparator) {
  const int comparedReminder = mod3(compared);
  return (comparedReminder < mod3(comparator)) && (comparedReminder > -1);
}