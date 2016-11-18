/**
*
* Solution to homework task
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2016/2017
*
* @author Ivo Stratev
* @idnumber 45342
* @task 9
* @compiler GCC
*
*/

#include <iostream>
using namespace std;

typedef unsigned short number;

const number MAX_4BIT_VALUE = 15;

int main(void) {
  number leftOperand = 0;
  number rightOperand = 0;
  number result = 0;
  char operation = '\0';
  bool divisionAllowed = true;
  cin >> leftOperand;
  cin >> operation;
  cin >> rightOperand;
  leftOperand &= MAX_4BIT_VALUE;
  rightOperand &= MAX_4BIT_VALUE;
  switch (operation) {
    case '+':
      result = leftOperand + rightOperand;
      break;
    case '-':
      result = leftOperand - rightOperand;
      break;
    case '*':
      result = leftOperand * rightOperand;
      break;
    case '/':
    case '%':
      divisionAllowed = rightOperand != 0;
      if (divisionAllowed) {
        result = operation == '/' ? (leftOperand / rightOperand)
                                  : (leftOperand % rightOperand);
      }
  }
  if (divisionAllowed) {
    cout << (result & MAX_4BIT_VALUE);
  } else {
    cout << "Division by zero!";
  }
  cout << '\n';

  return 0;
}
