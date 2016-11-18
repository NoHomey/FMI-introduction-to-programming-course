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
using namespace std;

int main(void) {
  unsigned int sum = 0;
  unsigned int count = 0;
  cin >> sum;
  cout << sum << " =";
  if (sum >= 50) {
    count = sum / 50;
    cout << ' ' << count << '*' << 50;
    sum -= count * 50;
    if (sum > 0) {
      cout << " +";
    }
  }
  if (sum >= 20) {
    count = sum / 20;
    cout << ' ' << count << '*' << 20;
    sum -= count * 20;
    if (sum > 0) {
      cout << " +";
    }
  }
  if (sum >= 10) {
    count = sum / 10;
    cout << ' ' << count << '*' << 10;
    sum -= count * 10;
    if (sum > 0) {
      cout << " +";
    }
  }
  if (sum >= 5) {
    count = sum / 5;
    cout << ' ' << count << '*' << 5;
    sum -= count * 5;
    if (sum > 0) {
      cout << " +";
    }
  }
  if (sum >= 2) {
    count = sum / 2;
    cout << ' ' << count << '*' << 2;
    sum -= count * 2;
    if (sum > 0) {
      cout << " +";
    }
  }
  if (sum >= 1) {
    count = sum / 1;
    cout << ' ' << count << '*' << 1;
    sum -= count * 1;
    if (sum > 0) {
      cout << " +";
    }
  }
  cout << '\n';

  return 0;
}
