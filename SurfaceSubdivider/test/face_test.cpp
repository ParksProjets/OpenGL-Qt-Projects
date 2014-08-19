#include "polyhedron.h"

#include "gtest/gtest.h"

#include "point.h"

TEST(FaceTest, GetFacePoint)
{
    Polyhedron polyhedron;

    polyhedron.AddVertex(Point(-2, 0, 0));
    polyhedron.AddVertex(Point(0, 0, 0));
    polyhedron.AddVertex(Point(0, 2, 0));
    polyhedron.AddVertex(Point(-2, 2, 0));

    polyhedron.AddQuadFace(0, 1, 2, 3);
    
    Face *face = polyhedron.GetFace(0);
    Vertex *facePoint = face->GetFacePoint();
    
    Point location = facePoint->GetPosition();
    
    EXPECT_DOUBLE_EQ(-1.0, location.GetX());
    EXPECT_DOUBLE_EQ(1.0, location.GetY());
    EXPECT_DOUBLE_EQ(0.0, location.GetZ());
}

TEST(FaceTest, FacePointSetIndex)
{
    Polyhedron polyhedron;

    polyhedron.AddVertex(Point(-2, 0, 0));
    polyhedron.AddVertex(Point(0, 0, 0));
    polyhedron.AddVertex(Point(0, 2, 0));
    polyhedron.AddVertex(Point(-2, 2, 0));

    polyhedron.AddQuadFace(0, 1, 2, 3);
    
    Face *face = polyhedron.GetFace(0);
    Vertex *facePoint = face->GetFacePoint();
    
    EXPECT_EQ(-1, facePoint->GetIndex());
    
    int newIndex = 5;
    facePoint->SetIndex(newIndex);
    
    facePoint = face->GetFacePoint();
    EXPECT_EQ(newIndex, facePoint->GetIndex());
}
