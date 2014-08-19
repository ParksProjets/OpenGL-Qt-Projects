#include "polyhedron.h"

#include "gtest/gtest.h"

#include "point.h"

TEST(EdgeTest, GetEdgePoint)
{
    Polyhedron polyhedron;

    polyhedron.AddVertex(Point(-3, 2, 0));
    polyhedron.AddVertex(Point(-3, 0, 0));
    polyhedron.AddVertex(Point(-1, 0, 0));
    polyhedron.AddVertex(Point(-1, 2, 0));

    polyhedron.AddQuadFace(0, 1, 2, 3);
    
    polyhedron.AddVertex(Point(-1, 2, 0));
    polyhedron.AddVertex(Point(-1, 0, 0));
    polyhedron.AddVertex(Point(1, 0, 0));
    polyhedron.AddVertex(Point(1, 2, 0));

    polyhedron.AddQuadFace(4, 5, 6, 7);
    
    Edge *edge = polyhedron.GetEdge(2);
    
    Vertex* edgePoint = edge->GetEdgePoint();
    Point point = edgePoint->GetPosition();
    
    EXPECT_DOUBLE_EQ(-1, point.GetX());
    EXPECT_DOUBLE_EQ(1, point.GetY());
    EXPECT_DOUBLE_EQ(0, point.GetZ());
}

TEST(EdgeTest, GetEdgePointHole)
{
    Polyhedron polyhedron;

    polyhedron.AddVertex(Point(-3, 2, 0));
    polyhedron.AddVertex(Point(-3, 0, 0));
    polyhedron.AddVertex(Point(-1, 0, 0));
    polyhedron.AddVertex(Point(-1, 4, 0));

    polyhedron.AddQuadFace(0, 1, 2, 3);
    
    Edge *edge = polyhedron.GetEdge(2);
    
    Vertex* edgePoint = edge->GetEdgePoint();
    Point point = edgePoint->GetPosition();
    
    EXPECT_DOUBLE_EQ(-1, point.GetX());
    EXPECT_DOUBLE_EQ(2, point.GetY());
    EXPECT_DOUBLE_EQ(0, point.GetZ());
}

TEST(EdgeTest, EdgePointSetIndex)
{
    Polyhedron polyhedron;

    polyhedron.AddVertex(Point(-3, 2, 0));
    polyhedron.AddVertex(Point(-3, 0, 0));
    polyhedron.AddVertex(Point(-1, 0, 0));
    polyhedron.AddVertex(Point(-1, 4, 0));

    polyhedron.AddQuadFace(0, 1, 2, 3);
    
    Edge *edge = polyhedron.GetEdge(2);
    
    Vertex* edgePoint = edge->GetEdgePoint();
    
    EXPECT_EQ(-1, edgePoint->GetIndex());
    
    int newIndex = 5;
    edgePoint->SetIndex(newIndex);
    EXPECT_EQ(newIndex, edgePoint->GetIndex());
}
