#include "rendering/primitives.h"

#include <cmath>

SoftObjectsFallOffFilter::SoftObjectsFallOffFilter(double maxDistance) :
	maxDistance(maxDistance)
{
}

double SoftObjectsFallOffFilter::GetValue(double distance)
{
	if (distance > maxDistance) {
		return 0.0;
	}

	double fractionOfRadius = distance / maxDistance;

	return 1 - (4.0 / 9) * pow(fractionOfRadius, 6)
			+ (17.0 / 9) * pow(fractionOfRadius, 4)
			- (22.0 / 9) * pow(fractionOfRadius, 2);
}

PointPrimitive::PointPrimitive(Point2D location, double fieldRadius,
		double isoValue) :
	location(location), fieldRadius(fieldRadius), isoValue(isoValue),
	fallOffFilter(fieldRadius), polygon(NULL)
{
}

double PointPrimitive::GetFieldValue(Point2D point)
{
	return fallOffFilter.GetValue(location.DistanceTo(point));
}

double PointPrimitive::GetIsoValue()
{
	return isoValue;
}

Point2D PointPrimitive::GetSkeletonPoint()
{
	return location;
}

bool PointPrimitive::ContainsPoint(Point2D point)
{
	return GetFieldValue(point) > GetIsoValue();
}

void PointPrimitive::Shift(double dx, double dy)
{
	location = Point2D(location.x() + dx, location.y() + dy);
}

void PointPrimitive::AssociatePolygon(Polygon *polygon)
{
	this->polygon = polygon;
}

Polygon *PointPrimitive::GetPolygon()
{
	return polygon;
}
