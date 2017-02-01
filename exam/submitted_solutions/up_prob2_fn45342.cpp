#include <iostream>

bool isLowerCaseLetter(const char symbol) {
    return (symbol >= 'a') && (symbol <= 'z');
}

bool isUpperCaseLetter(const char symbol) {
    return (symbol >= 'A') && (symbol <= 'Z');
}

bool isLetter(const char symbol) {
    return isLowerCaseLetter(symbol) || isUpperCaseLetter(symbol);
}

bool wordIsFound(char** words, size_t wordsCount, char* word, size_t length) {
    if(wordsCount == 0) {
        return false;
    }
    for(size_t i = 0; i < wordsCount; ++i) {
        for(size_t j = 0; words[i][j] != '\0'; ++j) {
            if(j == length) {
                return false;
            }
            if(words[i][j] != word[j]) {
                return false;
            }
        }
    }

    return true;
}

size_t strLength(char* str) {
    size_t i = 0;
    while(str[i] != '\0') {
        ++i;
    }

    return i;
}

char** addToWords(char** words, size_t wordsCount, char* word, size_t length) {
    char** extended = new char* [wordsCount + 1];
    size_t copy = 0;
    for(size_t l = 0; l < wordsCount; ++l) {
        copy = strLength(words[l]);
        extended[l] = new char[copy];
        for(size_t k = 0; k <= copy; ++k) {
            extended[l][k] = words[l][k];
        }
    }
    for(size_t i = 0; i < wordsCount; ++i) {
        delete[] words[i];
    }
    delete[] words;
    words = extended;
    words[wordsCount] = new char[length + 1];
    size_t i = 0;
    for(; i < length; ++i) {
        words[wordsCount][i] = word[i];
    }
    words[wordsCount][i] = '\0';

    return words;
}

bool isBigger(char* a, char* b) {
    size_t i = 0;
    while(true) {
        if(((a[i] == '\0') || (b[i] == '\0'))) {
            return (a[i] == b[i]) && (a[i] == '\0');
        }
        if(b[i] > a[i]) {
            return false;
        }
    }

    return true;
}

void sort(char** words, size_t count) {
    const size_t last = count - 1;
    for(size_t i = 0; i < last; ++i) {
        if(isBigger(words[i + 1], words[i])) {

        }
    }
}

int main() {
    size_t n = 0;
    std::cin >> n;
    const size_t last = n - 1;
    char* text = new char[n];
    char** words = NULL;
    char* word = NULL;
    int begin = -1;
    size_t count = 0;
    size_t wordsCount = 0;
    bool isSymbolLetter = false;
    std::cin.get();
    for(size_t i = 0; i < n; ++i) {
        text[i] = std::cin.get();
    }
    for(size_t i = 0; i < n; ++i) {
        isSymbolLetter = isLetter(text[i]);
        if(isSymbolLetter) {
            if(begin == -1) {
                begin = i;
            } 
            ++count;
        }
        if((begin != -1) && (!isSymbolLetter || (i == last))) {
            word = text + begin;
            if(!wordIsFound(words, wordsCount, word, count)) {
                words = addToWords(words, wordsCount, word, count);
                ++wordsCount;
            }
            begin = -1;
            count = 0;
        }
    }
    for(size_t i = 0; i < wordsCount; ++i) {
        std::cout << words[i] << std::endl;
        delete[] words[i];
    }
    delete[] text;
    delete[] words;

    return 0;
}