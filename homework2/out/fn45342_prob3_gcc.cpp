/**
*
* Solution to homework task
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2016/2017
*
* @author Ivo Stratev
* @idnumber 45342
* @task 3
* @compiler GCC
*
*/

#include <cstdio>

typedef unsigned char Number;

const Number BEGINING = 0;
const Number MAX_DIGITS_COUNT = 10;

class Digits {
 protected:
  Number digits[MAX_DIGITS_COUNT];
  Number size;

  void pushDigit();

 public:
  Digits();

  Number operator[](const Number index) const;

  Number length() const;
};

int main() {
  const Digits digitsOfA = {};
  const Digits digitsOfB = {};
  const Number lengthOfDigitsOfA = digitsOfA.length();
  const Number lengthOfDigitsOfB = digitsOfB.length();
  Number count = BEGINING;
  if (lengthOfDigitsOfA <= lengthOfDigitsOfB) {
    const Number lastComparsionBegining = lengthOfDigitsOfB - lengthOfDigitsOfA;
    Number indexOfDigitsOfA = BEGINING;
    for (Number indexOfDigitsOfB = BEGINING;
         indexOfDigitsOfB <= lastComparsionBegining; ++indexOfDigitsOfB) {
      for (indexOfDigitsOfA = BEGINING; indexOfDigitsOfA < lengthOfDigitsOfA;
           ++indexOfDigitsOfA) {
        if (digitsOfB[indexOfDigitsOfB + indexOfDigitsOfA] !=
            digitsOfA[indexOfDigitsOfA]) {
          break;
        }
      }
      if (indexOfDigitsOfA == lengthOfDigitsOfA) {
        count++;
      }
    }
  }
  std::printf("%u\n", count);

  return 0;
}

void Digits::pushDigit() {
  char digit = std::getchar();
  if ((digit >= '0') && (digit <= '9')) {
    if ((digit != '0') || (size > 0)) {
      digits[size++] = digit - '0';
    }
    pushDigit();
  }
}

Digits::Digits() : digits{}, size{0} { pushDigit(); }

Number Digits::operator[](const Number index) const { return digits[index]; }

Number Digits::length() const { return size; }