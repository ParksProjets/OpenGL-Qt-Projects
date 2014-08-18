#include "rendering/blending.h"

#include "gtest/gtest.h"

#include <list>

#include "rendering/primitives.h"

TEST(SummationBlendingTest, TwoPoints)
{
	double isoValue = 0.5;
	double scaleWeight = 1.0;

	PointPrimitive primitive1(Point2D(-1.0, 3.0), 5, isoValue);
	PointPrimitive primitive2(Point2D(5.0, 2.0), 8, isoValue);

	std::list<Primitive *> primitives;
	primitives.push_back(&primitive1);
	primitives.push_back(&primitive2);

	SummationBlend blend(primitives, isoValue, scaleWeight);

	double delta = 0.000000001;
	EXPECT_NEAR(0.87227494, blend.GetGlobalField(Point2D(1.0, 1.0)), delta);
}

TEST(RicciBlendingTest, N1)
{
	double isoValue = 0.5;
	double scaleWeight = 1.0;

	PointPrimitive primitive1(Point2D(-1.0, 3.0), 5, isoValue);
	PointPrimitive primitive2(Point2D(5.0, 2.0), 8, isoValue);

	std::list<Primitive *> primitives;
	primitives.push_back(&primitive1);
	primitives.push_back(&primitive2);

	RicciBlend blend(primitives, isoValue, scaleWeight, 1);

	double delta = 0.000000001;
	EXPECT_NEAR(0.87227494, blend.GetGlobalField(Point2D(1.0, 1.0)), delta);
}

TEST(RicciBlendingTest, N2)
{
	double isoValue = 0.5;
	double scaleWeight = 1.0;

	PointPrimitive primitive1(Point2D(-1.0, 3.0), 5, isoValue);
	PointPrimitive primitive2(Point2D(5.0, 2.0), 8, isoValue);

	std::list<Primitive *> primitives;
	primitives.push_back(&primitive1);
	primitives.push_back(&primitive2);

	RicciBlend blend(primitives, isoValue, scaleWeight, 2);

	double delta = 0.000000001;
	EXPECT_NEAR(0.6193161128, blend.GetGlobalField(Point2D(1.0, 1.0)), delta);
}
