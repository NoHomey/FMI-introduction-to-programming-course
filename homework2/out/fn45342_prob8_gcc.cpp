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
#include <stdexcept>

typedef unsigned long Number;

Number input();

class BadInputData : public std::out_of_range {
 public:
  BadInputData();
};

void kBasedAdder(const Number a, const Number b, const Number k,
                 const Number addition = 0);

int main() {
  const Number n = input();
  const Number m = input();
  const Number k = input();
  try {
    kBasedAdder(n, m, k);
  } catch (BadInputData& error) {
    std::cout << error.what();
  }
  std::cout << '\n';

  return 0;
}

Number input() {
  Number value;
  std::cin >> value;
  return value;
}

BadInputData::BadInputData() : std::out_of_range("Bad input data!") {}

void kBasedAdder(const Number a, const Number b, const Number k,
                 const Number addition) {
  const Number lastDigitOfA = a % 10;
  const Number lastDigitOfB = b % 10;
  Number result = lastDigitOfA + lastDigitOfB + addition;
  Number nextAddition = 0;
  if ((lastDigitOfA >= k) || (lastDigitOfB >= k)) {
    throw BadInputData();
  }
  if ((a > 0) || (b > 0) || (result > 0)) {
    if (result >= k) {
      nextAddition = 1;
      result -= k;
    }
    kBasedAdder(a / 10, b / 10, k, nextAddition);
    std::cout << result;
  }
}