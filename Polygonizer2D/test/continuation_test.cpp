#include "rendering/continuation.h"

#include "gtest/gtest.h"

#include <list>

#include "rendering/blending.h"
#include "rendering/primitives.h"
#include "util/geometry.h"

TEST(ContinuationAlgTest, GetSeedCell)
{
	Rectangle bounds(-10.0, 10.0, -10.0, 10.0);
	Grid grid(bounds, 1.0);

	Point2D location(0.0, 0.0);
	double radius = 5.0;
	double isoValue = 0.5;
	PointPrimitive primitive(location, radius, isoValue);

	std::list<Primitive *> primitives;
	primitives.push_back(&primitive);

	SummationBlend blend(primitives, isoValue);

	ContinuationAlgorithm alg(&grid, &primitive, &blend);
	Cell *seedCell = alg.GetSeedCell();

	EXPECT_EQ(10, seedCell->GetRow());
	EXPECT_EQ(7, seedCell->GetColumn());
}

void ExpectContainsCell(int row, int column, std::list<Cell *> cells)
{
	bool foundCell = false;
	for (std::list<Cell *>::iterator it = cells.begin();
			it != cells.end(); it++) {
		Cell *cell = *it;

		if (cell->GetRow() == row && cell->GetColumn() == column) {
			foundCell = true;
			break;
		}
	}

	EXPECT_TRUE(foundCell) <<
			"Couldn't find cell (" << row << ", " << column << ")";
}

TEST(ContinuationAlgTest, GetUnvisitedNeighbours)
{
	Rectangle bounds(-2.0, 2.0, -2.0, 2.0);
	Grid grid(bounds, 1.0);

	ContinuationAlgorithm alg(&grid, NULL, NULL);
	Cell *targetCell = grid.GetCell(1, 1);

	std::list<Cell *> neighbours = alg.GetUnvisitedNeighbourCells(targetCell);

	EXPECT_EQ(8, neighbours.size());
	ExpectContainsCell(0, 0, neighbours);
	ExpectContainsCell(1, 0, neighbours);
	ExpectContainsCell(2, 0, neighbours);
	ExpectContainsCell(2, 1, neighbours);
	ExpectContainsCell(2, 2, neighbours);
	ExpectContainsCell(1, 2, neighbours);
	ExpectContainsCell(0, 2, neighbours);
	ExpectContainsCell(0, 1, neighbours);
}

TEST(ContinuationAlgTest, GetUnvisitedNeighboursBottomLeftCorner)
{
	Rectangle bounds(-2.0, 2.0, -2.0, 2.0);
	Grid grid(bounds, 1.0);

	ContinuationAlgorithm alg(&grid, NULL, NULL);
	Cell *targetCell = grid.GetCell(0, 0);

	std::list<Cell *> neighbours = alg.GetUnvisitedNeighbourCells(targetCell);

	EXPECT_EQ(3, neighbours.size());
	ExpectContainsCell(1, 0, neighbours);
	ExpectContainsCell(1, 1, neighbours);
	ExpectContainsCell(0, 1, neighbours);
}

TEST(ContinuationAlgTest, GetUnvisitedNeighboursTopRightCorner)
{
	Rectangle bounds(-2.0, 2.0, -2.0, 2.0);
	Grid grid(bounds, 1.0);

	ContinuationAlgorithm alg(&grid, NULL, NULL);
	Cell *targetCell = grid.GetCell(3, 3);

	std::list<Cell *> neighbours = alg.GetUnvisitedNeighbourCells(targetCell);

	EXPECT_EQ(3, neighbours.size());
	ExpectContainsCell(3, 2, neighbours);
	ExpectContainsCell(2, 2, neighbours);
	ExpectContainsCell(2, 3, neighbours);
}

TEST(ContinuationAlgTest, GetSurfaceCells)
{
	Rectangle bounds(-10.0, 10.0, -10.0, 10.0);
	Grid grid(bounds, 1.0);

	Point2D location(0.0, 0.0);
	double radius = 5.0;
	double isoValue = 0.5;
	PointPrimitive primitive(location, radius, isoValue);

	std::list<Primitive *> primitives;
	primitives.push_back(&primitive);

	SummationBlend blend(primitives, isoValue);

	ContinuationAlgorithm alg(&grid, &primitive, &blend);

	std::list<Cell *> surfaceCells = alg.GetSurfaceCells();

	EXPECT_EQ(20, surfaceCells.size());

	ExpectContainsCell(10, 7, surfaceCells);
	ExpectContainsCell(11, 7, surfaceCells);
	ExpectContainsCell(11, 8, surfaceCells);
	ExpectContainsCell(12, 8, surfaceCells);
	ExpectContainsCell(12, 9, surfaceCells);
	ExpectContainsCell(12, 10, surfaceCells);
	ExpectContainsCell(12, 11, surfaceCells);
	ExpectContainsCell(11, 11, surfaceCells);
	ExpectContainsCell(11, 12, surfaceCells);
	ExpectContainsCell(10, 12, surfaceCells);
	ExpectContainsCell(9, 12, surfaceCells);
	ExpectContainsCell(8, 12, surfaceCells);
	ExpectContainsCell(8, 11, surfaceCells);
	ExpectContainsCell(7, 11, surfaceCells);
	ExpectContainsCell(7, 10, surfaceCells);
	ExpectContainsCell(7, 9, surfaceCells);
	ExpectContainsCell(7, 8, surfaceCells);
	ExpectContainsCell(8, 8, surfaceCells);
	ExpectContainsCell(8, 7, surfaceCells);
	ExpectContainsCell(9, 7, surfaceCells);
}

TEST(ContinuationAlgTest, GetSurfaceCellsOffLeftEdge)
{
	Rectangle bounds(-2.0, 10.0, -10.0, 10.0);
	Grid grid(bounds, 1.0);

	Point2D location(0.0, 0.0);
	double radius = 5.0;
	double isoValue = 0.5;
	PointPrimitive primitive(location, radius, isoValue);

	std::list<Primitive *> primitives;
	primitives.push_back(&primitive);

	SummationBlend blend(primitives, isoValue);

	ContinuationAlgorithm alg(&grid, &primitive, &blend);

	std::list<Cell *> surfaceCells = alg.GetSurfaceCells();

	EXPECT_EQ(18, surfaceCells.size());

	ExpectContainsCell(10, 0, surfaceCells);
	ExpectContainsCell(11, 0, surfaceCells);
	ExpectContainsCell(12, 0, surfaceCells);
	ExpectContainsCell(12, 1, surfaceCells);
	ExpectContainsCell(12, 2, surfaceCells);
	ExpectContainsCell(12, 3, surfaceCells);
	ExpectContainsCell(11, 3, surfaceCells);
	ExpectContainsCell(11, 4, surfaceCells);
	ExpectContainsCell(10, 4, surfaceCells);
	ExpectContainsCell(9, 4, surfaceCells);
	ExpectContainsCell(8, 4, surfaceCells);
	ExpectContainsCell(8, 3, surfaceCells);
	ExpectContainsCell(7, 3, surfaceCells);
	ExpectContainsCell(7, 2, surfaceCells);
	ExpectContainsCell(7, 1, surfaceCells);
	ExpectContainsCell(7, 0, surfaceCells);
	ExpectContainsCell(8, 0, surfaceCells);
	ExpectContainsCell(9, 0, surfaceCells);
}

TEST(ContinuationAlgTest, GetSurfaceCellsOffRightEdge)
{
	Rectangle bounds(-10.0, 2.0, -10.0, 10.0);
	Grid grid(bounds, 1.0);

	Point2D location(0.0, 0.0);
	double radius = 5.0;
	double isoValue = 0.5;
	PointPrimitive primitive(location, radius, isoValue);

	std::list<Primitive *> primitives;
	primitives.push_back(&primitive);

	SummationBlend blend(primitives, isoValue);

	ContinuationAlgorithm alg(&grid, &primitive, &blend);

	std::list<Cell *> surfaceCells = alg.GetSurfaceCells();

	EXPECT_EQ(18, surfaceCells.size());

	ExpectContainsCell(10, 7, surfaceCells);
	ExpectContainsCell(11, 7, surfaceCells);
	ExpectContainsCell(11, 8, surfaceCells);
	ExpectContainsCell(12, 8, surfaceCells);
	ExpectContainsCell(12, 9, surfaceCells);
	ExpectContainsCell(12, 10, surfaceCells);
	ExpectContainsCell(12, 11, surfaceCells);
	ExpectContainsCell(11, 11, surfaceCells);
	ExpectContainsCell(10, 11, surfaceCells);
	ExpectContainsCell(9, 11, surfaceCells);
	ExpectContainsCell(8, 11, surfaceCells);
	ExpectContainsCell(7, 11, surfaceCells);
	ExpectContainsCell(7, 10, surfaceCells);
	ExpectContainsCell(7, 9, surfaceCells);
	ExpectContainsCell(7, 8, surfaceCells);
	ExpectContainsCell(8, 8, surfaceCells);
	ExpectContainsCell(8, 7, surfaceCells);
	ExpectContainsCell(9, 7, surfaceCells);
}

TEST(ContinuationAlgTest, GetSurfaceCellsOffTopAndRightEdges)
{
	Rectangle bounds(-10.0, 1.0, -10.0, 1.0);
	Grid grid(bounds, 1.0);

	Point2D location(0.0, 0.0);
	double radius = 5.0;
	double isoValue = 0.5;
	PointPrimitive primitive(location, radius, isoValue);

	std::list<Primitive *> primitives;
	primitives.push_back(&primitive);

	SummationBlend blend(primitives, isoValue);

	ContinuationAlgorithm alg(&grid, &primitive, &blend);

	std::list<Cell *> surfaceCells = alg.GetSurfaceCells();

	EXPECT_EQ(12, surfaceCells.size());

	ExpectContainsCell(10, 7, surfaceCells);
	ExpectContainsCell(10, 8, surfaceCells);
	ExpectContainsCell(10, 9, surfaceCells);
	ExpectContainsCell(10, 10, surfaceCells);
	ExpectContainsCell(9, 10, surfaceCells);
	ExpectContainsCell(8, 10, surfaceCells);
	ExpectContainsCell(7, 10, surfaceCells);
	ExpectContainsCell(7, 9, surfaceCells);
	ExpectContainsCell(7, 8, surfaceCells);
	ExpectContainsCell(8, 8, surfaceCells);
	ExpectContainsCell(8, 7, surfaceCells);
	ExpectContainsCell(9, 7, surfaceCells);
}
