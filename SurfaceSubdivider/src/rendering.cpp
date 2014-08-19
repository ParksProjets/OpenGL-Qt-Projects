#include "rendering.h"

#include <cstddef>

#include <GL/gl.h>

#include "defaults.h"
#include "point.h"

void glVertex3fp(Point point)
{
    glVertex3f(point.GetX(), point.GetY(), point.GetZ());
}

void Renderer::Render(Polyhedron* polyhedron)
{
    RenderFaces(polyhedron);
    RenderOutline(polyhedron);
}

void Renderer::RenderFaces(Polyhedron* polyhedron)
{
    glColor3fv(defaults::OBJECT_COLOUR);
    
    for (std::size_t i = 0; i < polyhedron->NumFaces(); i++) {
        Face *face = polyhedron->GetFace(i);
        
        glBegin(GL_POLYGON);
        
        Point norm = face->GetNorm();
        glNormal3f(norm.GetX(), norm.GetY(), norm.GetZ());
        
        for (std::size_t j = 0; j < face->NumVertices(); j++) {
            Vertex *vertex = face->GetVertex(j);
            Point position = vertex->GetPosition();

            glVertex3fp(position);
        }
        
        glEnd();
    }
}

void Renderer::RenderOutline(Polyhedron* polyhedron)
{
    glColor3fv(defaults::OUTLINE_COLOUR);
    glLineWidth(defaults::OUTLINE_THICKNESS);
    
    for (size_t i = 0; i < polyhedron->NumEdges(); i++) {
        Edge *edge = polyhedron->GetEdge(i);
        
        glBegin(GL_LINES);
        glVertex3fp(edge->GetStartLocation());
        glVertex3fp(edge->GetEndLocation());
        glEnd();
    }
}
