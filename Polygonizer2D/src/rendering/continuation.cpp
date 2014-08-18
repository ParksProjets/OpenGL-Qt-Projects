#include "continuation.h"

typedef std::list<Cell *>::iterator CellIterator;

ContinuationAlgorithm::ContinuationAlgorithm(
		Grid *grid, Primitive *primitive, Blend *blend) :
	grid(grid), primitive(primitive), blend(blend)
{
}

std::list<Cell *> ContinuationAlgorithm::GetSurfaceCells()
{
	std::list<Cell *> surfaceCells;

	Cell *seedCell = GetSeedCell();
	seedCell->MarkVisited();
	surfaceCells.push_back(seedCell);

	RecursiveSurfaceSearch(seedCell, &surfaceCells);

	return surfaceCells;
}

Cell *ContinuationAlgorithm::GetSeedCell()
{
	Point2D skeletonPoint = primitive->GetSkeletonPoint();

	Cell *skeletonCell = grid->GetContainerCell(skeletonPoint);
	int skeletonRow = skeletonCell->GetRow();
	int skeletonColumn = skeletonCell->GetColumn();

	int row = skeletonRow;
	int column = skeletonColumn;
	Cell *currentCell = skeletonCell;

	while(!IsHorizontallyIntersectingCell(currentCell)) {
		column -=1;

		if (column < 0) {
			break;
		}

		currentCell = grid->GetCell(row, column);
	}

	if (column < 0) {
		/* We didn't find an intersection searching left, probably because
		 * the primitive goes off the edge of the grid.  Unless the grid is
		 * really small, we should then find an intersection by searching
		 * right.
		 */
		row = skeletonRow;
		column = skeletonColumn;
		currentCell = skeletonCell;

		while(!IsHorizontallyIntersectingCell(currentCell)) {
			currentCell = grid->GetCell(row, ++column);
		}
	}

	return currentCell;
}

void ContinuationAlgorithm::RecursiveSurfaceSearch(
		Cell *targetCell, std::list<Cell *> *surfaceCells)
{
	std::list<Cell *> neighbours = GetUnvisitedNeighbourCells(targetCell);

	for (CellIterator it = neighbours.begin();
			it != neighbours.end(); it++) {
		Cell *cell = *it;

		if (cell->HasIntersectingEdge(blend) || SurfaceIsOffEdge(cell)) {
			surfaceCells->push_back(cell);
			RecursiveSurfaceSearch(cell, surfaceCells);
		}
	}
}

bool ContinuationAlgorithm::SurfaceIsOffEdge(Cell *cell)
{
	return (blend->ContainsPoint(cell->GetBottomLeft()) ||
			blend->ContainsPoint(cell->GetTopRight()))
			&& grid->IsEdgeCell(cell);
}

bool ContinuationAlgorithm::IsHorizontallyIntersectingCell(Cell *cell)
{
	return blend->ContainsPoint(cell->GetBottomLeft()) !=
			blend->ContainsPoint(cell->GetBottomRight());
}

std::list<Cell *> ContinuationAlgorithm::GetUnvisitedNeighbourCells(
		Cell *targetCell)
{
	std::list<Cell *> unvisitedNeighbours;

	int targetRow = targetCell->GetRow();
	int targetColumn = targetCell->GetColumn();

	for (int row = targetRow - 1; row <= targetRow +1; row++) {
		for (int column = targetColumn - 1; column <= targetColumn +1; column++) {
			if (row < 0 || column < 0 ||
					row >= grid->GetNumRows() ||
					column >= grid->GetNumColumns()) {
				continue;
			}

			if (row == targetRow && column == targetColumn) {
				continue;
			}

			Cell *cell = grid->GetCell(row, column);
			if (!cell->IsVisited()) {
				unvisitedNeighbours.push_back(cell);
				cell->MarkVisited();
			}
		}
	}

	return unvisitedNeighbours;
}
