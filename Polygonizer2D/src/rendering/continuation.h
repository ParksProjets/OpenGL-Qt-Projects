#ifndef CONTINUATION_H_
#define CONTINUATION_H_

#include <list>

#include "rendering/blending.h"
#include "rendering/grid.h"
#include "rendering/primitives.h"

/**
 * Finds cubes that are part of a primitive's surface.
 */
class ContinuationAlgorithm
{
public:
	ContinuationAlgorithm(Grid *grid, Primitive *primitive, Blend *blend);

	std::list<Cell *> GetSurfaceCells();
	Cell *GetSeedCell();
	std::list<Cell *> GetUnvisitedNeighbourCells(Cell *targetCell);

private:
	Grid *grid;
	Primitive *primitive;
	Blend *blend;

	void RecursiveSurfaceSearch(
			Cell *targetCell, std::list<Cell *> *surfaceCells);
	bool IsHorizontallyIntersectingCell(Cell *cell);
	bool SurfaceIsOffEdge(Cell *cell);
};

#endif
