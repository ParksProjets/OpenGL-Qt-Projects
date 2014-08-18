#include "gui/coords.h"

#include <GL/glu.h>
#include <QRay3D>
#include <QVector3D>

CoordinateConverter::CoordinateConverter(QPlane3D screenPlane) :
	screenPlane(screenPlane)
{
}

Point2D CoordinateConverter::ConvertScreenToObjectCoords(Point2D screenPoint)
{
    GLdouble nearPlaneX;
    GLdouble nearPlaneY;
    GLdouble nearPlaneZ;
    GLdouble farPlaneX;
    GLdouble farPlaneY;
    GLdouble farPlaneZ;

    GLdouble modelview[16];
    GLdouble projection[16];
    GLint viewport[4];

    glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
    glGetDoublev(GL_PROJECTION_MATRIX, projection);
    glGetIntegerv(GL_VIEWPORT, viewport);

    GLdouble height = viewport[3];
    GLdouble correctedY = height - screenPoint.y();

    gluUnProject(screenPoint.x(), correctedY, 0.0,
                 modelview, projection, viewport,
                 &nearPlaneX, &nearPlaneY, &nearPlaneZ);

    gluUnProject(screenPoint.x(), correctedY, 1.0,
                 modelview, projection, viewport,
                 &farPlaneX, &farPlaneY, &farPlaneZ);

    QVector3D nearPlanePoint(nearPlaneX, nearPlaneY, nearPlaneZ);
    QVector3D farPlanePoint(farPlaneX, farPlaneY, farPlaneZ);

    QRay3D ray(nearPlanePoint, farPlanePoint - nearPlanePoint);

    qreal t = screenPlane.intersection(ray);

    QVector3D point;
    if (qIsNaN(t)) {
        qWarning("No intersection found.");
    } else {
        point = ray.point(t);
    }

    return Point2D(point.x(), point.y());
}
