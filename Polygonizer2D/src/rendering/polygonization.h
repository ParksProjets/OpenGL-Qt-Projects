#ifndef POLYGONIZATION_H_
#define POLYGONIZATION_H_

#include <list>

#include "rendering/blending.h"
#include "rendering/cell.h"
#include "rendering/edge.h"
#include "util/geometry.h"

class PolygonizationAlgorithm
{
public:
	PolygonizationAlgorithm(std::list<Cell *> surfaceCells, Blend *blend);

	std::list<Point2D> GetSurfacePoints();

private:
	std::list<Cell *> surfaceCells;
	Blend *blend;

	std::list<Edge> GetIntersectingEdges();
};

#endif
