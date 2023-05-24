#include "Point.hpp"
using namespace ariel;

Point::Point(double first, double second):x(first),y(second)
{
}
Point::~Point()
{

}
Point::Point():x(0),y(0){}
Point::Point (const Point& point):x(point.x),y(point.y){}
Point& Point::operator=(const Point& point)
{
    if(!(this==&point))
    {
        x=point.x;
        y=point.y;
    }
    return *this;
}
Point::Point (Point &&point) noexcept:x(point.x),y(point.y){}

Point & Point::operator=(Point&& point) noexcept
{
    x=point.x;
    y=point.y;

    return *this;
}

double Point::distance(const Point& point) const
{
    double dlx = x - point.x;
    double dly = y - point.y;
    
    return sqrt(dlx*dlx + dly*dly);
}
double Point::getX()const
{
    return x;
}
double Point::getY()const
{
    return y;
}
string Point::print() const
{
    
    string ret = "(" + to_string(x) + "," + to_string(y) + ")";
    return ret;
}
bool Point::operator==(const Point& point)const
{
    return (x==point.x)&&(y==point.y);
}
