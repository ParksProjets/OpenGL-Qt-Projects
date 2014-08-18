#include "rendering/edge.h"

#include "gtest/gtest.h"

#include "rendering/blending.h"
#include "rendering/primitives.h"

TEST(EdgeTest, GetAngleHorizontal)
{
	Point2D point1(1.0, 1.0);
	Point2D point2(4.0, 1.0);

	Edge edge(point1, point2);
	EXPECT_DOUBLE_EQ(0.0, edge.GetAngle());
}

TEST(EdgeTest, GetIntersectionPoint)
{
	Point2D point1(1.0, 1.0);
	Point2D point2(4.0, 1.0);

	Edge edge(point1, point2);

	Point2D primitiveLocation(0.0, 0.0);
	double radius = 5.0;
	double isoValue = 0.5;
	PointPrimitive primitive(primitiveLocation, radius, isoValue);

	std::list<Primitive *> primitives;
	primitives.push_back(&primitive);

	SummationBlend blend(primitives, isoValue);

	Point2D intersection = edge.GetIntersectionPoint(&blend);

	double delta = 0.000000001;
	EXPECT_NEAR(2.273965344, intersection.x(), delta);
	EXPECT_NEAR(1.0, intersection.y(), delta);
}
