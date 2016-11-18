/**
*
* Solution to homework task
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2016/2017
*
* @author Ivo Stratev
* @idnumber 45342
* @task 10
* @compiler GCC
*
*/

#include <iostream>
using namespace std;

enum Solution { No, One, Many };

const float EPSILON = 0.00001;

int main() {
  float a1 = 0;
  float b1 = 0;
  float c1 = 0;
  float a2 = 0;
  float b2 = 0;
  float c2 = 0;
  float x = 0;
  float y = 0;
  Solution solution = Many;
  cin >> a1;
  cin >> b1;
  cin >> c1;
  cin >> a2;
  cin >> b2;
  cin >> c2;
  if (((!((a1 < EPSILON) && (a1 > -EPSILON))) ||
       (!((b1 < EPSILON) && (b1 > -EPSILON))) ||
       (!((c1 < EPSILON) && (c1 > -EPSILON)))) &&
      ((!((a2 < EPSILON) && (a2 > -EPSILON))) ||
       (!((b2 < EPSILON) && (b2 > -EPSILON))) ||
       (!((c2 < EPSILON) && (c2 > -EPSILON))))) {
    if (((a1 < EPSILON) && (a1 > -EPSILON)) && (solution == Many)) {
      if ((b1 < EPSILON) && (b1 > -EPSILON)) {
        solution = No;
      } else {
        y = c1 / b1;
        x = (c2 - (b2 * y)) / a2;
        solution = One;
      }
    }
    if (((a2 < EPSILON) && (a2 > -EPSILON)) && (solution == Many)) {
      if ((b2 < EPSILON) && (b2 > -EPSILON)) {
        solution = No;
      } else {
        y = c2 / b2;
        x = (c1 - (b1 * y)) / a1;
        solution = One;
      }
    }
    if (((b1 < EPSILON) && (b1 > -EPSILON)) && (solution == Many)) {
      if ((a1 < EPSILON) && (a1 > -EPSILON)) {
        solution = No;
      } else {
        x = c1 / a1;
        y = (c2 - (a2 * x)) / b2;
        solution = One;
      }
    }
    if (((b2 < EPSILON) && (b2 > -EPSILON)) && (solution == Many)) {
      if ((a2 < EPSILON) && (a2 > -EPSILON)) {
        solution = No;
      } else {
        x = c2 / a2;
        y = (c1 - (a1 * x)) / b1;
        solution = One;
      }
    }
    if (solution == Many) {
      const float k1 = (-a2) / a1;
      const float b3 = (b1 * k1) + b2;
      const float c3 = (c1 * k1) + c2;
      const float k2 = (-b1) / b2;
      const float a4 = (a2 * k2) + a1;
      const float c4 = (c2 * k2) + c1;
      if ((((b3 < EPSILON) && (b3 > -EPSILON)) &&
           (!((c3 < EPSILON) && (c3 > -EPSILON)))) ||
          (((a4 < EPSILON) && (a4 > -EPSILON)) &&
           (!((c4 < EPSILON) && (c4 > -EPSILON))))) {
        solution = No;
      } else {
        const float y1 = c3 / b3;
        const float x1 = (c1 - (b1 * y1)) / a1;
        const float x2 = c4 / a4;
        const float y2 = (c2 - (a2 * x2)) / b2;
        const float DIFF_X = x1 - x2;
        const float DIFF_Y = y1 - y2;
        if (((DIFF_X < EPSILON) && (DIFF_X > -EPSILON)) &&
            ((DIFF_Y < EPSILON) && (DIFF_Y > -EPSILON))) {
          x = x1;
          y = y1;
          solution = One;
        }
      }
    }
  }
  switch (solution) {
    case No:
      cout << "No solution";
      break;
    case Many:
      cout << "Many solutions";
      break;
    case One:
      int sign = 0;
      int wholePart = 0;
      int absWholePart = 0;
      int floatPart = 0;
      int multiplier = 0;
      sign = (x <= -EPSILON ? -1 : 1);
      wholePart = x + (sign * EPSILON);
      multiplier = 1;
      absWholePart = sign * wholePart;
      if ((absWholePart >= 0) && (absWholePart < 10)) {
        multiplier = 10000;
      }
      if ((absWholePart >= 10) && (absWholePart < 100)) {
        multiplier = 1000;
      }
      if ((absWholePart >= 100) && (absWholePart < 1000)) {
        multiplier = 100;
      }
      if ((absWholePart >= 1000) && (absWholePart < 10000)) {
        multiplier = 10;
      }
      floatPart =
          (int)((x + (sign * EPSILON)) * multiplier) - (wholePart * multiplier);
      x = ((float)floatPart / multiplier) + wholePart;
      sign = (y <= -EPSILON ? -1 : 1);
      wholePart = y + (sign * EPSILON);
      multiplier = 1;
      absWholePart = sign * wholePart;
      if ((absWholePart >= 0) && (absWholePart < 10)) {
        multiplier = 10000;
      }
      if ((absWholePart >= 10) && (absWholePart < 100)) {
        multiplier = 1000;
      }
      if ((absWholePart >= 100) && (absWholePart < 1000)) {
        multiplier = 100;
      }
      if ((absWholePart >= 1000) && (absWholePart < 10000)) {
        multiplier = 10;
      }
      floatPart =
          (int)((y + (sign * EPSILON)) * multiplier) - (wholePart * multiplier);
      y = ((float)floatPart / multiplier) + wholePart;
      cout << x << ' ' << y;
      break;
  }
  cout << '\n';

  return 0;
}
