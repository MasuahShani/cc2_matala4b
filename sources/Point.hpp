#pragma once
#include <iostream>
#include <cmath>
#include <string>

using namespace std;
namespace ariel{
    class Point
    {
    private:
        double x;
        double y;
       

    public:
    
        Point(double first, double second);
        ~Point();
        Point();
        Point (const Point& point);
        Point& operator=(const Point& point);
        Point (Point &&point) noexcept;
        
        Point & operator=(Point&& point) noexcept;

        double distance(const Point& point) const;
        double getX()const;
        double getY()const;
        string print() const;
        bool operator==(const Point& point)const;
        static Point moveTowards(Point const& src, Point const& dst, double dis)
        {
            if(dis<0)
            {
                throw invalid_argument("neg dis");
            }
            double dlx = dst.x - src.x;
            double dly = dst.y - src.y;
            double distance = sqrt(dlx * dlx + dly * dly);

            double ratio = dis / distance;
            if(distance<dis)
            {
                ratio=1;
            }
            
            
            double newX = src.x + ratio * dlx;
            double newY = src.y + ratio * dly;

            if(src.getY()>dst.getY() && src.getX()>src.getX())
            {
                newX = src.x - ratio * dlx;
                newY = src.y - ratio * dly;
            }
            else if(src.getY()>dst.getY() && src.getX()<src.getX())
            {
               newX = src.x + ratio * dlx;
                newY = src.y - ratio * dly;
            }
            else if(src.getY()<dst.getY() && src.getX()>src.getX())
            {
               newX = src.x - ratio * dlx;
                newY = src.y + ratio * dly;
            }

            return Point(newX, newY);
        }

    };
   
}