#ifndef POLYGON_H_
#define POLYGON_H_

#include <list>

#include "util/geometry.h"

class Polygon
{
public:
	Polygon(std::list<Point2D> surfacePoints);

	void Draw();
	void UpdateSurface(std::list<Point2D> newSurfacePoints);

private:
	std::list<Point2D> surfacePoints;
};

#endif
