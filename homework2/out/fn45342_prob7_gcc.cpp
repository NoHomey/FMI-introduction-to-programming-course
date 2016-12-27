/**
*
* Solution to homework task
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2016/2017
*
* @author Ivo Stratev
* @idnumber 45342
* @task 7
* @compiler GCC
*
*/

#include <iostream>

#define SETUP_MODULAR_POWER()    \
  Number exponentCounter = 0;    \
  Number modularPowerResult = 0; \
  Number prevModularPowerResult = 0

#define MODULAR_POWER(base, exponent, modulus)                  \
  exponentCounter = exponent;                                   \
  modularPowerResult = 1;                                       \
  while (exponentCounter > 0) {                                 \
    prevModularPowerResult = modularPowerResult;                \
    modularPowerResult = (modularPowerResult * base) % modulus; \
    if ((modularPowerResult == 0) ||                            \
        (prevModularPowerResult == modularPowerResult)) {       \
      break;                                                    \
    }                                                           \
    --exponentCounter;                                          \
  }

#define IS_MODULAR_POWER_RESULT(value) modularPowerResult == value

typedef unsigned long long Number;

Number input();

template <typename T>
inline void print(const T value);

int main() {
  const Number n = input();
  const Number m = input();
  const Number y = input();
  bool foundNumber = false;
  SETUP_MODULAR_POWER();
  for (Number x = 1; x < m; ++x) {
    MODULAR_POWER(x, n, m);
    if (IS_MODULAR_POWER_RESULT(y)) {
      if (foundNumber) {
        print(' ');
      } else {
        foundNumber = true;
      }
      print(x);
    }
  }
  if (!foundNumber) {
    print(-1);
  }
  print('\n');

  return 0;
}

Number input() {
  Number value;
  std::cin >> value;
  return value;
}

template <typename T>
void print(const T value) {
  std::cout << value;
}