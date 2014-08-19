#include "polyhedron.h"

#include "gtest/gtest.h"

#include "point.h"

class PolyhedronTest : public ::testing::Test
{
protected:
    virtual void SetUp()
    {
        polyhedron.AddVertex(Point(-1, -1, 0));
        polyhedron.AddVertex(Point(1, -1, 0));
        polyhedron.AddVertex(Point(1, 1, 0));
        polyhedron.AddVertex(Point(-1, 1, 0));

        polyhedron.AddQuadFace(0, 1, 2, 3);
        
        EXPECT_EQ(4, polyhedron.NumVertices());
        EXPECT_EQ(4, polyhedron.NumEdges());
        EXPECT_EQ(1, polyhedron.NumFaces());
        
        vertex0 = polyhedron.GetVertex(0);
        vertex1 = polyhedron.GetVertex(1);
        vertex2 = polyhedron.GetVertex(2);
        vertex3 = polyhedron.GetVertex(3);

        edge0 = polyhedron.GetEdge(0);
        edge1 = polyhedron.GetEdge(1);
        edge2 = polyhedron.GetEdge(2);
        edge3 = polyhedron.GetEdge(3);

        face0 = polyhedron.GetFace(0);
    }
        
    Polyhedron polyhedron;

    Vertex *vertex0;
    Vertex *vertex1;
    Vertex *vertex2;
    Vertex *vertex3;
    
    Edge *edge0;
    Edge *edge1;
    Edge *edge2;
    Edge *edge3;
    
    Face *face0;
};

TEST_F(PolyhedronTest, VerticesHaveCorrectFaces)
{
    EXPECT_TRUE(vertex0->IsConnectedToFace(face0));
    EXPECT_TRUE(vertex1->IsConnectedToFace(face0));
    EXPECT_TRUE(vertex2->IsConnectedToFace(face0));
    EXPECT_TRUE(vertex3->IsConnectedToFace(face0));
}

TEST_F(PolyhedronTest, Vertex0HasCorrectEdges)
{
    EXPECT_TRUE(vertex0->IsConnectedToEdge(edge0));
    EXPECT_FALSE(vertex0->IsConnectedToEdge(edge1));
    EXPECT_FALSE(vertex0->IsConnectedToEdge(edge2));
    EXPECT_TRUE(vertex0->IsConnectedToEdge(edge3));
}

TEST_F(PolyhedronTest, Vertex1HasCorrectEdges)
{
    EXPECT_TRUE(vertex1->IsConnectedToEdge(edge0));
    EXPECT_TRUE(vertex1->IsConnectedToEdge(edge1));
    EXPECT_FALSE(vertex1->IsConnectedToEdge(edge2));
    EXPECT_FALSE(vertex1->IsConnectedToEdge(edge3));
}

TEST_F(PolyhedronTest, Vertex2HasCorrectEdges)
{
    EXPECT_FALSE(vertex2->IsConnectedToEdge(edge0));
    EXPECT_TRUE(vertex2->IsConnectedToEdge(edge1));
    EXPECT_TRUE(vertex2->IsConnectedToEdge(edge2));
    EXPECT_FALSE(vertex2->IsConnectedToEdge(edge3));
}

TEST_F(PolyhedronTest, Vertex3HasCorrectEdges)
{
    EXPECT_FALSE(vertex3->IsConnectedToEdge(edge0));
    EXPECT_FALSE(vertex3->IsConnectedToEdge(edge1));
    EXPECT_TRUE(vertex3->IsConnectedToEdge(edge2));
    EXPECT_TRUE(vertex3->IsConnectedToEdge(edge3));
}

TEST_F(PolyhedronTest, Edge0HasCorrectVertices)
{
    EXPECT_TRUE(edge0->IsEndPoint(vertex0));
    EXPECT_TRUE(edge0->IsEndPoint(vertex1));
    EXPECT_FALSE(edge0->IsEndPoint(vertex2));
    EXPECT_FALSE(edge0->IsEndPoint(vertex3));
}

TEST_F(PolyhedronTest, Edge1HasCorrectVertices)
{
    EXPECT_FALSE(edge1->IsEndPoint(vertex0));
    EXPECT_TRUE(edge1->IsEndPoint(vertex1));
    EXPECT_TRUE(edge1->IsEndPoint(vertex2));
    EXPECT_FALSE(edge1->IsEndPoint(vertex3));
}

TEST_F(PolyhedronTest, Edge2HasCorrectVertices)
{
    EXPECT_FALSE(edge2->IsEndPoint(vertex0));
    EXPECT_FALSE(edge2->IsEndPoint(vertex1));
    EXPECT_TRUE(edge2->IsEndPoint(vertex2));
    EXPECT_TRUE(edge2->IsEndPoint(vertex3));
}

TEST_F(PolyhedronTest, Edge3HasCorrectVertices)
{
    EXPECT_TRUE(edge3->IsEndPoint(vertex0));
    EXPECT_FALSE(edge3->IsEndPoint(vertex1));
    EXPECT_FALSE(edge3->IsEndPoint(vertex2));
    EXPECT_TRUE(edge3->IsEndPoint(vertex3));
}

TEST_F(PolyhedronTest, EdgesHaveCorrectFace)
{
    EXPECT_TRUE(edge0->IsConnectedToFace(face0));
    EXPECT_TRUE(edge1->IsConnectedToFace(face0));
    EXPECT_TRUE(edge2->IsConnectedToFace(face0));
    EXPECT_TRUE(edge3->IsConnectedToFace(face0));
}

TEST_F(PolyhedronTest, FaceHasCorrectVertices)
{
    EXPECT_TRUE(face0->ContainsVertex(vertex0));
    EXPECT_TRUE(face0->ContainsVertex(vertex1));
    EXPECT_TRUE(face0->ContainsVertex(vertex2));
    EXPECT_TRUE(face0->ContainsVertex(vertex3));
}

TEST_F(PolyhedronTest, FaceHasCorrectEdges)
{
    EXPECT_TRUE(face0->ContainsEdge(edge0));
    EXPECT_TRUE(face0->ContainsEdge(edge1));
    EXPECT_TRUE(face0->ContainsEdge(edge2));
    EXPECT_TRUE(face0->ContainsEdge(edge3));
}
