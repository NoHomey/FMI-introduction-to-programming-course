/**
*
* Solution to homework task
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2016/2017
*
* @author Ivo Stratev
* @idnumber 45342
* @task 2
* @compiler GCC
*
*/

#include <iostream>
using namespace std;

typedef unsigned short number;

enum ChechsumWeights {
  SequenceNNNWeight = 6,
  SequenceNNWeight = 3,
  SequenceNWeight = 7,
  DayDDWeight = 9,
  DayDWeight = 10,
  MonthMMWeight = 5,
  MonthMWeight = 8,
  YearYYWeight = 4,
  YearYWeight = 2
};

const number ONE_DIGIT = 10;
const number THREE_DIGITS = 1000;
const number TWO_DIGITS = 100;
const char DOT = '.';
const char SPACE = ' ';

int main() {
  number day = 0;
  number month = 0;
  number year = 0;
  number birthSequence = 0;
  number controlDigit = 0;
  char sex = 'M';
  unsigned long egn = 0;
  bool invalid = false;
  cin >> egn;
  controlDigit = egn % ONE_DIGIT;
  egn /= ONE_DIGIT;
  birthSequence = egn % THREE_DIGITS;
  egn /= THREE_DIGITS;
  day = egn % TWO_DIGITS;
  egn /= TWO_DIGITS;
  month = egn % TWO_DIGITS;
  egn /= TWO_DIGITS;
  year = egn % TWO_DIGITS;
  egn /= TWO_DIGITS;
  number dayCopy = day;
  number monthCopy = month;
  number normalizatedMonth = month;
  number fullYear = year;
  if (month > 40) {
    normalizatedMonth -= 40;
    fullYear += 2000;
  } else if (month > 20) {
    normalizatedMonth -= 20;
    fullYear += 1800;
  } else {
    fullYear += 1900;
  }
  invalid = (normalizatedMonth == 0) || (normalizatedMonth > 12);
  if (!invalid) {
    invalid = day == 0;
    if (!invalid) {
      unsigned short limit = 31;
      switch (normalizatedMonth) {
        case 4:
        case 6:
        case 9:
        case 11:
          limit = 30;
          break;
        case 2:
          limit = (((year % 4) == 0) && ((fullYear % 100) == 0) &&
                   ((fullYear % 400) == 0))
                      ? 29
                      : 28;
      }
      invalid = day > limit;
    }
  }
  if (!invalid) {
    number checksum = 0;
    if (!(((birthSequence % ONE_DIGIT) % 2) == 0)) {
      sex = 'F';
    }
    checksum += (birthSequence % ONE_DIGIT) * SequenceNNNWeight;
    birthSequence /= ONE_DIGIT;
    checksum += (birthSequence % ONE_DIGIT) * SequenceNNWeight;
    birthSequence /= ONE_DIGIT;
    checksum += (birthSequence % ONE_DIGIT) * SequenceNWeight;
    birthSequence /= ONE_DIGIT;
    checksum += (dayCopy % ONE_DIGIT) * DayDDWeight;
    dayCopy /= ONE_DIGIT;
    checksum += (dayCopy % ONE_DIGIT) * DayDWeight;
    dayCopy /= ONE_DIGIT;
    checksum += (monthCopy % ONE_DIGIT) * MonthMMWeight;
    monthCopy /= ONE_DIGIT;
    checksum += (monthCopy % ONE_DIGIT) * MonthMWeight;
    monthCopy /= ONE_DIGIT;
    checksum += (year % ONE_DIGIT) * YearYYWeight;
    year /= ONE_DIGIT;
    checksum += (year % ONE_DIGIT) * YearYWeight;
    year /= ONE_DIGIT;
    checksum %= 11;
    if (checksum > 9) {
      checksum = 0;
    }
    invalid = checksum != controlDigit;
  }
  if (!invalid) {
    if (day < 10) {
      cout << 0 << day;
    } else {
      cout << day;
    }
    cout << DOT;
    if (normalizatedMonth < 10) {
      cout << 0 << normalizatedMonth;
    } else {
      cout << normalizatedMonth;
    }
    cout << DOT << fullYear << SPACE << sex;
  } else {
    cout << "Bad input data!";
  }
  cout << '\n';

  return 0;
}
