#include "rendering/grid.h"

#include "util/math.h"

Grid::Grid(Rectangle bounds, double cellSideLength) :
	bounds(bounds), cellSideLength(cellSideLength),
	numRows(bounds.GetHeight() / cellSideLength),
	numColumns(bounds.GetWidth() / cellSideLength),
	cells()
{
	CreateCells();
}

Grid::~Grid()
{
	for (int i = 0; i < numRows * numColumns; i++) {
		delete cells[i];
	}

	delete cells;
}

int Grid::GetNumRows()
{
	return numRows;
}

int Grid::GetNumColumns()
{
	return numColumns;
}

Cell *Grid::GetCell(int rowNumber, int columnNumber)
{
	return cells[columnNumber * numRows + rowNumber];
}

Cell *Grid::GetContainerCell(Point2D point)
{
	int rowNumber = IntFloor(
			(point.y() - bounds.GetMinY()) / cellSideLength);
	int columnNumber = IntFloor(
			(point.x() - bounds.GetMinX()) / cellSideLength);

	return GetCell(rowNumber, columnNumber);
}

bool Grid::IsEdgeCell(Cell *cell)
{
	int cellRow = cell->GetRow();
	int cellColumn = cell->GetColumn();

	return cellRow == 0 || cellRow == numRows - 1 || cellColumn == 0 ||
			cellColumn == numColumns - 1;
}

void Grid::CreateCells()
{
	cells = new Cell*[numRows * numColumns];

	for (int column = 0; column < numColumns; column++) {
		for (int row = 0; row < numRows; row++) {
			double leftX = bounds.GetMinX() + column * cellSideLength;
			double bottomY = bounds.GetMinY() + row * cellSideLength;

			cells[column * numRows + row] = new Cell(leftX, bottomY,
					cellSideLength, row, column);
		}
	}
}
