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
#include <new>

template <typename K, typename V>
class Map;

typedef Map<unsigned short, float> Tasks;
typedef Map<unsigned int, Tasks> Students;

template <typename K, typename V>
class Map {
 protected:
  struct MapEntry {
    K key;
    V value;
  };

  size_t size;
  MapEntry* entries;

 public:
  class KeyNotFoundInMap {};

  Map();

  Map(const MapEntry& entry);

  void set(const K& key, const V& val);

  V& get(const K& key) const;

  template <typename T>
  void forEach(T functional) const;
};

class Outputer {
 protected:
  unsigned int student;

 public:
  Outputer(const unsigned int& fn);

  void operator()(const unsigned short& task, const float& score) const;
};

template <typename T>
T input();

void output(const unsigned int& student, const Tasks& tasks);

int main() {
  Students students = {};
  const size_t count = input<size_t>();
  unsigned int student = 0;
  unsigned short task = 0;
  float score = 0;
  for (size_t i = 0; i < count; ++i) {
    student = input<unsigned int>();
    task = input<unsigned short>();
    score = input<float>();
    try {
      students.get(student).set(task, score);
    } catch (const Students::KeyNotFoundInMap& error) {
      students.set(student, {{task, score}});
    }
  }
  students.forEach(output);

  return 0;
}

template <typename K, typename V>
Map<K, V>::Map() : size{0}, entries{nullptr} {}

template <typename K, typename V>
Map<K, V>::Map(const MapEntry& entry) : size{0}, entries{nullptr} {
  try {
    entries = new MapEntry[1];
  } catch (const std::bad_alloc& error) {
    throw error;
  }
  entries[0] = entry;
  size = 1;
}

template <typename K, typename V>
void Map<K, V>::set(const K& key, const V& val) {
  MapEntry* setted = nullptr;
  try {
    setted = new MapEntry[size + 1];
  } catch (const std::bad_alloc& error) {
    throw error;
  }
  size_t index = 0;
  size_t minIndex = 0;
  const size_t oldSize = size;
  for (; index < size; ++index) {
    setted[index] = entries[index];
  }
  setted[size++] = {key, val};
  delete[] entries;
  entries = setted;
  for (index = 0; index < oldSize; ++index) {
    minIndex = index;
    for (size_t index2 = index; index2 < size; ++index2) {
      if (entries[index2].key < entries[minIndex].key) {
        minIndex = index2;
      }
    }
    if (minIndex != index) {
      MapEntry tmp = entries[index];
      entries[index] = entries[minIndex];
      entries[minIndex] = tmp;
    }
  }
}

template <typename K, typename V>
V& Map<K, V>::get(const K& key) const {
  if (size > 0) {
    size_t lowerBound = 0;
    size_t upperBound = size - 1;
    size_t middle = 0;
    while (lowerBound <= upperBound) {
      middle = (lowerBound + upperBound) / 2;
      K middleKey = entries[middle].key;
      if (middleKey == key) {
        return entries[middle].value;
      } else {
        if (middleKey > key) {
          if (middle == 0) {
            break;
          }
          upperBound = middle - 1;
        } else {
          lowerBound = middle + 1;
        }
      }
    }
  }

  throw KeyNotFoundInMap{};
}

template <typename K, typename V>
template <typename T>
void Map<K, V>::forEach(T functor) const {
  for (size_t index = 0; index < size; ++index) {
    MapEntry entry = entries[index];
    functor(entry.key, entry.value);
  }
}

Outputer::Outputer(const unsigned int& fn) : student{fn} {}

void Outputer::operator()(const unsigned short& task,
                          const float& score) const {
  std::cout << student << ' ' << task << ' ' << score << '\n';
}

template <typename T>
T input() {
  T value;
  std::cin >> value;
  return value;
}

void output(const unsigned int& student, const Tasks& tasks) {
  Outputer outputer = {student};
  tasks.forEach(outputer);
}