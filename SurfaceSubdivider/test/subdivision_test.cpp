#include "subdivision.h"

#include "gtest/gtest.h"

#include "polyhedron.h"

TEST(SubdivisionTest, SubdivideLevel1)
{
    CatmullClarkSubdivider subdivider;
    
    Polyhedron *level1Polyhedron = subdivider.Subdivide();
    
    EXPECT_EQ(26, level1Polyhedron->NumVertices());
    EXPECT_EQ(48, level1Polyhedron->NumEdges());
    EXPECT_EQ(24, level1Polyhedron->NumFaces());
}
