#include "rendering/polygonization.h"

typedef std::list<Edge>::iterator EdgeIterator;
typedef std::list<Cell *>::iterator CellIterator;

PolygonizationAlgorithm::PolygonizationAlgorithm(
		std::list<Cell *> surfaceCells, Blend *blend) :
	surfaceCells(surfaceCells), blend(blend)
{
}

std::list<Point2D> PolygonizationAlgorithm::GetSurfacePoints()
{
	std::list<Point2D> surfacePoints;

	std::list<Edge> intersectingEdges = GetIntersectingEdges();

	for (EdgeIterator it = intersectingEdges.begin();
			it != intersectingEdges.end(); it++) {
		Edge edge = *it;

		surfacePoints.push_back(edge.GetIntersectionPoint(blend));
	}

	return surfacePoints;
}

std::list<Edge> PolygonizationAlgorithm::GetIntersectingEdges()
{
	std::list<Edge> intersectingEdges;

	// TODO: avoid duplicate edges...
	for (CellIterator it = surfaceCells.begin();
			it != surfaceCells.end(); it++) {
		Cell *cell = *it;

		std::list<Edge> edges = cell->GetIntersectingEdges(blend);
		intersectingEdges.splice(intersectingEdges.end(), edges);
	}

	return intersectingEdges;
}
