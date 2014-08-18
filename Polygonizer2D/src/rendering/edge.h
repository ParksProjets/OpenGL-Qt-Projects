#ifndef EDGE_H_
#define EDGE_H_

#include "rendering/blending.h"
#include "util/geometry.h"

class Edge
{
public:
	Edge(Point2D point1, Point2D point2);

	Point2D GetPoint1();
	Point2D GetPoint2();
	double GetLength();
	double GetAngle();
	bool HasIntersection(Blend *blend);
	Point2D GetIntersectionPoint(Blend *blend);

private:
	Point2D point1;
	Point2D point2;
};

#endif
