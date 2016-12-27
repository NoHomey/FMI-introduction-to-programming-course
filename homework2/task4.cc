#include <cstdio>

const int DIGITS_COUNT = 10;

class Digits {
protected:
bool digits[DIGITS_COUNT];

void clear(const size_t index = 0);

void set();

public: 
Digits();

bool operator==(const Digits& other) const;
};

inline void printBool(const bool result);

int main() {
    const Digits a = {};
    const Digits b = {};
    printBool(a == b);

    return 0;
}

void Digits::clear(const size_t index) {
    if(index < DIGITS_COUNT) {
        digits[index] = false;
        clear(index + 1);
    }
}

void Digits::set() {
    char digit = std::getchar();
    if(digit == '-') {
        set();
    }
    if((digit >= '0') && (digit <= '9')) {
        digits[digit - '0'] = true;
        set();
    }
}

Digits::Digits()
: digits{} {
    clear();
    set();
}

bool Digits::operator==(const Digits& other) const {
    for(int index = 0; index < DIGITS_COUNT; ++index) {
        if(digits[index] != other.digits[index]) {
            return false;
        }
    }

    return true;
}

void printBool(const bool result) {
    std::printf("%s\n", (result ? "Yes" : "No"));
}