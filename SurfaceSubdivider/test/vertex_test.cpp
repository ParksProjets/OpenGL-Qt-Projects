#include "polyhedron.h"

#include "gtest/gtest.h"

#include "point.h"

TEST(VertexTest, Update)
{
    Polyhedron *polyhedron = new Polyhedron();
    
    for (int x = -1; x <= 1; x+=2) {
        for (int y = -1; y <= 1; y+=2) {
            for (int z = -1; z <= 1; z+=2) {
                polyhedron->AddVertex(Point(x, y, z));
            }
        }
    }
    
    polyhedron->AddQuadFace(0, 1, 3, 2);
    polyhedron->AddQuadFace(6, 7, 5, 4);
    polyhedron->AddQuadFace(4, 5, 1, 0);
    polyhedron->AddQuadFace(2, 3, 7, 6);
    polyhedron->AddQuadFace(0, 2, 6, 4);
    polyhedron->AddQuadFace(5, 7, 3, 1);
    
    Vertex *target = polyhedron->GetVertex(7);
    Point targetPoint = target->GetPosition();
    EXPECT_DOUBLE_EQ(1, targetPoint.GetX());
    EXPECT_DOUBLE_EQ(1, targetPoint.GetY());
    EXPECT_DOUBLE_EQ(1, targetPoint.GetZ());
    
    Vertex *updated = target->Update();
    Point updatedPoint = updated->GetPosition();
    EXPECT_DOUBLE_EQ(5.0 / 9, updatedPoint.GetX());
    EXPECT_DOUBLE_EQ(5.0 / 9, updatedPoint.GetY());
    EXPECT_DOUBLE_EQ(5.0 / 9, updatedPoint.GetZ());
}
