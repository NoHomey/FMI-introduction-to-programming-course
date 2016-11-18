/**
*
* Solution to homework task
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2016/2017
*
* @author Ivo Stratev
* @idnumber 45342
* @task 4
* @compiler GCC
*
*/

#include <iostream>
using namespace std;

typedef short number;

enum Figure { Queen = 'Q', Bishop = 'B', Knight = 'N', Rook = 'R' };

int main(void) {
  char figure = '\0';
  char figureX = '\0';
  number figureY = 0;
  char kingX = '\0';
  number kingY = 0;
  bool check = false;
  cin >> figure;
  cin >> figureX;
  cin >> figureY;
  cin >> kingX;
  cin >> kingY;
  const number figureXN = 1 + (figureX - 'a');
  const number kingXN = 1 + (kingX - 'a');
  const number DIFF_X = kingXN - figureXN;
  const number DIFF_Y = kingY - figureY;
  switch (figure) {
    case Queen:
    case Bishop:
      check =
          (DIFF_X < 0 ? -DIFF_X : DIFF_X) == (DIFF_Y < 0 ? -DIFF_Y : DIFF_Y);
      if (figure == Bishop) {
        break;
      }
    case Rook:
      if (!check) {
        check = (kingXN == figureXN) || (kingY == figureY);
      }
      break;
    case Knight:
      if (((figureXN + 1) == kingXN) || ((figureXN - 1) == kingXN)) {
        check = ((figureY + 2) == kingY) || ((figureY - 2) == kingY);
      }
      if (((figureXN + 2) == kingXN) || ((figureXN - 2) == kingXN)) {
        check = ((figureY + 1) == kingY) || ((figureY - 1) == kingY);
      }
  }
  cout << (check ? "Yes" : "No") << '\n';

  return 0;
}
