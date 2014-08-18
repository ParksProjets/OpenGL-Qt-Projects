#ifndef GEOMETRY_H_
#define GEOMETRY_H_

#include <QPoint>

class Point2D
{
public:
	Point2D(double x, double y);
	Point2D(QPoint qPoint);

	double x();
	double y();
	double DistanceTo(Point2D otherPoint);

private:
	double _x;
	double _y;
};

class Rectangle
{
public:
	Rectangle(double minX, double maxX, double minY, double maxY);

	double GetMinX();
	double GetMaxX();
	double GetMinY();
	double GetMaxY();

	double GetHeight();
	double GetWidth();

	Point2D GetTopLeft();
	Point2D GetTopRight();
	Point2D GetBottomLeft();
	Point2D GetBottomRight();

	bool Contains(Point2D point);

private:
	double minX;
	double maxX;
	double minY;
	double maxY;
};

#endif
