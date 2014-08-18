#include "rendering/grid.h"

#include "gtest/gtest.h"

#include "util/geometry.h"

TEST(GridTest, GetContainerCell)
{
	Rectangle bounds(-2.0, 2.0, -1.0, 1.0);
	Grid grid(bounds, 1.0);

	Point2D testPoint(0.2, 0.3);
	Cell *cell = grid.GetContainerCell(testPoint);

	EXPECT_EQ(1, cell->GetRow());
	EXPECT_EQ(2, cell->GetColumn());
}
