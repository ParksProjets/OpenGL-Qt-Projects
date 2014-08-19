#ifndef RENDERING_H
#define	RENDERING_H

#include "polyhedron.h"

class Renderer {
public:
    /**
     * Perform rendering operations.
     */
    void Render(Polyhedron *polyhedron);
    
private:
    /**
     * Renders the polyhedron's faces in the colour specified in 
     * defaults.h.
     */
    void RenderFaces(Polyhedron *polyhedron);
    
    /**
     * Renders the outline (edges) of the polyhedron in the
     * colour specified in defaults.h.
     */
    void RenderOutline(Polyhedron *polyhedron);
};

#endif
