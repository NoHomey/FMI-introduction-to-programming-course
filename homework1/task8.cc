#include <iostream>
using namespace std;

#define DEFINE_VARIABLE(name) unsigned int name = 0

#define PRINT(value) cout << value

#define PRINT_IF_INCLUDES(banknote)\
if(sum >= banknote) {\
    count = sum / banknote;\
    PRINT(' ') << count << '*' << banknote;\
    sum -= count * banknote;\
    if(sum > 0) {\
        PRINT(" +");\
    }\
}\

/* @begin */
int main(void) {
    DEFINE_VARIABLE(sum);
    DEFINE_VARIABLE(count);
    cin >> sum;
    PRINT(sum) << " =";
    PRINT_IF_INCLUDES(50)
    PRINT_IF_INCLUDES(20)
    PRINT_IF_INCLUDES(10)
    PRINT_IF_INCLUDES(5)
    PRINT_IF_INCLUDES(2)
    PRINT_IF_INCLUDES(1)
    PRINT('\n');

    return 0;
}