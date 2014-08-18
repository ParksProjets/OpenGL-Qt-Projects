#ifndef COORDS_H_
#define COORDS_H_

#include <QPlane3D>

#include "util/geometry.h"

class CoordinateConverter
{
public:
	CoordinateConverter(QPlane3D screenPlane);

	Point2D ConvertScreenToObjectCoords(Point2D screenPoint);

private:
	QPlane3D screenPlane;
};

#endif
