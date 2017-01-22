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

#include <cstdio>

typedef unsigned char Small;

const char FORMAT[] = "%hhu";

void sequence(const Small n);

int main() {
  Small n = 0;
  scanf(FORMAT, &n);
  sequence(n);
  printf("\n");

  return 0;
}

void sequence(const Small n) {
  const Small prev = n - 1;
  if (n > 0) {
    sequence(prev);
    printf(FORMAT, n);
    sequence(prev);
  }
}