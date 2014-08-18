#include "gui/glevents.h"

MouseEvent::MouseEvent(Point2D point) :
	position(point)
{
}

Point2D MouseEvent::Position()
{
	return position;
}

double MouseEvent::x()
{
	return position.x();
}

double MouseEvent::y()
{
	return position.y();
}
