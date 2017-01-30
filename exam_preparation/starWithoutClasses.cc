#include <iostream>

const double POSITIVE_EPSILON = 0.001;
const double NEGATIVE_EPSILON = -POSITIVE_EPSILON;

double edges[5][2];
double lines[5][3];
double lineEquationValues[5];
double point[2];

void calculateLine(const size_t line,  const size_t edge1, const size_t edge2) {
    const double x1 = edges[edge1][0];
    const double y1 = edges[edge1][1];
    const double xDiff = edges[edge2][0] - x1;
    const double yDiff = edges[edge2][1] - y1;
    lines[line][0] = yDiff;
    lines[line][1] = -xDiff;
    lines[line][2] = (y1 * xDiff) - (x1 * yDiff);
}

double calculateLineEquationValue(const size_t line) {
    return (lines[line][0] * point[0]) + (lines[line][1] * point[1]) + lines[line][2];
}

bool isPointInPositiveHalfPlane(const size_t lineValue) {
    return lineEquationValues[lineValue] > POSITIVE_EPSILON;
}

bool isPointInNegativeHalfPlane(const size_t lineValue) {
    return lineEquationValues[lineValue] < NEGATIVE_EPSILON;
}

int calculateStarSector() {
    if(isPointInPositiveHalfPlane(0) && isPointInNegativeHalfPlane(1) && isPointInNegativeHalfPlane(2)
    && isPointInPositiveHalfPlane(3) && isPointInPositiveHalfPlane(4)) {
        return 0;
    }
    if(isPointInPositiveHalfPlane(0) && isPointInNegativeHalfPlane(1) && isPointInPositiveHalfPlane(2)) {
        return 1;
    }
    if(isPointInNegativeHalfPlane(0) && isPointInNegativeHalfPlane(2) && isPointInPositiveHalfPlane(3)) {
        return 2;
    }
    if(isPointInPositiveHalfPlane(0) && isPointInNegativeHalfPlane(3) && isPointInNegativeHalfPlane(4)) {
        return 3;
    }
    if(isPointInNegativeHalfPlane(1) && isPointInPositiveHalfPlane(3) && isPointInNegativeHalfPlane(4)) {
        return 4;
    }
    if(isPointInNegativeHalfPlane(2) && isPointInPositiveHalfPlane(3) && isPointInPositiveHalfPlane(4)) {
        return 5;
    }

    return -1;
}

int main() {
    int i = 0;
    for(; i < 5; ++i) {
        std::cin >> edges[i][0];
        std::cin >> edges[i][1];
    }
    std::cin >> point[0];
    std::cin >> point[1];
    calculateLine(0, 0, 2);
    calculateLine(1, 0, 3);
    calculateLine(2, 1, 4);
    calculateLine(3, 1, 3);
    calculateLine(4, 2, 4);
    for(i = 0; i < 5; ++i) {
        lineEquationValues[i] = calculateLineEquationValue(i);
    }
    const int starSector = calculateStarSector();
    if(starSector != 0) {
        std::cout << "Sector: " << starSector << std::endl;
    } else {
        std::cout << "None" << std::endl;
    }

    return 0;
}
