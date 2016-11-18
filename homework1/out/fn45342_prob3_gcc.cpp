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

#include <iostream>
using namespace std;

typedef unsigned long long number;

const number HEX_F = 15;
const number HEX_DIGIT = 4;

int main() {
  number inputNumber = 0;
  number digits = 0;
  cin >> inputNumber;
  number first4Bits = inputNumber & HEX_F;
  if ((inputNumber & (HEX_F << 4)) != 0) {
    digits = 4;
  }
  if ((inputNumber & (HEX_F << 8)) != 0) {
    digits = 8;
  }
  if ((inputNumber & (HEX_F << 12)) != 0) {
    digits = 12;
  }
  if ((inputNumber & (HEX_F << 16)) != 0) {
    digits = 16;
  }
  if ((inputNumber & (HEX_F << 20)) != 0) {
    digits = 20;
  }
  if ((inputNumber & (HEX_F << 24)) != 0) {
    digits = 24;
  }
  if ((inputNumber & (HEX_F << 28)) != 0) {
    digits = 28;
  }
  if ((inputNumber & (HEX_F << 32)) != 0) {
    digits = 32;
  }
  if ((inputNumber & (HEX_F << 36)) != 0) {
    digits = 36;
  }
  if ((inputNumber & (HEX_F << 40)) != 0) {
    digits = 40;
  }
  if ((inputNumber & (HEX_F << 44)) != 0) {
    digits = 44;
  }
  if ((inputNumber & (HEX_F << 48)) != 0) {
    digits = 48;
  }
  if ((inputNumber & (HEX_F << 52)) != 0) {
    digits = 52;
  }
  if ((inputNumber & (HEX_F << 56)) != 0) {
    digits = 56;
  }
  if ((inputNumber & (HEX_F << 60)) != 0) {
    digits = 60;
  }
  cout << (((inputNumber >> HEX_DIGIT) | (first4Bits << digits)) == inputNumber
               ? "Yes"
               : "No")
       << '\n';

  return 0;
}
