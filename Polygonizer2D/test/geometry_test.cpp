#include "util/geometry.h"

#include "gtest/gtest.h"

TEST(GeometryPoint2dTest, DistanceTo)
{
	Point2D point1(0.0, 0.0);
	Point2D point2(2.0, 2.0);

	double expectedDistance = 2.8284271247461903;

	EXPECT_DOUBLE_EQ(point1.DistanceTo(point2), expectedDistance);
	EXPECT_DOUBLE_EQ(point2.DistanceTo(point1), expectedDistance);
}

TEST(GeometryRectangleTest, GetWidth)
{
	Rectangle rectangle(5.0, 10.0, 3.0, 7.0);

	EXPECT_DOUBLE_EQ(5.0, rectangle.GetWidth());
}

TEST(GeometryRectangleTest, GetHeight)
{
	Rectangle rectangle(5.0, 10.0, 3.0, 7.0);

	EXPECT_DOUBLE_EQ(4.0, rectangle.GetHeight());
}

TEST(GeometryRectangleTest, GetCorners)
{
	Rectangle rectangle(-1.0, 1.0, -1.0, 1.0);

	Point2D bottomLeft = rectangle.GetBottomLeft();
	EXPECT_DOUBLE_EQ(-1.0, bottomLeft.x());
	EXPECT_DOUBLE_EQ(-1.0, bottomLeft.y());

	Point2D bottomRight = rectangle.GetBottomRight();
	EXPECT_DOUBLE_EQ(1.0, bottomRight.x());
	EXPECT_DOUBLE_EQ(-1.0, bottomRight.y());

	Point2D topLeft = rectangle.GetTopLeft();
	EXPECT_DOUBLE_EQ(-1.0, topLeft.x());
	EXPECT_DOUBLE_EQ(1.0, topLeft.y());

	Point2D topRight = rectangle.GetTopRight();
	EXPECT_DOUBLE_EQ(1.0, topRight.x());
	EXPECT_DOUBLE_EQ(1.0, topRight.y());
}

TEST(GeometryRectangleTest, ContainsTrue)
{
	Rectangle rectangle(-1.0, 1.0, -1.0, 1.0);

	EXPECT_TRUE(rectangle.Contains(Point2D(0.0, 0.0)));
}

TEST(GeometryRectangleTest, ContainsFalse)
{
	Rectangle rectangle(-1.0, 1.0, -1.0, 1.0);

	EXPECT_FALSE(rectangle.Contains(Point2D(0.0, -1.1)));
}
