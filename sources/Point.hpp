#pragma once
#include <string>

class Point
{
    // Attributes:
    double x;
    double y;

    // Ctors
    public:
    Point(double x, double y);

    // Methods
    double distance(const Point other) const;
    std::string print() const;
    static Point moveTowards(Point src, Point dst, double distance);
    double getX() const;
    void setX(double new_x);
    double getY() const;
    void setY(double new_y);
};