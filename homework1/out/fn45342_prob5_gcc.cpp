/**
*
* Solution to homework task
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2016/2017
*
* @author Ivo Stratev
* @idnumber 45342
* @task 5
* @compiler GCC
*
*/

#include <iostream>
using namespace std;

const float EPSILON = 0.001;
const float SQUARE_OF_R1 = (8 * 8);
const float SQUARE_OF_R2 = (3 * 3);
const float SQUARE_OF_R3 = (1 * 1);

int main() {
  float x = 0;
  float y = 0;
  float u = 0;
  float v = 0;
  cin >> x;
  cin >> y;
  cin >> u;
  cin >> v;
  const float X = x + u;
  const float Y = y + v;
  const float SQUARE_OF_DISTANCE = (X * X) + (Y * Y);
  float score = 0;
  if (SQUARE_OF_DISTANCE <= (SQUARE_OF_R3 - EPSILON)) {
    score = 60;
  }
  if ((SQUARE_OF_DISTANCE >= (SQUARE_OF_R3 + EPSILON)) &&
      (SQUARE_OF_DISTANCE <= (SQUARE_OF_R2 - EPSILON))) {
    score = 20;
  }
  if ((SQUARE_OF_DISTANCE >= (SQUARE_OF_R2 + EPSILON)) &&
      (SQUARE_OF_DISTANCE <= (SQUARE_OF_R1 - EPSILON))) {
    score = 10;
  }
  cout << score << '\n';

  return 0;
}
