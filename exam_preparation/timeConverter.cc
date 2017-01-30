#include <iostream>

typedef unsigned int uint;

const uint SECONDS_IN_MINUTE = 60;
const uint SECONDS_IN_HOUR = SECONDS_IN_MINUTE * 60;
const uint SECONDS_IN_DAY = SECONDS_IN_HOUR * 24;

int main() {
    unsigned int seconds = 0;
    std::cin >> seconds;
    std::cout << seconds << " = ";
    const uint days = seconds / SECONDS_IN_DAY;
    seconds %= SECONDS_IN_DAY;
    const uint hours = seconds / SECONDS_IN_HOUR;
    seconds %= SECONDS_IN_HOUR;
    const uint minutes = seconds / SECONDS_IN_MINUTE;
    seconds %= SECONDS_IN_MINUTE;
    std::cout << days << ' ' << hours << ' ' << minutes << ' ' << seconds << std::endl;

    return 0;
}
