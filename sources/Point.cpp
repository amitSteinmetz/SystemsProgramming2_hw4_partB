#include "Point.hpp"
#include <cmath>
#include <iostream>

using namespace std;

/* Ctors */ 

Point::Point(double x, double y) : x(x), y(y)
{}

/* Methods */

double Point::distance(const Point other) const
{
    double x_pow = pow(x - other.getX(), 2);
    double y_pow = pow(y - other.getY(), 2);

    double result = sqrt(x_pow + y_pow);

    return result;
}

string Point::print() const
{
    string p = "(" + to_string(x) + ", " + to_string(y) + ")";
    
    return p;
}

Point Point::moveTowards(Point src, Point dst, double distance)
{
    double distance_from_src_to_dst = src.distance(dst);

    if (distance < 0) throw invalid_argument("Distance must be non-negative!");
   
    // Dest point is within or at the given distance from the src point
    if (distance_from_src_to_dst <= distance) return dst;

    else
    {  
        /*  Calculates a ratio to determine how far along the line connecting the source and destination 
            points the closest point should be */

        double dx, dy, ratio, newX, newY;

        dx = dst.getX() - src.getX();
        dy = dst.getY() - src.getY();

        ratio = distance / distance_from_src_to_dst;

        newX = src.getX() + dx * ratio;
        newY = src.getY() + dy * ratio;
        
        return Point(newX, newY);
    }
}
double Point::getX() const
{
    return x;
}
void Point::setX(double new_x)
{
    x = new_x;
}
double Point::getY() const
{
    return y;
}
void Point::setY(double new_y)
{
    y = new_y;
}