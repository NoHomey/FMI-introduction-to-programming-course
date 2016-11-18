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
using namespace std;

const float R2 = 3;
const float SQUARE_OF_R1 = (1 * 1);
const float SQUARE_OF_R2 = (R2 * R2);
const float SQUARE_OF_R3 = (6 * 6);

enum YinYang { Good, Evil, Neutral };

int main() {
  float x = 0;
  float y = 0;
  float y1 = 0;
  float SQUARE_OF_DISTANCE = 0;
  YinYang point = Neutral;
  cin >> x;
  cin >> y;
  const float SQUARE_OF_X = (x * x);
  y1 = y - R2;
  SQUARE_OF_DISTANCE = SQUARE_OF_X + (y1 * y1);
  if ((SQUARE_OF_X + (y * y)) < SQUARE_OF_R3) {
    if (y > 0) {
      if (SQUARE_OF_DISTANCE < SQUARE_OF_R1) {
        point = Evil;
      }
      if (x > 0) {
        if ((SQUARE_OF_DISTANCE > SQUARE_OF_R1) &&
            (SQUARE_OF_DISTANCE < SQUARE_OF_R2)) {
          point = Good;
        } else if (SQUARE_OF_DISTANCE > SQUARE_OF_R2) {
          point = Evil;
        }
      } else if (SQUARE_OF_DISTANCE > SQUARE_OF_R1) {
        point = Good;
      }
    } else {
      y1 = y + R2;
      SQUARE_OF_DISTANCE = SQUARE_OF_X + (y1 * y1);
      if (SQUARE_OF_DISTANCE < SQUARE_OF_R1) {
        point = Good;
      }
      if (x > 0) {
        if (SQUARE_OF_DISTANCE > SQUARE_OF_R1) {
          point = Evil;
        }
      } else {
        if ((SQUARE_OF_DISTANCE > SQUARE_OF_R1) &&
            (SQUARE_OF_DISTANCE < SQUARE_OF_R2)) {
          point = Evil;
        } else if (SQUARE_OF_DISTANCE > SQUARE_OF_R2) {
          point = Good;
        }
      }
    }
  }
  switch (point) {
    case Good:
      cout << "Good";
      break;
    case Evil:
      cout << "Evil";
      break;
    case Neutral:
      cout << "Neutral";
      break;
  }
  cout << '\n';

  return 0;
}
