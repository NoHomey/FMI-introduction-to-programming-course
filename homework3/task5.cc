#include <cstdio>
#include <new>

typedef unsigned char Digit;
typedef unsigned long long UnsignedDecimalNumber;
typedef Digit(*CharToNumberConverter)(const char);

const char ZERO_CHAR = '0';
const char NINE_CHAR = '9';
const char A_CHAR = 'A';
const char b_CHAR = 'b';
const char x_CHAR = 'x';
const char SPACE_CHAR = ' ';
const char PLUS_CHAR = '+';
const char NEWLINE_CHAR = '\n';
const Digit TEN_DIGIT = 10;
const Digit SIXTEEN_DIGIT = 16;
const Digit ZERO_DIGIT = 0;
const Digit ONE_DIGIT = 1;
const Digit TWO_DIGIT = 2;
const Digit EIGHT_DIGIT = 8;

class Array {
protected:
static const Digit ALOCATED_CHUNK_SIZE = 8;
size_t capacity;
size_t size;
Digit* data;

public:
Array();

~Array();

void push(const Digit element);

size_t length() const;

Digit operator[](const size_t index) const;
}; 

class Number {
private:
static Digit CharToDecimalLikeNumberConverter(const char symbol);

static Digit CharToHexNumberConverter(const char symbol);

static CharToNumberConverter getCharToDigitConverter(const Digit baseOfNumericSystem);

protected:
Digit baseOfNumericSystem;
Array digits;
bool reachedEnd;

public:
Number();

Number(const Digit base, const char firstDigit);

UnsignedDecimalNumber toUnsignedDecimalNumber() const;

bool isEndReached() const;
};

int main() {
    char symbol = std::getchar();
    Digit baseOfNumericSystem = ZERO_DIGIT;
    UnsignedDecimalNumber result = ZERO_DIGIT;
    while(true) {
        baseOfNumericSystem = TEN_DIGIT;
        if((symbol != PLUS_CHAR) && (symbol != SPACE_CHAR)) {
            if(symbol == ZERO_CHAR) {
                symbol = std::getchar();
                baseOfNumericSystem = EIGHT_DIGIT;
                if((symbol == b_CHAR) || (symbol == x_CHAR)) {
                    baseOfNumericSystem = symbol == b_CHAR ? TWO_DIGIT : SIXTEEN_DIGIT;
                    symbol = std::getchar();
                }
                while(symbol == ZERO_CHAR) {
                    symbol = std::getchar();
                }
            }
            if((symbol != NEWLINE_CHAR) && (symbol != SPACE_CHAR)) {
                Number number = {baseOfNumericSystem, symbol};
                result += number.toUnsignedDecimalNumber();
                if(number.isEndReached()) {
                    std::printf("%llu\n", result);
                    break;
                }
            }
            if(symbol == NEWLINE_CHAR) {
                std::printf("%llu\n", result);
                break;
            }
        }
        symbol = std::getchar();
    }

    return 0;
}

Array::Array()
: capacity{0}, size{0}, data{nullptr} {
    try {
        data = new Digit[ALOCATED_CHUNK_SIZE];
    } catch(const std::bad_alloc& error) {
        throw error;
    }
    capacity = ALOCATED_CHUNK_SIZE;
}

Array::~Array() {
    delete[] data;
}

void Array::push(const Digit element) {
    if(capacity == size) {
        Digit* extended = nullptr;
        try {
            extended = new Digit[(capacity + ALOCATED_CHUNK_SIZE)];
        } catch(const std::bad_alloc& error) {
            throw error;
        }
        capacity += ALOCATED_CHUNK_SIZE;
        for(size_t index = 0; index < size; ++index) {
            extended[index] = data[index];
        }
        delete[] data;
        data = extended;
    }
    data[size] = element;
    ++size;
}

size_t Array::length() const {
    return size;
}

Digit Array::operator[](const size_t index) const {
    return data[index];
}

Digit Number::CharToDecimalLikeNumberConverter(const char symbol) {
    return symbol - ZERO_CHAR;
}

Digit Number::CharToHexNumberConverter(const char symbol) {
    return symbol <= NINE_CHAR
        ? CharToDecimalLikeNumberConverter(symbol)
        : (TEN_DIGIT + (symbol - A_CHAR));
}

CharToNumberConverter Number::getCharToDigitConverter(const Digit baseOfNumericSystem) {
    return baseOfNumericSystem == SIXTEEN_DIGIT
        ? CharToHexNumberConverter
        : CharToDecimalLikeNumberConverter;
}

Number::Number()
: baseOfNumericSystem{ZERO_DIGIT}, digits{}, reachedEnd{false} {}

Number::Number(const Digit base, const char firstDigit)
: baseOfNumericSystem{base}, digits{}, reachedEnd{false} {
    CharToNumberConverter converter = getCharToDigitConverter(base);
    char symbol = std::getchar();
    digits.push(converter(firstDigit));
    while(symbol != SPACE_CHAR) {
        if(symbol == NEWLINE_CHAR) {
            reachedEnd = true;
            break;
        }
        digits.push(converter(symbol));
        symbol = std::getchar();
    }
}

UnsignedDecimalNumber Number::toUnsignedDecimalNumber() const {
    UnsignedDecimalNumber number = ZERO_DIGIT;
    UnsignedDecimalNumber multiplier = ONE_DIGIT; 
    for(size_t index = digits.length(); index > ZERO_DIGIT; --index) {
        number += (digits[(index - 1)] * multiplier);
        multiplier *= baseOfNumericSystem;
    }

    return number;
}

bool Number::isEndReached() const {
    return reachedEnd;
}