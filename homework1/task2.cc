#include <iostream>
using namespace std;

#define NUMBER(name, value) number name = value

#define DEFINE_VARIABLE(name) NUMBER(name, 0)

#define DEFINE_CONST(name, value) const NUMBER(name, value)

#define CHAR(name, value) char name = value

#define DEFINE_CHAR_CONST(name, value) const CHAR(name, value)

#define EXTRACT_FROM_EGN(part, extracter)\
part = egn % extracter;\
egn /= extracter\

#define EXTRACT_FROM_EGN_FROM_DATE(part) EXTRACT_FROM_EGN(part, TWO_DIGITS)

#define FULL_YEAR_STARTS(yy) fullYear += yy##00

#define TEST_MONTH_FOR_FULL_YEAR_STARTS(mm, yy)\
if(month > mm) {\
    normalizatedMonth -= mm;\
    FULL_YEAR_STARTS(yy);\
}\

#define IF_VALID() if(!invalid)

#define IS_EVEN_DIVIDABLE(value, divider) ((value % divider) == 0)

#define EXTRACT_ADD_TO_CHECKSUM_FROM_VARAIBLE(varaible, weight)\
checksum += (varaible % ONE_DIGIT) * weight;\
varaible /= ONE_DIGIT\

#define PRINT(value) cout << value

#define TWO_DIGIT_PRINT(value)\
if(value < 10) {\
    PRINT(0) << value;\
} else {\
    PRINT(value);\
}\

/* @begin */
typedef unsigned short number;

enum ChechsumWeights {
    SequenceNNNWeight = 6,
    SequenceNNWeight = 3,
    SequenceNWeight = 7,
    DayDDWeight = 9,
    DayDWeight = 10,
    MonthMMWeight = 5,
    MonthMWeight = 8,
    YearYYWeight = 4,
    YearYWeight = 2
};

DEFINE_CONST(ONE_DIGIT, 10);
DEFINE_CONST(THREE_DIGITS, 1000);
DEFINE_CONST(TWO_DIGITS, 100);
DEFINE_CHAR_CONST(DOT, '.');
DEFINE_CHAR_CONST(SPACE, ' ');

int main() {
    DEFINE_VARIABLE(day);
    DEFINE_VARIABLE(month);
    DEFINE_VARIABLE(year);
    DEFINE_VARIABLE(birthSequence);
    DEFINE_VARIABLE(controlDigit);
    CHAR(sex, 'M');
    unsigned long egn = 0;
    bool invalid = false;
    cin >> egn;
    EXTRACT_FROM_EGN(controlDigit, ONE_DIGIT);
    EXTRACT_FROM_EGN(birthSequence, THREE_DIGITS);
    EXTRACT_FROM_EGN_FROM_DATE(day);
    EXTRACT_FROM_EGN_FROM_DATE(month);
    EXTRACT_FROM_EGN_FROM_DATE(year);
    NUMBER(dayCopy, day);
    NUMBER(monthCopy, month);
    NUMBER(normalizatedMonth, month);
    NUMBER(fullYear, year);
    TEST_MONTH_FOR_FULL_YEAR_STARTS(40, 20)
    else TEST_MONTH_FOR_FULL_YEAR_STARTS(20, 18)
    else {
        FULL_YEAR_STARTS(19);
    }
    invalid = (normalizatedMonth == 0) || (normalizatedMonth > 12);
    IF_VALID() {
        invalid = day == 0;
        IF_VALID() {
            unsigned short limit = 31;
            switch(normalizatedMonth) {
                case 4:
                case 6:
                case 9:
                case 11:
                    limit = 30;
                    break;
                case 2: limit = (IS_EVEN_DIVIDABLE(year, 4) && IS_EVEN_DIVIDABLE(fullYear, 100) && IS_EVEN_DIVIDABLE(fullYear, 400)) ? 29 : 28;
            }
            invalid = day > limit;
        }
    }
    IF_VALID() {
        DEFINE_VARIABLE(checksum);
        if(!IS_EVEN_DIVIDABLE((birthSequence % ONE_DIGIT), 2)) {
            sex = 'F';
        }
        EXTRACT_ADD_TO_CHECKSUM_FROM_VARAIBLE(birthSequence, SequenceNNNWeight);
        EXTRACT_ADD_TO_CHECKSUM_FROM_VARAIBLE(birthSequence, SequenceNNWeight);
        EXTRACT_ADD_TO_CHECKSUM_FROM_VARAIBLE(birthSequence, SequenceNWeight);
        EXTRACT_ADD_TO_CHECKSUM_FROM_VARAIBLE(dayCopy, DayDDWeight);
        EXTRACT_ADD_TO_CHECKSUM_FROM_VARAIBLE(dayCopy, DayDWeight);
        EXTRACT_ADD_TO_CHECKSUM_FROM_VARAIBLE(monthCopy, MonthMMWeight);
        EXTRACT_ADD_TO_CHECKSUM_FROM_VARAIBLE(monthCopy, MonthMWeight);
        EXTRACT_ADD_TO_CHECKSUM_FROM_VARAIBLE(year, YearYYWeight);
        EXTRACT_ADD_TO_CHECKSUM_FROM_VARAIBLE(year, YearYWeight);
        checksum %= 11;
        if(checksum > 9) {
            checksum = 0;
        } 
        invalid = checksum != controlDigit;
    }
    IF_VALID() {
        TWO_DIGIT_PRINT(day)
        PRINT(DOT);
        TWO_DIGIT_PRINT(normalizatedMonth)
        PRINT(DOT) << fullYear << SPACE << sex;
    } else {
        PRINT("Bad input data!");
    }
    PRINT('\n');

    return 0;
}