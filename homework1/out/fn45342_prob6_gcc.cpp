/**
*
* Solution to homework task
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2016/2017
*
* @author Ivo Stratev
* @idnumber 45342
* @task 6
* @compiler GCC
*
*/

#include <iostream>
using namespace std;

int main(void) {
  int x11 = 0;
  int y11 = 0;
  int height1 = 0;
  int width1 = 0;
  int x21 = 0;
  int y21 = 0;
  int height2 = 0;
  int width2 = 0;
  cin >> x11;
  cin >> y11;
  cin >> height1;
  cin >> width1;
  cin >> x21;
  cin >> y21;
  cin >> height2;
  cin >> width2;
  /**
  * The formula for calculating the area of intersection between two rectangles
  * is taken from the accepted answer of the question: "Calculate overlapped
  * area between two rectangles".
  * Asked by Eric Bal <http://stackoverflow.com/users/4230794/eric-bal>,
  * at stackoverflow <http://stackoverflow.com/>.
  * Question reference:
  * <http://stackoverflow.com/questions/27152904/calculate-overlapped-area-between-two-rectangles>.
  * Author of the accpeted answer is: tom10
  * <http://stackoverflow.com/users/102302/tom10>.
  */
  const int x12 = x11 + width1;
  const int x22 = x21 + width2;
  const int width = (x12 < x22 ? x12 : x22) - (x11 > x21 ? x11 : x21);
  const int y12 = y11 + height1;
  const int y22 = y21 + height2;
  const int height = (y12 < y22 ? y12 : y22) - (y11 > y21 ? y11 : y21);
  cout << (((width > 0) && (height > 0)) ? (width * height) : 0) << '\n';

  return 0;
}
