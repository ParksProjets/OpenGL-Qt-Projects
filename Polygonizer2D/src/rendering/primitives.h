#ifndef PRIMITIVES_H_
#define PRIMITIVES_H_

#include "rendering/polygon.h"
#include "util/geometry.h"

class SoftObjectsFallOffFilter
{
public:
	SoftObjectsFallOffFilter(double maxDistance);

	double GetValue(double distance);

private:
	double maxDistance;
};

class Primitive
{
public:
	virtual ~Primitive() {};

	virtual double GetFieldValue(Point2D point)	= 0;
	virtual double GetIsoValue() = 0;
	virtual Point2D GetSkeletonPoint() = 0;
	virtual bool ContainsPoint(Point2D point) = 0;
	virtual void Shift(double dx, double dy) = 0;
	virtual void AssociatePolygon(Polygon *polygon) = 0;
	virtual Polygon *GetPolygon() = 0;
};

class PointPrimitive : public Primitive
{
public:
	PointPrimitive(Point2D location, double fieldRadius, double isoValue);

	double GetFieldValue(Point2D point);
	double GetIsoValue();
	Point2D GetSkeletonPoint();
	bool ContainsPoint(Point2D point);
	void Shift(double dx, double dy);
	void AssociatePolygon(Polygon *polygon);
	Polygon *GetPolygon();

private:
	Point2D location;
	double fieldRadius;
	double isoValue;
	SoftObjectsFallOffFilter fallOffFilter;
	Polygon *polygon;
};

#endif
