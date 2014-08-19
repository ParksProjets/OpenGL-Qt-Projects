#ifndef SUBDIVISION_H
#define	SUBDIVISION_H

#include <cstddef>
#include <vector>

#include "polyhedron.h"

/**
 * Implements the Catmull-Clarke surface subdivision algorithm.
 * 
 * See: http://en.wikipedia.org/wiki/Catmull%E2%80%93Clark_subdivision_surface
 * 
 * The following code was also useful in understanding the details of 
 * the algorithm:
 * http://rosettacode.org/wiki/Catmull%E2%80%93Clark_subdivision_surface/C
 */
class CatmullClarkSubdivider
{
public:
    /**
     * Creates a cube as the starting polyhedron.
     */
    CatmullClarkSubdivider();

    /**
     * Subdivide the current polyhedron and return the result.
     */
    Polyhedron *Subdivide();
    
    /**
     * Undo subdivision, reverting back to the previous polyhedron.
     */
    Polyhedron *Undivide();

    /**
     * Returns a pointer to the polyhedron at the current level of 
     * subdivision.
     */
    Polyhedron *GetCurrentPolyhedron();    
    
private:
    std::vector<Polyhedron *> polyhedrons;
    std::size_t subdivisionLevel;

    /**
     * Performs the actual subdivision on the specified polyhedron,
     * and returns the result.
     */
    Polyhedron *DoSubdivide(Polyhedron *polyhedron);
    
    void AddFace(Polyhedron *newPolyhedron, Polyhedron *oldPolyhedron, 
                    Face *oldFace, int vertexIndex);
    
    /**
     * Creates the starting polyhedron, which is a cube.
     */
    Polyhedron *CreateCube();
};

#endif
