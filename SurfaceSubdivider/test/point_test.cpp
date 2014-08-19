#include "point.h"

#include "gtest/gtest.h"

TEST(PointTest, ConstructEmptyGetValues)
{
    Point point;

    EXPECT_DOUBLE_EQ(0, point.GetX());
    EXPECT_DOUBLE_EQ(0, point.GetY());
    EXPECT_DOUBLE_EQ(0, point.GetZ());
}

TEST(PointTest, DistanceTo)
{
    Point point1(0.0, 0.0, 1.0);
    Point point2(2.0, 2.0, 1.0);

    double expectedDistance = 2.8284271247461903;

    EXPECT_DOUBLE_EQ(point1.DistanceTo(point2), expectedDistance);
    EXPECT_DOUBLE_EQ(point2.DistanceTo(point1), expectedDistance);
}

TEST(PointTest, CrossProduct)
{
    Point point1(3.0, 2.0, -2.0);
    Point point2(1.0, 0.0, -5.0);
    
    Point crossProduct = point1.CrossProduct(point2);
    
    EXPECT_DOUBLE_EQ(-10, crossProduct.GetX());
    EXPECT_DOUBLE_EQ(13, crossProduct.GetY());
    EXPECT_DOUBLE_EQ(-2, crossProduct.GetZ());
}

TEST(PointTest, Length)
{
    Point point1(1.0, 0.0, 0.0);
    EXPECT_DOUBLE_EQ(1.0, point1.Length());

    Point point2(-5.0, 4.0, 2.0);
    double absError = 0.000000001;
    EXPECT_NEAR(6.708203932, point2.Length(), absError);
}

TEST(PointTest, NormalizeZeroPoint)
{
    Point zeroPoint;
    zeroPoint.Normalize();

    EXPECT_DOUBLE_EQ(0.0, zeroPoint.Length());
    EXPECT_DOUBLE_EQ(0.0, zeroPoint.GetX());
    EXPECT_DOUBLE_EQ(0.0, zeroPoint.GetY());
    EXPECT_DOUBLE_EQ(0.0, zeroPoint.GetZ());
}

TEST(PointTest, NormalizeUnitPoint)
{
    Point unitPoint(0.0, 1.0, 0.0);
    unitPoint.Normalize();

    EXPECT_DOUBLE_EQ(1.0, unitPoint.Length());
    EXPECT_DOUBLE_EQ(0.0, unitPoint.GetX());
    EXPECT_DOUBLE_EQ(1.0, unitPoint.GetY());
    EXPECT_DOUBLE_EQ(0.0, unitPoint.GetZ());
}

TEST(PointTest, NormalizePoint)
{
    Point point(2.0, -2.0, 5.0);
    point.Normalize();

    double absError = 0.000000001;
    EXPECT_DOUBLE_EQ(1.0, point.Length());
    EXPECT_NEAR(0.3481553119, point.GetX(), absError);
    EXPECT_NEAR(-0.3481553119, point.GetY(), absError);
    EXPECT_NEAR(0.8703882798, point.GetZ(), absError);
}

TEST(PointTest, ReversePoint)
{
    Point point(2.0, -2.0, 5.0);
    point.Reverse();

    EXPECT_DOUBLE_EQ(-2.0, point.GetX());
    EXPECT_DOUBLE_EQ(2.0, point.GetY());
    EXPECT_DOUBLE_EQ(-5.0, point.GetZ());
}

TEST(PointTest, Add)
{
    Point point1(1.0, 2.0, 3.0);
    Point point2(4.0, 5.0, 6.0);

    Point sumPoint = point1 + point2;

    EXPECT_DOUBLE_EQ(5.0, sumPoint.GetX());
    EXPECT_DOUBLE_EQ(7.0, sumPoint.GetY());
    EXPECT_DOUBLE_EQ(9.0, sumPoint.GetZ());
}

TEST(PointTest, Subtract)
{
    Point point1(1.0, 5.0, 6.0);
    Point point2(4.0, 1.0, 6.0);

    Point diffPoint = point1 - point2;

    EXPECT_DOUBLE_EQ(-3.0, diffPoint.GetX());
    EXPECT_DOUBLE_EQ(4.0, diffPoint.GetY());
    EXPECT_DOUBLE_EQ(0.0, diffPoint.GetZ());
}

TEST(PointTest, MultiplyConstantRight)
{
    Point point1(1.0, 2.0, 3.0);

    Point prodPoint = point1 * 2.5;

    EXPECT_DOUBLE_EQ(2.5, prodPoint.GetX());
    EXPECT_DOUBLE_EQ(5.0, prodPoint.GetY());
    EXPECT_DOUBLE_EQ(7.5, prodPoint.GetZ());
}

TEST(PointTest, MultiplyConstantLeft)
{
    Point point1(1.0, 2.0, 3.0);

    Point prodPoint = 2.5 * point1;

    EXPECT_DOUBLE_EQ(2.5, prodPoint.GetX());
    EXPECT_DOUBLE_EQ(5.0, prodPoint.GetY());
    EXPECT_DOUBLE_EQ(7.5, prodPoint.GetZ());
}

TEST(PointTest, DivideConstant)
{
    Point point(1.0, 2.0, 3.0);
    
    Point scaled = point / 2.0;
    
    EXPECT_DOUBLE_EQ(0.5, scaled.GetX());
    EXPECT_DOUBLE_EQ(1.0, scaled.GetY());
    EXPECT_DOUBLE_EQ(1.5, scaled.GetZ());
}

TEST(PointTest, MultiplyPoint)
{
    Point point1(-1.0, 2.0, 3.0);
    Point point2(4.0, 5.0, 6.0);

    Point prodPoint = point1 * point2;

    EXPECT_DOUBLE_EQ(-4.0, prodPoint.GetX());
    EXPECT_DOUBLE_EQ(10.0, prodPoint.GetY());
    EXPECT_DOUBLE_EQ(18.0, prodPoint.GetZ());
}

TEST(PointTest, PlusEquals)
{
    Point point1(-1.0, 2.0, 3.0);
    Point point2(4.0, 5.0, 6.0);

    point1 += point2;

    EXPECT_DOUBLE_EQ(3.0, point1.GetX());
    EXPECT_DOUBLE_EQ(7.0, point1.GetY());
    EXPECT_DOUBLE_EQ(9.0, point1.GetZ());
}
