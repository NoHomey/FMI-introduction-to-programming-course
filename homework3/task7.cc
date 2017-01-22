#include <cstdio>
#include <new>

const char DISTANCE_FROM_UPPER_TO_LOWER_CASE = 'a' - 'A';

class String {
private:
static const size_t ALOCATED_CHUNK_SIZE = 8;

protected:
size_t allocated_size;
size_t size;
char* string;

void deleteString();

void resize();

public:
String();

~String();

size_t length() const;

void append(const char symbol);

char operator[](const size_t index);

void clear();
};

bool isUpperCaseLetter(const char symbol);

bool isLowerCaseLetter(const char symbol);

bool isLetter(const char symbol);

char toLowerCase(const char letter);

char toUpperCase(const char letter);

bool isStrictVowelLetter(const char letter);

bool isStrictConsonantLetter(const char letter);

int main() {
    char symbol = '\0';
    char nextSymbol = '\0';
    bool isWord = false;
    bool isVowel = false;
    bool isLetterSymbol = false;
    bool isUpperCase = false;
    bool isNextLowerCase = false;
    bool isConsonant = false;
    bool areAllUpperCase = false;
    size_t counter = 0;
    String buffer = {};
    while(symbol != '\n') {
        symbol = std::getchar();
        isLetterSymbol = isLetter(symbol);
        if(isLetterSymbol && (!isWord)) {
            isWord = true;
            areAllUpperCase = true;
            counter = 0;
            isVowel = isStrictVowelLetter(symbol);
            if(!isVowel) {
                isUpperCase = isUpperCaseLetter(symbol);
                nextSymbol = std::getchar();
                if(isLetter(nextSymbol)) {
                    isNextLowerCase = isLowerCaseLetter(nextSymbol);
                    isConsonant = isStrictConsonantLetter(nextSymbol);
                    buffer.clear();
                    buffer.append(isNextLowerCase ? toLowerCase(symbol) : symbol);
                    while(isConsonant) {
                        buffer.append(nextSymbol);
                        nextSymbol = std::getchar();
                        isConsonant = isStrictConsonantLetter(nextSymbol);
                    }
                    isLetterSymbol = isLetter(nextSymbol);
                    symbol = (isNextLowerCase && isUpperCase)
                        ? toUpperCase(nextSymbol)
                        : nextSymbol;
                }
            }
        }
        if(isWord && (!isLetterSymbol)) {
            if(isVowel) {
                std::printf("%c", ((areAllUpperCase && (counter > 1)) ? 'W' : 'w'));
            } else {
                size_t index = 0;
                char bufferChar = '\0';
                while(true) {
                    bufferChar = buffer[index++];
                    if(bufferChar == '\0') {
                        break;
                    }
                    areAllUpperCase &= isUpperCaseLetter(bufferChar);
                    ++counter;
                    std::printf("%c", bufferChar);
                }
            }
            std::printf(((areAllUpperCase && (counter > 1))) ? "AY" : "ay");
            isWord = false;
            areAllUpperCase = false;
        }
        areAllUpperCase &= isUpperCaseLetter(symbol);
        ++counter;
        std::printf("%c", symbol);
    }

    return 0;
}

void String::deleteString() {
    delete[] string;
}

void String::resize() {
    char* resized = nullptr;
    try {
        resized = new char[allocated_size];
    } catch(const std::bad_alloc& error) {
        throw error;
    }
    for(size_t index = 0; index < size; ++index) {
        resized[index] = string[index];
    }
    deleteString();
    string = resized;
}

String::String()
: allocated_size{0}, size{0}, string{nullptr} {
    clear(); 
}

String::~String() {
    deleteString();
}

size_t String::length() const {
    return size;
}

void String::append(const char symbol) {
    if((size + 1) == allocated_size) {
        allocated_size += ALOCATED_CHUNK_SIZE;
        resize();
    }
    string[size] = symbol;
    ++size;
    string[size] = '\0';
}

char String::operator[](const size_t index) {
    return string[index];
}

void String::clear() {
    deleteString();
    try {
        string = new char[ALOCATED_CHUNK_SIZE];
    } catch(const std::bad_alloc& error) {
        throw error;
    }
    string[0] = '\0';
    size = 0;
    allocated_size = ALOCATED_CHUNK_SIZE;
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

char toLowerCase(const char letter) {
    return isUpperCaseLetter(letter)
        ? (letter + DISTANCE_FROM_UPPER_TO_LOWER_CASE)
        : letter;
}

char toUpperCase(const char letter) {
    return isLowerCaseLetter(letter)
        ? (letter - DISTANCE_FROM_UPPER_TO_LOWER_CASE)
        : letter;
}

bool isStrictVowelLetter(const char letter) {
    switch(toLowerCase(letter)) {
        case 'a':
        case 'e':
        case 'o':
        case 'u':
        case 'i':
        case 'y':
            return true;
    }

    return false;
}

bool isStrictConsonantLetter(const char letter) {
    return isLetter(letter) && (!isStrictVowelLetter(letter));
}