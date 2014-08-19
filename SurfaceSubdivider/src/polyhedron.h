#ifndef POLYHEDRON_H
#define	POLYHEDRON_H

#include <vector>

#include "point.h"

class Edge;
class Face;

/**
 * A vertex in a polyhedron.
 */
class Vertex
{
public:
    /**
     * Creates a new vertex at the specified position.  Specify the index 
     * to mark this vertex as being part of a polyhedron (at that index).
     */
    Vertex(Point position, int index = -1);
    
    /**
     * Returns the position of the vertex.
     */
    Point GetPosition();

    /**
     * Returns the index of this vertex in the polyhedron it is part of.
     * It will be -1 if this vertex is not part of a polyhedron.
     */
    int GetIndex();
    
    /**
     * Sets the index to a new value.
     */
    void SetIndex(int index);
    
    /**
     * Remember an edge which has this vertex as one of its endpoints.
     */
    void AddEdge(Edge *edge);
    
    /**
     * Remember a face which contains this vertex.
     */
    void AddFace(Face *face);
    
    /**
     * Returns true if this vertex is connected to the specified edge.
     */
    bool IsConnectedToEdge(Edge *edge);

    /**
     * Returns true if this vertex is connected to the specified face.
     */
    bool IsConnectedToFace(Face *face);
    
    /**
     Returns all edges that this vertex is part of.
     */
    std::vector<Edge *> GetConnectedEdges();
    
    /**
     * Average the norms of the connected faces.  The value can be retrieved
     * with GetFacesAverageNorm().
     */
    void CalculateFacesAverageNorm();
    
    /**
     * Returns the average norm of the connected faces if 
     * CalculateFacesAverageNorm has already been called.  
     * Otherwise returns the origin.
     */
    Point GetFacesAverageNorm();

    /**
     * Returns true if this vertex is on the border of a whole in the
     * polygon.
     */
    bool IsHoleVertex();
    
    /**
     * Calculate this vertex's new location after subdivision.
     */
    Vertex *Update();
    
private:
    Point position;
    bool isPartOfPolygon;
    std::vector<Edge *> connectedEdges;
    std::vector<Face *> connectedFaces;
    int index;
    Point facesAverageNorm;
    Vertex *newVertex;
};


/**
 * An edge in a polyhedron.
 */
class Edge
{
public:
    /**
     * Creates a new edge with the endpoints at the provided vertices.
     */
    Edge(Vertex *vertex1, Vertex *vertex2);
    
    /**
     * Returns the location of the first vertex in this edge.
     */
    Point GetStartLocation();
    
    /**
     * Returns the location of the second vertex in this edge.
     */
    Point GetEndLocation();
    
    /**
     * Returns the point at the middle between the two ends of the edge.
     */
    Point GetMidpoint();
    
    /**
     * Remember a face which is connected to this edge.
     */
    void AddFace(Face *face);
    
    /**
     Returns true if the specified vertex is one of the endpoints of 
     this edge.
     */
    bool IsEndPoint(Vertex *vertex);

    /**
     * Returns true if this edge is part of the specified face.
     */
    bool IsConnectedToFace(Face *face);
    
    /**
     * Returns true if the edge is on the boundary of a whole in the 
     * polyhedron.
     */
    bool IsHoleEdge();
    
    /**
     * Returns the average of the two neighbouring face points and the
     * two original end points.
     */
    Vertex *GetEdgePoint();
    
private:
    Vertex *vertex1;
    Vertex *vertex2;
    std::vector<Face *> connectedFaces;
    Vertex *edgePoint;
};


/**
 * A face of a polyhedron.
 */
class Face
{
public:
    /**
     * Creates a new face.  At first no data is associated with it.
     */
    Face();
    
    /**
     * Remember an edge in this face.
     */
    void AddEdge(Edge *edge);
    
    /**
     * Remember a vertex in this face.
     */
    void AddVertex(Vertex *vertex);
    
    /**
     Returns true if the specified vertex is part of this face.
     */
    bool ContainsVertex(Vertex *vertex);

    /**
     Returns true if the specified edge is part of this face.
     */
    bool ContainsEdge(Edge *edge);

    /**
     * Returns the numbers of edges that are a part of this face.
     */
    std::size_t NumEdges();
    
    /**
     * Returns the edge that was added at the specified index.
     */
    Edge *GetEdge(int index);
    
    /**
     * Returns the number of vertices that are part of this face.
     */
    std::size_t NumVertices();
    
    /**
     * Returns the vertex which was added at the specified index.
     */
    Vertex *GetVertex(int index);
    
    /**
     * Calculates the normal for this face.  The value can afterwards
     * be retrieved with GetNorm();
     */
    void CalculateNorm();
    
    /**
     * Returns the normal to this face if CalculateNorm has already been
     * called.  Otherwise returns the origin.
     */
    Point GetNorm();
    
    /**
     * Returns the average of all points in the face.
     */
    Vertex *GetFacePoint();
    
private:
    std::vector<Vertex *> vertices;
    std::vector<Edge *> edges;
    Point norm;
    Vertex *facePoint;
};


/**
 * A polyhedron is a solid in three dimensions with flat faces, straight
 * edges and sharp corners or vertices.
 */
class Polyhedron
{
public:
    /**
     * Destructor which cleans up dynamic memory allocations.
     */
    ~Polyhedron();

    /**
     * Adds a vertex to the polyhedron by specifying its location in space.
     */
    void AddVertex(Point position);
    
    /**
     * Adds an existing vertex to this polyhedron.  Returns its index.  If
     * the vertex is already part of a polyhedron, it is not added, but
     * the index is still returned.
     */
    int AddVertexIfNew(Vertex *vertex);

    /**
     * Adds a quadrilateral-shaped face to the polygon defined by the four
     * specified vertex indices.  These indices are for the order in which
     * the vertices we added via "AddVertex".
     */
    void AddQuadFace(int index1, int index2, int index3, int index4);
    
    /**
     * Creates an edge between the specified vertices, and returns a 
     * reference to it.
     */
    Edge *AddEdge(Vertex *vertex1, Vertex *vertex2);
    
    /**
     * Returns the number of vertices in the polyhedron.
     */
    std::size_t NumVertices();

    /**
     * Returns the number of edges in the polyhedron.
     */
    std::size_t NumEdges();
    
    /**
     * Returns the number of faces in the polyhedron.
     */
    std::size_t NumFaces();
    
    /**
     * Returns the vertex that was added at the specified index.
     */
    Vertex *GetVertex(int index);

    /**
     * Returns the edge that was added at the specified index.
     */
    Edge *GetEdge(int index);
    
    /**
     * Returns the face that was added at the specified index.
     */
    Face *GetFace(int index);
    
    /**
     Calculate normals for faces of this polyhedron.
     */
    void CalculateNorms();
    
private:
    std::vector<Edge *> edges;
    std::vector<Vertex *> vertices;
    std::vector<Face *> faces;
    
    Edge *AddEdgeByVertices(Vertex *vertex1, Vertex *vertex2);
};

#endif
