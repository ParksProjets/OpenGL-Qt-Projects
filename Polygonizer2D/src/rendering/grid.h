#ifndef GRID_H_
#define GRID_H_

#include "rendering/cell.h"
#include "util/geometry.h"

class Grid
{
public:
	Grid(Rectangle bounds, double cellSideLength = 0.05);
	~Grid();

	int GetNumRows();
	int GetNumColumns();
	Cell *GetCell(int rowNumber, int columnNumber);
	Cell *GetContainerCell(Point2D point);
	bool IsEdgeCell(Cell *cell);

private:
	Rectangle bounds;
	double cellSideLength;
	int numRows;
	int numColumns;
	Cell **cells;

	void CreateCells();
};

#endif
