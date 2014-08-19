#include "point.h"

#include <cmath>

Point::Point()
    : x(0.0), y(0.0), z(0.0)
{
}

Point::Point(double x, double y, double z)
    : x(x), y(y), z(z)
{
}

double Point::GetX() const
{
    return x;
}

double Point::GetY() const
{
    return y;
}

double Point::GetZ() const
{
    return z;
}

double Point::DistanceTo(const Point &otherPoint) const
{
    return sqrt(
            pow(GetX() - otherPoint.GetX(), 2) +
            pow(GetY() - otherPoint.GetY(), 2) +
            pow(GetZ() - otherPoint.GetZ(), 2));
}

Point Point::CrossProduct(const Point& otherPoint) const
{
    double newX = GetY() * otherPoint.GetZ() - GetZ() * otherPoint.GetY();
    double newY = GetZ() * otherPoint.GetX() - GetX() * otherPoint.GetZ();
    double newZ = GetX() * otherPoint.GetY() - GetY() * otherPoint.GetX();
    
    return Point(newX, newY, newZ);
}

double Point::Length() const
{
    return sqrt(pow(GetX(), 2) + pow(GetY(), 2) + pow(GetZ(), 2));
}

void Point::Normalize()
{
    double length = Length();

    if (length > 0) {
        x = x / length;
        y = y / length;
        z = z / length;
    }
}

void Point::Reverse()
{
    x = -x;
    y = -y;
    z = -z;
}

Point Point::operator+(const Point &otherPoint) const
{
    return Point(
        GetX() + otherPoint.GetX(),
        GetY() + otherPoint.GetY(),
        GetZ() + otherPoint.GetZ());
}

Point Point::operator-(const Point &otherPoint) const
{
    return Point(
        GetX() - otherPoint.GetX(),
        GetY() - otherPoint.GetY(),
        GetZ() - otherPoint.GetZ());
}

Point Point::operator*(double scalingFactor) const
{
    return Point(
        GetX() * scalingFactor,
        GetY() * scalingFactor,
        GetZ() * scalingFactor);
}

Point Point::operator*(const Point &otherPoint) const
{
    return Point(
        GetX() * otherPoint.GetX(),
        GetY() * otherPoint.GetY(),
        GetZ() * otherPoint.GetZ());
}

Point operator*(double scalingFactor, const Point &point)
{
    return point * scalingFactor;
}

Point Point::operator/(double scalingFactor) const
{
    return Point(
            GetX() / scalingFactor,
            GetY() / scalingFactor,
            GetZ() / scalingFactor);
}

Point &Point::operator+=(const Point &otherPoint)
{
    x += otherPoint.GetX();
    y += otherPoint.GetY();
    z += otherPoint.GetZ();

    return *this;
}
