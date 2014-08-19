#include "animation.h"
#include "arclength.h"

#include <GL/gl.h>

PathAnimator::PathAnimator(QVector<QVector3D> *pathPoints) :
    pathPoints(pathPoints), pointIndex(0), isRunning(false)
{
}

void PathAnimator::startAnimation()
{
    isRunning = true;
    pointIndex = 0;
}

void PathAnimator::advance()
{
    if (!isRunning)
    {
        return;
    }

    if (pointIndex >= pathPoints->size() - 1)
    {
        isRunning = false;
        return;
    }

    pointIndex++;
}

void PathAnimator::drawMarker()
{
    if (!isRunning)
    {
        return;
    }

    QVector3D currentPoint = getCurrentPoint();

    glColor3f(0.3f, 0.6f, 0.3f);
    glPointSize(12.0f);

    glBegin(GL_POINTS);
    glVertex3d(currentPoint.x(), currentPoint.y(), currentPoint.z());
    glEnd();
}

float PathAnimator::getParametricValue()
{
    return (float) pointIndex / (pathPoints->size() - 1);
}

float PathAnimator::getArclength()
{
    ArclengthTable arclengthTable(pathPoints);
    return arclengthTable.GetArclength(getParametricValue());
}

QVector3D PathAnimator::getCurrentPoint()
{
    return (*pathPoints)[pointIndex];
}
