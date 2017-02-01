#include <iostream>

class Point {
protected:
double x;
double y;

public:
static constexpr double POSITIVE_EPSILON = 0.001;
static constexpr double NEGATIVE_EPSILON = -POSITIVE_EPSILON;

Point(const double X = 0, const double Y = 0)
: x{X}, y{Y} {}

double getX() const {
    return x;
}

double getY() const {
    return y;
}
};

class Line {
protected:
double a;
double b;
double c;

public:
enum PointPositionAboutLine {BelongsToLine, PositiveHalfPlane, NegativeHalfPlane};

Line()
: a{0}, b{0}, c{0} {}

Line(const Point& p1, const Point& p2)
: Line{} {
    const double x1 = p1.getX();
    const double y1 = p1.getY();
    const double xDiff = p2.getX() - x1;
    const double yDiff = p2.getY() - y1;
    a = yDiff;
    b = -xDiff;
    c = (y1 * xDiff) - (x1 * yDiff);
}

PointPositionAboutLine getPointPosition(const Point& point) const {
    const double result = (a * point.getX()) + (b * point.getY()) + c;
    if(result > Point::POSITIVE_EPSILON) {
        return PositiveHalfPlane;
    }
    if(result < Point::NEGATIVE_EPSILON) {
        return NegativeHalfPlane;
    }

    return BelongsToLine;
}
};

class Star {
protected:
Line lines[5];

public:
enum StarSector {StarSector0, StarSector1, StarSector2, StarSector3, StarSector4, StarSector5, None};

Star()
: lines{} {}

void calculateLines(const Point* points) {
    lines[0] = {points[0], points[2]};
    lines[1] = {points[0], points[3]};
    lines[2] = {points[1], points[4]};
    lines[3] = {points[1], points[3]};
    lines[4] = {points[2], points[4]};
}

StarSector getStarSectorOfPoint(const Point& point) const {
    Line::PointPositionAboutLine positionAboutLines[5];
    for(int i = 0; i < 5; ++i) {
        positionAboutLines[i] = lines[i].getPointPosition(point);
    }
    if((positionAboutLines[0] == Line::PointPositionAboutLine::PositiveHalfPlane)
    && (positionAboutLines[1] == Line::PointPositionAboutLine::NegativeHalfPlane)
    && (positionAboutLines[2] == Line::PointPositionAboutLine::NegativeHalfPlane)
    && (positionAboutLines[3] == Line::PointPositionAboutLine::PositiveHalfPlane)
    && (positionAboutLines[4] == Line::PointPositionAboutLine::PositiveHalfPlane)) {
        return StarSector0;
    }
    if((positionAboutLines[0] == Line::PointPositionAboutLine::PositiveHalfPlane)
    && (positionAboutLines[1] == Line::PointPositionAboutLine::NegativeHalfPlane)
    && (positionAboutLines[2] == Line::PointPositionAboutLine::PositiveHalfPlane)) {
        return StarSector1;
    }
    if((positionAboutLines[0] == Line::PointPositionAboutLine::NegativeHalfPlane)
    && (positionAboutLines[2] == Line::PointPositionAboutLine::NegativeHalfPlane)
    && (positionAboutLines[3] == Line::PointPositionAboutLine::PositiveHalfPlane)) {
        return StarSector2;
    }
    if((positionAboutLines[0] == Line::PointPositionAboutLine::PositiveHalfPlane)
    && (positionAboutLines[3] == Line::PointPositionAboutLine::NegativeHalfPlane)
    && (positionAboutLines[4] == Line::PointPositionAboutLine::NegativeHalfPlane)) {
        return StarSector3;
    }
    if((positionAboutLines[1] == Line::PointPositionAboutLine::NegativeHalfPlane)
    && (positionAboutLines[3] == Line::PointPositionAboutLine::PositiveHalfPlane)
    && (positionAboutLines[4] == Line::PointPositionAboutLine::NegativeHalfPlane)) {
        return StarSector4;
    }
    if((positionAboutLines[2] == Line::PointPositionAboutLine::NegativeHalfPlane)
    && (positionAboutLines[3] == Line::PointPositionAboutLine::PositiveHalfPlane)
    && (positionAboutLines[4] == Line::PointPositionAboutLine::PositiveHalfPlane)) {
        return StarSector5;
    }

    return None;
}
};

int main() {
    Star star = {};
    Point edges[5];
    double x = 0;
    double y = 0;
    for(int i = 0; i < 5; ++i) {
        std::cin >> x;
        std::cin >> y;
        edges[i] = {x, y};
    }
    std::cin >> x;
    std::cin >> y;
    const Point point = {x, y};
    star.calculateLines(edges);
    const Star::StarSector sector = star.getStarSectorOfPoint(point);
    if(sector != Star::StarSector::None) {
        std::cout << "Sector: " << sector << std::endl;
    } else {
        std::cout << "None" << std::endl;
    }

    return 0;
}
