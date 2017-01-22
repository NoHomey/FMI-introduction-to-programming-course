#include <cstdio>
#include <new>

typedef unsigned char Byte;

const Byte BIT_SIZE_OF_BYTE = 8;

const int NO_WORD = -1;

class BooleanArray {
protected:
Byte* array;

public:
BooleanArray(const size_t count);

~BooleanArray();

bool get(const size_t index);

void set(const size_t index, const bool value);
};

void rotateWord(char* word, const size_t length, const size_t times);

bool isUpperCaseLetter(const char symbol);

bool isLowerCaseLetter(const char symbol);

bool isLetter(const char symbol);

bool isWordChar(const char prev, const char current, const char next);

int main() {
    char* text = nullptr;
    try {
        text = new char[10000];
    } catch(const std::bad_alloc& error) {
        throw error;
    }
    size_t read = 0;
    size_t rotates = 0;
    int wordBegin = NO_WORD;
    size_t wordEnd = 0;
    char prev = '\0';
    char current = '\0';
    char next = '\0';
    char symbol = std::getchar();
    while(symbol != '\n') {
        text[read] = symbol;
        ++read;
        symbol = std::getchar();
    }
    scanf("%lu", &rotates);
    for(size_t i = 0; i <= read; ++i) {
        prev = i > 0 ? text[i - 1] : '\0';
        current = text[i];
        next = i < read ? text[i + 1] : '\0';
        if((wordBegin < 0) && isLetter(current)) {
            wordBegin = i;
            wordEnd = 1;
            continue;
        }
        if((wordBegin >= 0)) {
            if(isWordChar(prev, current, next)) {
                ++wordEnd;   
            } else {
                rotateWord(text + wordBegin, wordEnd, rotates);
                wordBegin = NO_WORD;
            }
        }
    }
    for(size_t i = 0; i < read; ++i) {
        printf("%c", text[i]);
    }
    printf("\n");

    delete[] text;

    return 0;
}

BooleanArray::BooleanArray(const size_t count)
: array{nullptr} {
    const size_t size = (count / BIT_SIZE_OF_BYTE) + (((count % BIT_SIZE_OF_BYTE) > 0) ? 1 : 0);
    try {
        array = new Byte[size];
    } catch(const std::bad_alloc& error) {
        throw error;
    }
    for(size_t i = 0; i < size; ++i) {
        array[i] = 0;
    }
}

BooleanArray::~BooleanArray() {
    delete[] array;
}

bool BooleanArray::get(const size_t index) {
    return (array[index / BIT_SIZE_OF_BYTE]) & (1 << (index % BIT_SIZE_OF_BYTE)); 
}

void BooleanArray::set(const size_t index, const bool value) {
    const Byte mask = 1 << (index % BIT_SIZE_OF_BYTE);
    const size_t byteIndex = index / BIT_SIZE_OF_BYTE;
    if(value) {
        array[byteIndex] |= mask;
    } else {
        array[byteIndex] &= (~mask);
    }
}

void rotateWord(char* word, const size_t length, const size_t times) {
    const size_t rotateWith = times % length;
    BooleanArray visit = {length};
    size_t rotates = 0;
    size_t currentIndex = 0;
    size_t nextIndex = 0;
    char tmp = '\0';
    char moving = word[currentIndex];
    while(rotates < length) {
        visit.set(currentIndex, true);
        nextIndex = currentIndex + rotateWith;
        if(nextIndex >= length) {
            nextIndex -= length;
        }
        tmp = moving;
        moving = word[nextIndex];
        word[nextIndex] = tmp;
        ++rotates;
        if(visit.get(nextIndex)) {
            while(visit.get(++nextIndex));
            moving = word[nextIndex];
        }
        currentIndex = nextIndex;
    }
}

bool isUpperCaseLetter(const char symbol) {
    return (symbol >= 'A') && (symbol <= 'Z');
}

bool isLowerCaseLetter(const char symbol) {
    return (symbol >= 'a') && (symbol <= 'z');
}

bool isLetter(const char symbol) {
    return isUpperCaseLetter(symbol) || isLowerCaseLetter(symbol);
}

bool isWordChar(const char prev, const char current, const char next) {
    return isLetter(current) || ((current == '-') && isLetter(next) && isLetter(prev));
}