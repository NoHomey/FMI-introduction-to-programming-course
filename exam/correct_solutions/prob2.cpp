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

bool areEqual(const char* str1, const char* str2, const size_t str2Length) {
    for(size_t i = 0; str1[i] != '\0'; ++i) {
        if((i == str2Length) || (str1[i] != str2[i])) {
            return false;
        }
    }

    return true;
}

bool wordIsFound(char** words, size_t wordsCount, const char* word, size_t length) {
    for(size_t i = 0; i < wordsCount; ++i) {
        if(areEqual(words[i], word, length)) {
            return true;
        }
    }

    return false;
}

size_t strLength(const char* str) {
    size_t i = 0;
    while(str[i] != '\0') {
        ++i;
    }

    return i;
}

void deleteWords(char** words, const size_t count) {
    for(size_t i = 0; i < count; ++i) {
        delete[] words[i];
    }
    delete[] words;
}

char** addToWords(char** words, const size_t wordsCount, const char* word, const size_t length) {
    char** extended = new(std::nothrow) char* [wordsCount + 1];
    if(extended == NULL) {
        deleteWords(words, wordsCount);
        return NULL;
    }
    size_t copy = 0;
    for(size_t l = 0; l < wordsCount; ++l) {
        copy = strLength(words[l]);
        extended[l] = new(std::nothrow) char[copy];
        if(extended[l] == NULL) {
            deleteWords(extended, l);
            deleteWords(words, wordsCount);
            return NULL;

        }
        for(size_t k = 0; k <= copy; ++k) {
            extended[l][k] = words[l][k];
        }
    }
    deleteWords(words, wordsCount);
    words = extended;
    words[wordsCount] = new(std::nothrow) char[length + 1];
    if(words[wordsCount] == NULL) {
        deleteWords(words, wordsCount);
        return NULL;
    }
    size_t i = 0;
    for(; i < length; ++i) {
        words[wordsCount][i] = word[i];
    }
    words[wordsCount][i] = '\0';

    return words;
}

bool isBigger(const char* a, const char* b) {
    size_t i = 0;
    while(true) {
        if(((a[i] == '\0') || (b[i] == '\0'))) {
            return a[i] > b[i];
        }
        if(a[i] == b[i]) {
            ++i;
            continue;
        }

        return a[i] > b[i];
    }

    return false;
}

void sortWords(char** words, size_t count) {
    const size_t last = count - 1;
    size_t maxIndex = 0;
    for(size_t i = 0; i < last; ++i) {
        maxIndex = i;
        for(size_t j = i; j < count; ++j) {
            if(isBigger(words[j], words[maxIndex])) {
                maxIndex = j;
            }
        }
        if(maxIndex != i) {
            char* tmp = words[i];
            words[i] = words[maxIndex];
            words[maxIndex] = tmp;
        }
    }
}

int main() {
    size_t n = 0;
    std::cin >> n;
    const size_t last = n - 1;
    char* text = new(std::nothrow) char[n];
    if(text == NULL) {
        return 0;
    }
    char** words = NULL;
    char* word = NULL;
    int begin = -1;
    size_t count = 0;
    size_t wordsCount = 0;
    bool isSymbolLetter = false;
    std::cin.ignore();
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
                if(words == NULL) {
                    delete[] text;
                    return 0;
                }
                ++wordsCount;
            }
            begin = -1;
            count = 0;
        }
    }
    delete[] text;
    sortWords(words, wordsCount);
    for(size_t i = 0; i < wordsCount; ++i) {
        std::cout << words[i] << std::endl;
        delete[] words[i];
    }
    delete[] words;

    return 0;
}
