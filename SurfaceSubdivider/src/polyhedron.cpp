#include "polyhedron.h"

#include <algorithm>
#include <cstddef>

typedef std::vector<Face *>::iterator FaceIterator;
typedef std::vector<Vertex *>::iterator VertexIterator;

template<typename T>
bool VectorContains(std::vector<T *> vector, T *item)
{
    return std::find(vector.begin(), vector.end(), item) != vector.end();
}

Vertex::Vertex(Point position, int index)
    : position(position), index(index), newVertex(NULL)
{
}

Point Vertex::GetPosition()
{
    return position;
}

int Vertex::GetIndex()
{
    return index;
}

void Vertex::SetIndex(int index)
{
    this->index = index;
}

void Vertex::AddEdge(Edge *edge)
{
    connectedEdges.push_back(edge);
}

void Vertex::AddFace(Face *face)
{
    connectedFaces.push_back(face);
}

bool Vertex::IsConnectedToEdge(Edge* edge)
{
    return VectorContains(connectedEdges, edge);
}

bool Vertex::IsConnectedToFace(Face *face)
{
    return VectorContains(connectedFaces, face);
}

std::vector<Edge*> Vertex::GetConnectedEdges()
{
    return connectedEdges;
}

void Vertex::CalculateFacesAverageNorm()
{
    for (size_t i = 0; i < connectedFaces.size(); i++) {
        Face *face = connectedFaces[i];
        
        facesAverageNorm += face->GetNorm();
    }
    
    facesAverageNorm.Normalize();
}

Point Vertex::GetFacesAverageNorm() {
    return facesAverageNorm;
}

bool Vertex::IsHoleVertex()
{
    return connectedFaces.size() != connectedEdges.size();
}

Vertex *Vertex::Update()
{
    if (newVertex != NULL) {
        return newVertex;
    }
    
    Point facesAverage;
    for (size_t i = 0; i < connectedFaces.size(); i++) {
        facesAverage += connectedFaces[i]->GetFacePoint()->GetPosition();
    }
    
    facesAverage = facesAverage / connectedFaces.size();
    
    Point edgesAverage;
    for (size_t i = 0; i < connectedEdges.size(); i++) {
        edgesAverage += connectedEdges[i]->GetMidpoint();
    }
    
    edgesAverage = edgesAverage / connectedEdges.size();
    
    size_t n = connectedFaces.size();
    
    Point newLocation = (facesAverage + 2 * edgesAverage + 
                            (n - 3) * GetPosition()) / n;
    
    newVertex = new Vertex(newLocation);
    
    return newVertex;
}

Edge::Edge(Vertex *vertex1, Vertex *vertex2)
    : vertex1(vertex1), vertex2(vertex2), edgePoint(NULL)
{
}

Point Edge::GetStartLocation()
{
    return vertex1->GetPosition();
}

Point Edge::GetEndLocation()
{
    return vertex2->GetPosition();
}

Point Edge::GetMidpoint()
{
    return (GetStartLocation() + GetEndLocation()) / 2;
}

void Edge::AddFace(Face *face)
{
    connectedFaces.push_back(face);
}

bool Edge::IsEndPoint(Vertex* vertex)
{
    return vertex1 == vertex || vertex2 == vertex;
}

bool Edge::IsConnectedToFace(Face* face)
{
    return VectorContains(connectedFaces, face);
}

bool Edge::IsHoleEdge()
{
    return connectedFaces.size() == 1;
}

Vertex* Edge::GetEdgePoint()
{
    if (edgePoint == NULL) {
        Point sum;
        sum += vertex1->GetPosition();
        sum += vertex2->GetPosition();

        int count = 2;
        
        if (!IsHoleEdge()) {
            for (size_t i = 0; i < connectedFaces.size(); i++) {
                sum += connectedFaces[i]->GetFacePoint()->GetPosition();
                count++;
            }
        }
        
        edgePoint = new Vertex(sum / count);
    }
    
    return edgePoint;
}

Face::Face()
    : facePoint(NULL)
{
}

void Face::AddEdge(Edge *edge)
{
    edges.push_back(edge);
}

void Face::AddVertex(Vertex *vertex)
{
    vertices.push_back(vertex);
}

bool Face::ContainsVertex(Vertex* vertex)
{
    return VectorContains(vertices, vertex);
}

bool Face::ContainsEdge(Edge *edge)
{
    return VectorContains(edges, edge);
}

std::size_t Face::NumEdges()
{
    return edges.size();
}

Edge *Face::GetEdge(int index)
{
    return edges[index];
}

std::size_t Face::NumVertices()
{
    return vertices.size();
}

Vertex* Face::GetVertex(int index) {
    return vertices[index];
}

void Face::CalculateNorm()
{
    size_t numVertices = vertices.size();
    
    Vertex *previousVertex;
    Vertex *currentVertex;
    Vertex *nextVertex;
    Point norm;
    
    for (size_t i = 0; i < numVertices; i++) {
        currentVertex = vertices[i];
        
        /* Wrap both previous and next indices if necessary */
        previousVertex = vertices[i ? i - 1 : numVertices - 1];
        nextVertex = vertices[(i + 1) % numVertices];
        
        Point directionToCurrent = currentVertex->GetPosition() - 
                previousVertex->GetPosition();
        Point directionToNext = nextVertex->GetPosition() - 
                currentVertex->GetPosition();
        
        norm += directionToCurrent.CrossProduct(directionToNext);
    }
    
    norm.Normalize();
    
    this->norm = norm;
}

Point Face::GetNorm()
{
    return norm;
}

Vertex* Face::GetFacePoint()
{
    if (facePoint == NULL) {
        Point sum;
        
        size_t numVertices = vertices.size();
        
        for (size_t i = 0; i < numVertices; i++) {
            sum += vertices[i]->GetPosition();
        }
        
        facePoint = new Vertex(sum / numVertices);
    }
    
    return facePoint;
}

Polyhedron::~Polyhedron()
{
    for (std::size_t i = 0; i < vertices.size(); i++) {
        delete vertices[i];
    }
}

void Polyhedron::AddVertex(Point position)
{
    vertices.push_back(new Vertex(position, vertices.size()));
}

int Polyhedron::AddVertexIfNew(Vertex *vertex)
{
    if (vertex->GetIndex() == -1) {
        vertex->SetIndex(vertices.size());
        vertices.push_back(vertex);
    }
    
    return vertex->GetIndex();
}

void Polyhedron::AddQuadFace(int index1, int index2, int index3, int index4)
{
    std::vector<Vertex *> vertices;
    vertices.push_back(GetVertex(index1));
    vertices.push_back(GetVertex(index2));
    vertices.push_back(GetVertex(index3));
    vertices.push_back(GetVertex(index4));
    
    Face *face = new Face();

    Vertex *currentVertex;
    Vertex *nextVertex;
    Edge *currentEdge;

    currentVertex = vertices[0];
    for (size_t i = 1; i <= vertices.size(); i++) {
        /* Note we wrap around to 0 with modulus */
        nextVertex = vertices[i % vertices.size()];
        
        nextVertex->AddFace(face);

        currentEdge = AddEdgeByVertices(currentVertex, nextVertex);
        
        currentEdge->AddFace(face);
        face->AddEdge(currentEdge);
        face->AddVertex(nextVertex);
        
        currentVertex = nextVertex;
    }
    
    faces.push_back(face);
}

Edge *Polyhedron::AddEdgeByVertices(Vertex *vertex1, Vertex *vertex2)
{
    std::vector<Edge *> vertex1Edges = vertex1->GetConnectedEdges();
    
    for (size_t i = 0; i < vertex1Edges.size(); i++) {
        Edge *edge = vertex1Edges[i];
        
        if (edge->IsEndPoint(vertex2)) {
            return edge;
        }
    }
    
    return AddEdge(vertex1, vertex2);
}

Edge *Polyhedron::AddEdge(Vertex *vertex1, Vertex *vertex2)
{
    Edge *edge = new Edge(vertex1, vertex2);
    
    vertex1->AddEdge(edge);
    vertex2->AddEdge(edge);
    
    edges.push_back(edge);
    
    return edge;
}

std::size_t Polyhedron::NumVertices()
{
    return vertices.size();
}

std::size_t Polyhedron::NumEdges()
{
    return edges.size();
}

std::size_t Polyhedron::NumFaces()
{
    return faces.size();
}

Vertex *Polyhedron::GetVertex(int index)
{
    return vertices[index];
}

Edge *Polyhedron::GetEdge(int index)
{
    return edges[index];
}

Face *Polyhedron::GetFace(int index)
{
    return faces[index];
}

void Polyhedron::CalculateNorms()
{
    for (FaceIterator it = faces.begin(); it != faces.end(); it++) {
        (*it)->CalculateNorm();
    }
    
    for (VertexIterator it = vertices.begin(); it != vertices.end(); it++) {
        (*it)->CalculateFacesAverageNorm();
    }
}
