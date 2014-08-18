#include "rendering/cell.h"

#include "gtest/gtest.h"

#include <list>

#include "rendering/blending.h"
#include "rendering/edge.h"
#include "rendering/grid.h"
#include "rendering/primitives.h"
#include "util/geometry.h"

TEST(CellTest, GetIntersectingEdges)
{
	Rectangle bounds(-10.0, 10.0, -10.0, 10.0);
	Grid grid(bounds, 1.0);

	Point2D location(0.0, 0.0);
	double radius = 5.0;
	double isoValue = 0.5;
	PointPrimitive primitive(location, radius, isoValue);

	Cell *cell = grid.GetCell(10, 7);

	std::list<Primitive *> primitives;
	primitives.push_back(&primitive);

	SummationBlend blend(primitives, isoValue);
	std::list<Edge> intersectingEdges = cell->GetIntersectingEdges(&blend);

	EXPECT_EQ(2, intersectingEdges.size());

	Edge edge1 = intersectingEdges.front();
	Edge edge2 = intersectingEdges.back();

	EXPECT_DOUBLE_EQ(-3.0, edge1.GetPoint1().x());
	EXPECT_DOUBLE_EQ(0.0, edge1.GetPoint1().y());
	EXPECT_DOUBLE_EQ(-2.0, edge1.GetPoint2().x());
	EXPECT_DOUBLE_EQ(0.0, edge1.GetPoint2().y());

	EXPECT_DOUBLE_EQ(-3.0, edge2.GetPoint1().x());
	EXPECT_DOUBLE_EQ(1.0, edge2.GetPoint1().y());
	EXPECT_DOUBLE_EQ(-2.0, edge2.GetPoint2().x());
	EXPECT_DOUBLE_EQ(1.0, edge2.GetPoint2().y());
}
