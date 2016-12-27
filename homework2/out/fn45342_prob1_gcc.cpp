/**
*
* Solution to homework task
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2016/2017
*
* @author Ivo Stratev
* @idnumber 45342
* @task 1
* @compiler GCC
*
*/

#include <cmath>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>

typedef float Number;

const Number PI = 3.14;
const Number EPSILON = 0.01;
const Number NEGATIVE_EPSILON = -0.01;

template <typename T = Number>
T input();

class Point {
 protected:
  Number x, y;

 public:
  Point(const Number x = 0, const Number y = 0);

  Number getX() const;

  Number getY() const;
};

class Vector {
 protected:
  Number a1, a2;

 public:
  Vector(const Point& begin, const Point& end);

  Number calculateXDiff() const;

  Number calculateYDiff() const;

  Number distance() const;
};

enum SideType { X, Y, Unknown };

class Side {
 private:
  bool isType(const SideType sideType) const;

 protected:
  Number forAll;
  SideType type;

 public:
  Side(const Number common = 0, const SideType sideType = Unknown);

  Number getCommon() const;

  SideType getType() const;

  bool isXType() const;

  bool isYType() const;

  bool isUnknownType() const;
};

class XSide : public Side {
 public:
  XSide(const Number common = 0);

  Number getX() const;
};

class YSide : public Side {
 public:
  YSide(const Number common = 0);

  Number getY() const;
};

class Line {
 protected:
  Point p1;
  Point p2;
  Number a;
  Number b;
  Number c;

 public:
  class SideIsOfUnknownType : public std::invalid_argument {
   public:
    SideIsOfUnknownType();
  };

  Line(const Point& point1, const Point& point2);

  Point getPoint1() const;

  Point getPoint2() const;

  Vector getLineVector() const;

  Number calculateX(const Number y) const;

  Number calculateY(const Number x) const;

  Point calculatePointFromIntersectionWithSide(const Side& side) const;
};

class RectangularShape {
 protected:
  Point A;
  Point C;
  YSide AB;
  XSide BC;
  YSide DC;
  XSide AD;

 public:
  RectangularShape(const Point& downLeft, const Point& upRight);

  virtual bool isXInRectanglesX(const Number x) const = 0;

  virtual bool isYInRectanglesY(const Number x) const = 0;

  virtual bool isInRectangle(const Point& point) const = 0;

  virtual Point calculatePointOfIntersectionWithLine(
      const Line& line) const = 0;
};

class RectangleWithCentralSymmetry : public RectangularShape {
 private:
  static Point pointWithPositiveCoordinates(const Point& point);

  static Point pointWithNegativeCoordinates(const Point& point);

  static bool isGreater(const Number n1, const Number n2);

  static bool isNegative(const Number n);

  static bool isInRectanglesSide(const Number d, const Side& dSide);

 public:
  class PointIsInsideRectangleWithCentralSymmetry
      : public std::invalid_argument {
   private:
    static std::string pointToString(const Point& point);

   public:
    PointIsInsideRectangleWithCentralSymmetry(
        const Point& pointinSidePlaygroundPoint,
        const Point& pointOfCentralSymmetry);
  };

  RectangleWithCentralSymmetry(const Point& point);

  bool isXInRectanglesX(const Number x) const;

  bool isYInRectanglesY(const Number y) const;

  bool isInRectangle(const Point& point) const final;

  Point calculatePointOfIntersectionWithLine(const Line& line) const;
};

Number f(const Number x);

int main() {
  const RectangleWithCentralSymmetry playground = {{5, 2}};
  Number playerTotalDistance = 0;
  const size_t n = input<size_t>();
  Number x = input();
  Number y = input();
  Point A = {x, y};
  Point B = A;
  Point playerPosition1 = A;
  Point playerPosition2 = B;
  bool isAInPlayground = playground.isInRectangle(A);
  bool isBInPlayground = isAInPlayground;
  Point inSidePlaygroundPoint, outSidePlaygroundPoint;
  for (size_t pointsCounter = 1; pointsCounter < n; ++pointsCounter) {
    A = B;
    isAInPlayground = isBInPlayground;
    x = input();
    y = input();
    B = {x, y};
    isBInPlayground = playground.isInRectangle(B);
    if (isAInPlayground || isBInPlayground) {
      playerPosition1 = A;
      playerPosition2 = B;
      if (!(isAInPlayground && isBInPlayground)) {
        if (isAInPlayground) {
          inSidePlaygroundPoint = A;
          outSidePlaygroundPoint = B;
        } else {
          inSidePlaygroundPoint = B;
          outSidePlaygroundPoint = A;
        }
        playerPosition1 = inSidePlaygroundPoint;
        playerPosition2 = playground.calculatePointOfIntersectionWithLine(
            {inSidePlaygroundPoint, outSidePlaygroundPoint});
      }
      playerTotalDistance +=
          f(Vector(playerPosition1, playerPosition2).distance());
    }
  }
  std::cout << std::fixed << std::setprecision(3) << playerTotalDistance
            << '\n';

  return 0;
}

template <typename T>
T input() {
  T value;
  std::cin >> value;
  return value;
}

Point::Point(const Number x, const Number y) : x{x}, y{y} {}

Number Point::getX() const { return x; }

Number Point::getY() const { return y; }

Vector::Vector(const Point& begin, const Point& end)
    : a1{end.getX() - begin.getX()}, a2{end.getY() - begin.getY()} {}

Number Vector::calculateXDiff() const { return std::abs(a1); }

Number Vector::calculateYDiff() const { return std::abs(a2); }

Number Vector::distance() const { return std::sqrt((a1 * a1) + (a2 * a2)); }

bool Side::isType(const SideType sideType) const { return type == sideType; }

Side::Side(const Number common, const SideType sideType)
    : forAll{common}, type{sideType} {}

Number Side::getCommon() const { return forAll; }

SideType Side::getType() const { return type; }

bool Side::isXType() const { return isType(SideType::X); }

bool Side::isYType() const { return isType(SideType::Y); }

bool Side::isUnknownType() const { return isType(SideType::Unknown); }

XSide::XSide(const Number common) : Side(common, SideType::X) {}

Number XSide::getX() const { return getCommon(); }

YSide::YSide(const Number common) : Side(common, SideType::Y) {}

Number YSide::getY() const { return getCommon(); }

Line::SideIsOfUnknownType::SideIsOfUnknownType()
    : std::invalid_argument(
          "Can not calculatePointFromIntersectionWithSide which type is "
          "SideType::Unknown\n") {}

Line::Line(const Point& point1, const Point& point2)
    : p1{point1}, p2{point2}, a{0}, b{0}, c{0} {
  const Number y = p2.getY() - p1.getY();
  const Number x = p2.getX() - p1.getX();
  a = y;
  b = -x;
  c = (x * p1.getY()) - (y * p1.getX());
}

Point Line::getPoint1() const { return p1; }

Point Line::getPoint2() const { return p2; }

Vector Line::getLineVector() const { return {p1, p2}; }

Number Line::calculateX(const Number y) const { return (c + (b * y)) / (-a); }

Number Line::calculateY(const Number x) const { return (c + (a * x)) / (-b); }

Point Line::calculatePointFromIntersectionWithSide(const Side& side) const {
  if (side.isUnknownType()) {
    throw SideIsOfUnknownType();
  }
  if (side.isXType()) {
    const Number x = side.getCommon();
    return {x, calculateY(x)};
  } else {
    const Number y = side.getCommon();
    return {calculateX(y), y};
  }
}

RectangularShape::RectangularShape(const Point& downLeft, const Point& upRight)
    : A{downLeft},
      C{upRight},
      AB{A.getY()},
      BC{C.getX()},
      DC{C.getY()},
      AD{A.getX()} {}

Point RectangleWithCentralSymmetry::pointWithPositiveCoordinates(
    const Point& point) {
  return {std::abs(point.getX()), std::abs(point.getY())};
}

Point RectangleWithCentralSymmetry::pointWithNegativeCoordinates(
    const Point& point) {
  const Point positivePoint = pointWithPositiveCoordinates(point);
  return {-(positivePoint.getX()), -(positivePoint.getY())};
}

bool RectangleWithCentralSymmetry::isGreater(const Number n1, const Number n2) {
  return n1 >= (n2 + EPSILON);
}

bool RectangleWithCentralSymmetry::isNegative(const Number n) {
  return n <= NEGATIVE_EPSILON;
}

bool RectangleWithCentralSymmetry::isInRectanglesSide(const Number d,
                                                      const Side& dSide) {
  return !(isGreater(std::abs(d), dSide.getCommon()));
}

std::string RectangleWithCentralSymmetry::
    PointIsInsideRectangleWithCentralSymmetry::pointToString(
        const Point& point) {
  return "Point with coordinates (" + std::to_string(point.getX()) + ", " +
         std::to_string(point.getY()) + ")";
}

RectangleWithCentralSymmetry::PointIsInsideRectangleWithCentralSymmetry::
    PointIsInsideRectangleWithCentralSymmetry(
        const Point& pointinSidePlaygroundPoint,
        const Point& pointOfCentralSymmetry)
    : std::invalid_argument(
          pointToString(pointinSidePlaygroundPoint) +
          "\nis inSidePlaygroundPoint RectangleWithCentralSymmetry about\n" +
          pointToString(pointOfCentralSymmetry) +
          "\nthere is no side of intersection with that point!\n") {}

RectangleWithCentralSymmetry::RectangleWithCentralSymmetry(const Point& point)
    : RectangularShape(pointWithNegativeCoordinates(point),
                       pointWithPositiveCoordinates(point)) {}

bool RectangleWithCentralSymmetry::isXInRectanglesX(const Number x) const {
  return isInRectanglesSide(x, BC);
}

bool RectangleWithCentralSymmetry::isYInRectanglesY(const Number y) const {
  return isInRectanglesSide(y, DC);
}

bool RectangleWithCentralSymmetry::isInRectangle(const Point& point) const {
  return isXInRectanglesX(point.getX()) & isYInRectanglesY(point.getY());
}

Point RectangleWithCentralSymmetry::calculatePointOfIntersectionWithLine(
    const Line& line) const {
  const Point point = line.getPoint2();
  if (isInRectangle(point)) {
    throw PointIsInsideRectangleWithCentralSymmetry(point, C);
  }
  const Vector vector = line.getLineVector();
  XSide xSide = BC;
  YSide ySide = DC;
  if (isNegative(point.getX())) {
    xSide = AD;
  }
  if (isNegative(point.getY())) {
    ySide = AB;
  }
  Side intersectionSide = xSide;
  if (isGreater(vector.calculateYDiff(), vector.calculateXDiff())) {
    intersectionSide = ySide;
  }

  return line.calculatePointFromIntersectionWithSide(intersectionSide);
}

Number f(const Number x) { return (((PI * x) / 2) + x) / 2; }