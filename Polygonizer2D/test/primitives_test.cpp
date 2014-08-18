#include "rendering/primitives.h"

#include "gtest/gtest.h"

TEST(SoftObjectsFalloffFilter, Basic)
{
	SoftObjectsFallOffFilter filter(5.0);

	EXPECT_DOUBLE_EQ(0.655424, filter.GetValue(2.0));
}

TEST(SoftObjectsFalloffFilter, Limits)
{
	SoftObjectsFallOffFilter filter(5.0);

	EXPECT_DOUBLE_EQ(0.0, filter.GetValue(5.0));
	EXPECT_DOUBLE_EQ(1.0, filter.GetValue(0.0));
}

TEST(SoftObjectsFalloffFilter, OutsideMaxDistance)
{
	SoftObjectsFallOffFilter filter(5.0);

	EXPECT_DOUBLE_EQ(0.0, filter.GetValue(6.0));
}

TEST(PointPrimitive, OutsidePoint)
{
	PointPrimitive primitive(Point2D(1.0, 1.0), 5.0, 0.5);
	Point2D testPoint(6.0, 5.0);

	double fieldValue = primitive.GetFieldValue(testPoint);
	double isoValue = primitive.GetIsoValue();

	EXPECT_TRUE(fieldValue < isoValue);
}

TEST(PointPrimitive, InsidePoint)
{
	PointPrimitive primitive(Point2D(1.0, 1.0), 5.0, 0.5);
	Point2D testPoint(1.5, 1.5);

	double fieldValue = primitive.GetFieldValue(testPoint);
	double isoValue = primitive.GetIsoValue();

	EXPECT_TRUE(fieldValue > isoValue);
}
