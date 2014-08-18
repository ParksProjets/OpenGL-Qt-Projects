#include "rendering/polygon.h"

#include <GL/gl.h>

typedef std::list<Point2D>::iterator PointIterator;

Polygon::Polygon(std::list<Point2D> surfacePoints) :
	surfacePoints(surfacePoints)
{
}

void Polygon::Draw()
{
	glBegin(GL_POLYGON);

	for (PointIterator it = surfacePoints.begin();
			it != surfacePoints.end(); it++) {
		Point2D point = *it;

		glVertex2f(point.x(), point.y());
	}

	glEnd();
}

void Polygon::UpdateSurface(std::list<Point2D> newSurfacePoints)
{
	surfacePoints = newSurfacePoints;
}
