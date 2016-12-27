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
#include <stdexcept>

typedef unsigned long long Number;

Number input();

struct Querry {
  Number p1;
  Number n;
  Number p2;

  Querry();

  Querry(Number (*source)());
} typedef Querry;

class P_AdicOrder {
 protected:
  inline static Number power(Number a, Number k);

  bool infinity;
  Number value;

 public:
  class InfinityP_AdicOrder : public std::logic_error {
   public:
    InfinityP_AdicOrder();
  };

  P_AdicOrder(Number p = 0, Number n = 0);

  bool isInfinity() const;

  Number getValue() const;

  bool operator>(const P_AdicOrder& other) const;
};

const P_AdicOrder& max(const P_AdicOrder& order1, const P_AdicOrder& order2);

std::ostream& operator<<(std::ostream& out, const P_AdicOrder& order);

int main() {
  const Number nq = input();
  Querry querry = {};
  for (Number i = 0; i < nq; ++i) {
    querry = {input};
    std::cout << max(P_AdicOrder(querry.p1, querry.n),
                     P_AdicOrder(querry.p2, querry.n))
              << '\n';
  }

  return 0;
}

Number input() {
  Number value;
  std::cin >> value;
  return value;
}

Querry::Querry() : p1{0}, n{0}, p2{0} {}

Querry::Querry(Number (*source)()) : p1{source()}, n{source()}, p2{source()} {}

Number P_AdicOrder::power(Number a, Number k) {
  return k == 0 ? 1 : (k == 1 ? a : a * power(a, k - 1));
}

P_AdicOrder::InfinityP_AdicOrder::InfinityP_AdicOrder()
    : std::logic_error("infinity") {}

P_AdicOrder::P_AdicOrder(Number p, Number n) : infinity{n == 0}, value{0} {
  if (!isInfinity()) {
    Number result = 1;
    for (Number v = value; result <= n; ++v) {
      result = power(p, v);
      if ((n % result) == 0) {
        value = v;
      }
    }
  }
}

bool P_AdicOrder::isInfinity() const { return infinity; }

Number P_AdicOrder::getValue() const {
  if (isInfinity()) {
    throw InfinityP_AdicOrder();
  }
  return value;
}

bool P_AdicOrder::operator>(const P_AdicOrder& other) const {
  if (isInfinity()) {
    return true;
  }
  if (other.isInfinity()) {
    return false;
  }

  return getValue() > other.getValue();
}

const P_AdicOrder& max(const P_AdicOrder& order1, const P_AdicOrder& order2) {
  return order1 > order2 ? order1 : order2;
}

std::ostream& operator<<(std::ostream& out, const P_AdicOrder& order) {
  try {
    out << order.getValue();
  } catch (P_AdicOrder::InfinityP_AdicOrder& error) {
    out << error.what();
  }

  return out;
}