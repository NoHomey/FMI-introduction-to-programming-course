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

#include <algorithm>
#include <iostream>
#include <vector>

typedef unsigned long long Number;
typedef std::vector<Number> Array;
typedef bool (*EveryNumberPredicate)(const Number, const Number);

template <typename T>
class Generator {
 protected:
  std::vector<T> generated;

  virtual T yield(const T previous) = 0;

 public:
  Generator() : generated{} {}

  Generator(std::initializer_list<T> list) : generated{list} {}

  virtual T next() = 0;

  T operator[](const size_t index) const { return generated[index]; }
};

class NumberGenerator : public Generator<Number> {
 public:
  NumberGenerator();

  NumberGenerator(std::initializer_list<Number> list);

  Number next();
};

class EveryNumber {
 protected:
  const Array& vector;
  const EveryNumberPredicate predicate;

  bool every(const Number test, Array::const_iterator iterator) const;

 public:
  EveryNumber(const Array& vector, const EveryNumberPredicate predicate);

  bool operator()(const Number test) const;
};

class PrimeNumberGenerator : public NumberGenerator {
 private:
  inline static bool isNotDivisible(const Number checked, const Number prime);

 protected:
  EveryNumber isPrime;

  Number yield(const Number previous) final;

 public:
  PrimeNumberGenerator();
};

class MultiplierSequnce {
 protected:
  class Multiplier {
   protected:
    Number result;

   public:
    Multiplier();

    void operator()(const Number n);

    Number product() const;
  };

  Array multipliers;

 public:
  MultiplierSequnce(const PrimeNumberGenerator& primes, const Number end,
                    const Number start = 2);

  void sort();

  Array::iterator begin();

  Array::iterator end();

  Number reduce(MultiplierSequnce&& divisor);
};

template <typename T>
inline void print(const T value);

void printWithSymbol(const Number num, const char symbol);

void printWithSpace(const Number num);

void printWithNewLine(const Number num);

int main() {
  Number n = 0;
  std::cin >> n;
  PrimeNumberGenerator primes = {};
  while (n > primes.next())
    ;
  printWithSpace(1);
  if (n > 1) {
    printWithSpace(n);
    for (Number k = 3; k < n; ++k) {
      printWithSpace(MultiplierSequnce(primes, n, k)
                         .reduce(MultiplierSequnce(primes, n - k + 1)));
    }
    if (n > 2) {
      printWithSpace(n);
    }
  }
  if (n > 0) {
    printWithNewLine(1);
  }

  return 0;
}

NumberGenerator::NumberGenerator() : Generator() {}

NumberGenerator::NumberGenerator(std::initializer_list<Number> list)
    : Generator(list) {}

Number NumberGenerator::next() {
  Number current = yield(generated.back());
  generated.push_back(current);
  return current;
}

bool EveryNumber::every(const Number test,
                        Array::const_iterator iterator) const {
  while (iterator != vector.end()) {
    if (!predicate(test, *(iterator++))) {
      return false;
    }
  }

  return true;
}

EveryNumber::EveryNumber(const Array& vector,
                         const EveryNumberPredicate predicate)
    : vector{vector}, predicate{predicate} {}

bool EveryNumber::operator()(const Number test) const {
  return every(test, vector.begin());
}

bool PrimeNumberGenerator::isNotDivisible(const Number checked,
                                          const Number prime) {
  return (checked % prime) != 0;
}

Number PrimeNumberGenerator::yield(const Number previous) {
  Number current = previous + 1;
  return isPrime(current) ? current : yield(current);
}

PrimeNumberGenerator::PrimeNumberGenerator()
    : NumberGenerator({2}), isPrime{generated, isNotDivisible} {}

MultiplierSequnce::Multiplier::Multiplier() : result{1} {}

void MultiplierSequnce::Multiplier::operator()(const Number n) { result *= n; }

Number MultiplierSequnce::Multiplier::product() const { return result; }

MultiplierSequnce::MultiplierSequnce(const PrimeNumberGenerator& primes,
                                     const Number end, const Number start)
    : multipliers{} {
  Number currentPrimeNumber = 0;
  Number multiplier = 0;
  Number prime = 2;
  for (Number n = start; n <= end; ++n) {
    multiplier = n;
    currentPrimeNumber = 0;
    while (multiplier != 1) {
      prime = primes[currentPrimeNumber];
      if ((multiplier % prime) == 0) {
        multipliers.push_back(prime);
        multiplier /= prime;
      } else {
        ++currentPrimeNumber;
      }
    }
  }
}

void MultiplierSequnce::sort() {
  std::sort(multipliers.begin(), multipliers.end());
}

Array::iterator MultiplierSequnce::begin() { return multipliers.begin(); }

Array::iterator MultiplierSequnce::end() { return multipliers.end(); }

Number MultiplierSequnce::reduce(MultiplierSequnce&& divisor) {
  Array intersection = Array();
  sort();
  divisor.sort();
  Array::iterator beginIterator = begin();
  Array::iterator endIterator = end();
  std::set_intersection(beginIterator, endIterator, divisor.begin(),
                        divisor.end(), std::back_inserter(intersection));
  Array::iterator differenceEnd =
      std::set_difference(beginIterator, endIterator, intersection.begin(),
                          intersection.end(), beginIterator);
  multipliers.erase(differenceEnd, endIterator);

  return (std::for_each(begin(), end(), Multiplier())).product();
}

template <typename T>
inline void print(const T value) {
  std::cout << value;
}

void printWithSymbol(const Number num, const char symbol) {
  print(num);
  print(symbol);
}

void printWithSpace(const Number num) { printWithSymbol(num, ' '); }

void printWithNewLine(const Number num) { printWithSymbol(num, '\n'); }