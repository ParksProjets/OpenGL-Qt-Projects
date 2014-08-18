#include "rendering/edge.h"

#include <cmath>

#include "util/math.h"

Edge::Edge(Point2D point1, Point2D point2) : point1(point1), point2(point2)
{
}

Point2D Edge::GetPoint1()
{
	return point1;
}

Point2D Edge::GetPoint2()
{
	return point2;
}

double Edge::GetLength()
{
	return point1.DistanceTo(point2);
}

double Edge::GetAngle()
{
	return atan2(point2.y() - point1.y(), point2.x() - point1.x());
}

bool Edge::HasIntersection(Blend *blend)
{
	return blend->ContainsPoint(point1) !=
			blend->ContainsPoint(point2);
}

Point2D Edge::GetIntersectionPoint(Blend *blend)
{
	double fieldAtPoint1 = blend->GetGlobalField(point1);
	double fieldAtPoint2 = blend->GetGlobalField(point2);

	double distanceFromPoint1 = GetLength()
			* (blend->GetIsoValue() - fieldAtPoint1)
			/ (fieldAtPoint2 - fieldAtPoint1);

	double angle = GetAngle();

	double deltaX = distanceFromPoint1 * cos(angle);
	double deltaY = distanceFromPoint1 * sin(angle);

	return Point2D(point1.x() + deltaX, point1.y() + deltaY);
}
