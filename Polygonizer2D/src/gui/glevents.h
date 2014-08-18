#ifndef GLEVENTS_H_
#define GLEVENTS_H_

#include "util/geometry.h"

class MouseEvent
{
public:
	MouseEvent(Point2D point);

	/**
	 * Position in object coordinates.
	 */
	Point2D Position();

	double x();
	double y();

private:
	Point2D position;
};

class GLEventHandler
{
public:
	virtual ~GLEventHandler() {};
	virtual void HandleMousePress(MouseEvent *event) = 0;
	virtual void HandleMouseRelease(MouseEvent *event) = 0;
	virtual void HandleMouseMove(MouseEvent *event) = 0;
};

#endif
