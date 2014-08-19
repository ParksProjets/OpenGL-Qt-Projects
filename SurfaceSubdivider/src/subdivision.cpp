#include "subdivision.h"

#include "point.h"

CatmullClarkSubdivider::CatmullClarkSubdivider()
    : subdivisionLevel(0)
{
    polyhedrons.push_back(CreateCube());
}

Polyhedron *CatmullClarkSubdivider::Subdivide()
{
    subdivisionLevel++;
    
    while (subdivisionLevel >= polyhedrons.size()) {
        polyhedrons.push_back(DoSubdivide(polyhedrons.back()));
    }
    
    return GetCurrentPolyhedron();
}

Polyhedron *CatmullClarkSubdivider::Undivide()
{
    /* Do nothing if already at subidivision level 0. */
    if (subdivisionLevel > 0) {
        subdivisionLevel--;
    }

    return GetCurrentPolyhedron();
}

Polyhedron* CatmullClarkSubdivider::GetCurrentPolyhedron() {
    return polyhedrons[subdivisionLevel];
}

Polyhedron *CatmullClarkSubdivider::DoSubdivide(Polyhedron* polyhedron)
{
    Polyhedron *newPolyhedron = new Polyhedron();
    
    for (size_t i = 0; i < polyhedron->NumFaces(); i++) {
        Face *face = polyhedron->GetFace(i);
    
        for (size_t j = 0; j < face->NumVertices(); j++) {
            AddFace(newPolyhedron, polyhedron, face, j);
        }
    }
    
    newPolyhedron->CalculateNorms();
    
    return newPolyhedron;
}

void CatmullClarkSubdivider::AddFace(Polyhedron* newPolyhedron, 
        Polyhedron* oldPolyhedron, Face *oldFace, int vertexIndex)
{
    Vertex *vertex = oldFace->GetVertex(vertexIndex);
    
    int index1 = newPolyhedron->AddVertexIfNew(vertex->Update());
    int index2 = newPolyhedron->AddVertexIfNew(
        oldFace->GetEdge((vertexIndex + 1) % oldFace->NumEdges())->GetEdgePoint());
    int index3 = newPolyhedron->AddVertexIfNew(oldFace->GetFacePoint());
    int index4 = newPolyhedron->AddVertexIfNew(oldFace->GetEdge(vertexIndex)->GetEdgePoint());

    newPolyhedron->AddQuadFace(index1, index2, index3, index4);
}


Polyhedron *CatmullClarkSubdivider::CreateCube()
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
    
    return polyhedron;
}
