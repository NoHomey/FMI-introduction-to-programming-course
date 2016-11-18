/**
*
* Solution to homework task
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2016/2017
*
* @author Ivo Stratev
* @idnumber 45342
* @task 1
* @compiler GCC
*
*/

#include <iostream>
using namespace std;

typedef unsigned short number;

const number MAX_INPUT_VALUE = 3000;
const number ONE_DIGIT = 10;

int main(void) {
  number inputNumber = 0;
  number thousands = 0;
  number hundreds = 0;
  number tens = 0;
  number ones = 0;
  cin >> inputNumber;
  if ((inputNumber > MAX_INPUT_VALUE) || (inputNumber == 0)) {
    cout << "Invalid number!";
  } else {
    ones = inputNumber % ONE_DIGIT;
    inputNumber /= ONE_DIGIT;
    tens = inputNumber % ONE_DIGIT;
    inputNumber /= ONE_DIGIT;
    hundreds = inputNumber % ONE_DIGIT;
    inputNumber /= ONE_DIGIT;
    thousands = inputNumber % ONE_DIGIT;
    inputNumber /= ONE_DIGIT;
    switch (thousands) {
      case 3:
        cout << 'M';
      case 2:
        cout << 'M';
      case 1:
        cout << 'M';
    }
    switch (hundreds) {
      case 8:
      case 7:
      case 6:
      case 5:
        cout << 'D';
        if (hundreds == 5) {
          break;
        }
      case 4:
      case 3:
        cout << 'C';
        if (hundreds == 6) {
          break;
        }
        if (hundreds == 4) {
          cout << 'D';
          break;
        }
      case 2:
        cout << 'C';
        if (hundreds == 7) {
          break;
        }
      case 9:
      case 1:
        cout << 'C';
        if (hundreds == 9) {
          cout << 'M';
        }
    }
    switch (tens) {
      case 8:
      case 7:
      case 6:
      case 5:
        cout << 'L';
        if (tens == 5) {
          break;
        }
      case 4:
      case 3:
        cout << 'X';
        if (tens == 6) {
          break;
        }
        if (tens == 4) {
          cout << 'L';
          break;
        }
      case 2:
        cout << 'X';
        if (tens == 7) {
          break;
        }
      case 9:
      case 1:
        cout << 'X';
        if (tens == 9) {
          cout << 'C';
        }
    }
    switch (ones) {
      case 8:
      case 7:
      case 6:
      case 5:
        cout << 'V';
        if (ones == 5) {
          break;
        }
      case 4:
      case 3:
        cout << 'I';
        if (ones == 6) {
          break;
        }
        if (ones == 4) {
          cout << 'V';
          break;
        }
      case 2:
        cout << 'I';
        if (ones == 7) {
          break;
        }
      case 9:
      case 1:
        cout << 'I';
        if (ones == 9) {
          cout << 'X';
        }
    }
  }
  cout << '\n';

  return 0;
}
