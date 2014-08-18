#include "util/geometry.h"

#include <cmath>

Point2D::Point2D(double x, double y) :
	_x(x), _y(y)
{
}

Point2D::Point2D(QPoint qPoint) :
	_x(qPoint.x()), _y(qPoint.y())
{
}

double Point2D::x()
{
	return _x;
}

double Point2D::y()
{
	return _y;
}

double Point2D::DistanceTo(Point2D otherPoint)
{
	return sqrt(
			pow(x() - otherPoint.x(), 2) +
			pow(y() - otherPoint.y(), 2));
}

Rectangle::Rectangle(double minX, double maxX, double minY, double maxY) :
	minX(minX), maxX(maxX), minY(minY), maxY(maxY)
{
}

double Rectangle::GetMinX()
{
	return minX;
}

double Rectangle::GetMaxX()
{
	return maxX;
}

double Rectangle::GetMinY()
{
	return minY;
}

double Rectangle::GetMaxY()
{
	return maxY;
}

double Rectangle::GetHeight()
{
	return maxY - minY;
}

double Rectangle::GetWidth()
{
	return maxX - minX;
}

Point2D Rectangle::GetTopLeft()
{
	return Point2D(minX, maxY);
}

Point2D Rectangle::GetTopRight()
{
	return Point2D(maxX, maxY);
}

Point2D Rectangle::GetBottomLeft()
{
	return Point2D(minX, minY);
}

Point2D Rectangle::GetBottomRight()
{
	return Point2D(maxX, minY);
}

bool Rectangle::Contains(Point2D point)
{
	return point.x() >= minX && point.x() < maxX &&
			point.y() >= minY && point.y() < maxY;
}
