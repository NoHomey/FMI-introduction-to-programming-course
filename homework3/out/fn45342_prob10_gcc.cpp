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

#include <cstdio>
#include <new>
#include <stdexcept>

typedef unsigned char Index;

const Index DIMENTION = 5;
const Index FIRST_INDEX = 0;
const char DISTANCE_FROM_UPPER_TO_LOWER_CASE = 'a' - 'A';

bool isUpperCaseLetter(const char symbol);

bool isLowerCaseLetter(const char symbol);

char toUpperCase(const char letter);

class EncodableString {
 private:
  static const Index ALOCATED_CHUNK_SIZE = 8;

 protected:
  size_t allocated_size;
  size_t size;
  char* string;

  void deleteString();

  void resize();

 public:
  EncodableString();

  ~EncodableString();
  size_t length() const;

  void append(const char symbol);

  void shrinkToFit();

  void set(const size_t index, const char letter);

  char get(const size_t index) const;

  const char* const operator*();
};

class EncodingTable {
 private:
  static const char COMMON_REPLACER = 'X';

 protected:
  class LetterPair {
   protected:
    char first;
    char second;

   public:
    LetterPair(const char firstLetter, const char secondLetter);

    char getFirst() const;

    char getSecond() const;

    bool isTwinLetterPair() const;
  };

  class PositionInEncodingTable {
   protected:
    Index row;
    Index column;

   public:
    PositionInEncodingTable(const Index r, const Index c);

    Index getRow() const;

    Index getColumn() const;

    bool isInSameRow(const PositionInEncodingTable& otherPosition) const;

    bool isInSameColumn(const PositionInEncodingTable& otherPosition) const;
  };

  Index row;
  Index column;
  char replacer;
  char notInTable;
  char table[DIMENTION][DIMENTION];

  bool isLetterInTable(const char letter) const;

  void findNotInTable();

  char replace(const char symbol);

  bool isReplacer(const char letter) const;

  bool isReplacerPair(const LetterPair& letterPair) const;

  PositionInEncodingTable positionInEncodingTable(const char letter) const;

  char nextLetterInRow(const PositionInEncodingTable& positionInTable) const;

  char nextLetterInColumn(const PositionInEncodingTable& positionInTable) const;

  char getLetterOfIntersection(
      const PositionInEncodingTable& rowInTable,
      const PositionInEncodingTable& columnInTable) const;

  LetterPair encodeLetterPair(const LetterPair&& letterPair) const;

 public:
  class InvalidEncodingTable : public std::logic_error {
   public:
    InvalidEncodingTable();
  };

  EncodingTable();

  void addLetterToTable(char letter);

  void encodeString(EncodableString* encodableString);
};

void readEncodingTable(EncodingTable* encodingTable);

void readTextToBeEncoded(EncodableString* encodableString);

int main() {
  EncodingTable encodingTable = {};
  EncodableString encodableString = {};
  const char* output = "";
  try {
    readEncodingTable(&encodingTable);
    readTextToBeEncoded(&encodableString);
    encodingTable.encodeString(&encodableString);
    output = *encodableString;
  } catch (EncodingTable::InvalidEncodingTable& error) {
    output = error.what();
  }
  printf("%s\n", output);

  return 0;
}

bool isUpperCaseLetter(const char symbol) {
  return (symbol >= 'A') && (symbol <= 'Z');
}

bool isLowerCaseLetter(const char symbol) {
  return (symbol >= 'a') && (symbol <= 'z');
}

char toUpperCase(const char letter) {
  return isLowerCaseLetter(letter)
             ? (letter - DISTANCE_FROM_UPPER_TO_LOWER_CASE)
             : letter;
}

void EncodableString::deleteString() { delete[] string; }

void EncodableString::resize() {
  char* resized = nullptr;
  try {
    resized = new char[allocated_size];
  } catch (const std::bad_alloc& error) {
    throw error;
  }
  for (size_t index = FIRST_INDEX; index < size; ++index) {
    resized[index] = string[index];
  }
  deleteString();
  string = resized;
}

EncodableString::EncodableString()
    : allocated_size{0}, size{0}, string{nullptr} {
  try {
    string = new char[ALOCATED_CHUNK_SIZE];
  } catch (const std::bad_alloc& error) {
    throw error;
  }
  allocated_size = ALOCATED_CHUNK_SIZE;
  string[FIRST_INDEX] = '\0';
}

EncodableString::~EncodableString() { deleteString(); }

size_t EncodableString::length() const { return size; }

void EncodableString::append(const char symbol) {
  if ((size + 1) == allocated_size) {
    allocated_size += ALOCATED_CHUNK_SIZE;
    resize();
  }
  string[size] = symbol;
  ++size;
  string[size] = '\0';
}

void EncodableString::shrinkToFit() {
  if (size < allocated_size) {
    allocated_size = size + 1;
    resize();
    string[size] = '\0';
  }
}

void EncodableString::set(const size_t index, const char letter) {
  string[index] = letter;
}

char EncodableString::get(const size_t index) const { return string[index]; }

const char* const EncodableString::operator*() { return string; }

EncodingTable::LetterPair::LetterPair(const char firstLetter,
                                      const char secondLetter)
    : first{firstLetter}, second{secondLetter} {}

char EncodingTable::LetterPair::getFirst() const { return first; }

char EncodingTable::LetterPair::getSecond() const { return second; }

bool EncodingTable::LetterPair::isTwinLetterPair() const {
  return first == second;
}

EncodingTable::PositionInEncodingTable::PositionInEncodingTable(const Index r,
                                                                const Index c)
    : row{r}, column{c} {}

Index EncodingTable::PositionInEncodingTable::getRow() const { return row; }

Index EncodingTable::PositionInEncodingTable::getColumn() const {
  return column;
}

bool EncodingTable::PositionInEncodingTable::isInSameRow(
    const PositionInEncodingTable& otherPosition) const {
  return row == otherPosition.row;
}

bool EncodingTable::PositionInEncodingTable::isInSameColumn(
    const PositionInEncodingTable& otherPosition) const {
  return column == otherPosition.column;
}

bool EncodingTable::isLetterInTable(const char letter) const {
  return positionInEncodingTable(letter).getColumn() < DIMENTION;
}

void EncodingTable::findNotInTable() {
  for (char letter = 'A'; letter <= 'Z'; ++letter) {
    if (!isLetterInTable(letter)) {
      notInTable = letter;
      break;
    }
  }
}

char EncodingTable::replace(const char symbol) {
  const char upperCased = toUpperCase(symbol);
  if (notInTable == '\0') {
    findNotInTable();
  }

  return (isUpperCaseLetter(upperCased) && (upperCased != notInTable))
             ? upperCased
             : replacer;
}

bool EncodingTable::isReplacer(const char letter) const {
  return letter == replacer;
}

bool EncodingTable::isReplacerPair(const LetterPair& letterPair) const {
  return isReplacer(letterPair.getFirst()) &&
         isReplacer(letterPair.getSecond());
}

EncodingTable::PositionInEncodingTable EncodingTable::positionInEncodingTable(
    const char letter) const {
  for (Index r = FIRST_INDEX; r < DIMENTION; ++r) {
    for (Index c = FIRST_INDEX; c < DIMENTION; ++c) {
      if (table[r][c] == letter) {
        return {r, c};
      }
    }
  }

  return {DIMENTION, DIMENTION};
}

char EncodingTable::nextLetterInRow(
    const PositionInEncodingTable& positionInTable) const {
  const Index column = positionInTable.getColumn();
  const Index columnOfNextLetterInRow =
      column == (DIMENTION - 1) ? FIRST_INDEX : (column + 1);

  return table[positionInTable.getRow()][columnOfNextLetterInRow];
}

char EncodingTable::nextLetterInColumn(
    const PositionInEncodingTable& positionInTable) const {
  const Index row = positionInTable.getRow();
  const Index rowOfNextLetterInColumn =
      row == (DIMENTION - 1) ? FIRST_INDEX : (row + 1);

  return table[rowOfNextLetterInColumn][positionInTable.getColumn()];
}

char EncodingTable::getLetterOfIntersection(
    const PositionInEncodingTable& rowInTable,
    const PositionInEncodingTable& columnInTable) const {
  return table[rowInTable.getRow()][columnInTable.getColumn()];
}

EncodingTable::LetterPair EncodingTable::encodeLetterPair(
    const LetterPair&& letterPair) const {
  if (isReplacerPair(letterPair)) {
    return letterPair;
  }
  if (letterPair.isTwinLetterPair()) {
    return encodeLetterPair({letterPair.getFirst(), replacer});
  }
  const PositionInEncodingTable positionOfFirst =
      positionInEncodingTable(letterPair.getFirst());
  const PositionInEncodingTable positionOfSecond =
      positionInEncodingTable(letterPair.getSecond());
  if (positionOfFirst.isInSameRow(positionOfSecond)) {
    return {nextLetterInRow(positionOfFirst),
            nextLetterInRow(positionOfSecond)};
  }
  if (positionOfFirst.isInSameColumn(positionOfSecond)) {
    return {nextLetterInColumn(positionOfFirst),
            nextLetterInColumn(positionOfSecond)};
  }

  return {getLetterOfIntersection(positionOfFirst, positionOfSecond),
          getLetterOfIntersection(positionOfSecond, positionOfFirst)};
}

EncodingTable::InvalidEncodingTable::InvalidEncodingTable()
    : std::logic_error("Bad table!") {}

EncodingTable::EncodingTable()
    : row{FIRST_INDEX},
      column{FIRST_INDEX},
      replacer{'Z'},
      notInTable{'\0'},
      table{} {}

void EncodingTable::addLetterToTable(char letter) {
  for (Index r = FIRST_INDEX; r < row; ++r) {
    for (Index c = FIRST_INDEX; c < column; ++c) {
      if (table[r][c] == letter) {
        throw InvalidEncodingTable();
      }
    }
  }
  if (row == DIMENTION) {
    throw InvalidEncodingTable();
  }
  if (letter == COMMON_REPLACER) {
    replacer = COMMON_REPLACER;
  }
  table[row][column] = letter;
  ++column;
  if (column == DIMENTION) {
    ++row;
    column = FIRST_INDEX;
  }
}

void EncodingTable::encodeString(EncodableString* encodableString) {
  if ((encodableString->length() % 2) == 1) {
    encodableString->append(replacer);
  }
  encodableString->shrinkToFit();
  const size_t length = encodableString->length();
  char first = '\0';
  char second = '\0';
  for (size_t index = FIRST_INDEX; index < length; index += 2) {
    const size_t secondIndex = index + 1;
    first = replace(encodableString->get(index));
    second = replace(encodableString->get(secondIndex));
    const LetterPair letterPair = encodeLetterPair({first, second});
    encodableString->set(index, letterPair.getFirst());
    encodableString->set(secondIndex, letterPair.getSecond());
  }
}

void readEncodingTable(EncodingTable* encodingTable) {
  char symbol = std::getchar();
  Index readLines = FIRST_INDEX;
  while (true) {
    if (isUpperCaseLetter(symbol)) {
      encodingTable->addLetterToTable(symbol);
    } else if (symbol == '\n') {
      ++readLines;
      if (readLines == DIMENTION) {
        break;
      }
    }
    symbol = std::getchar();
  }
}

void readTextToBeEncoded(EncodableString* encodableString) {
  char symbol = std::getchar();
  while (symbol != '\n') {
    encodableString->append(symbol);
    symbol = std::getchar();
  }
}