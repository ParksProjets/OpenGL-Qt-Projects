#include "interpolation.h"

#include <cfloat>
#include <cmath>

CatmullRomInterpolation::CatmullRomInterpolation(QVector<QVector3D> &points) :
    controlPoints(points)
{
    basisMatrix = buildBasisMatrix();
}

QVector<QVector3D> CatmullRomInterpolation::interpolate(
        unsigned int numInterpolationPoints)
{
    QVector<QVector3D> interpolatedPoints;

    for (int index = 0; index < controlPoints.size() - 3; index++) {
        interpolatedPoints += interpolateSegment(index,
                                                 numInterpolationPoints);
    }

    return interpolatedPoints;
}

QVector<QVector3D> CatmullRomInterpolation::interpolateSegment(
        unsigned int firstPointIndex, unsigned int numInterpolationPoints)
{
    QVector<QVector3D> interpolatedPoints;

    /* IMPORTANT NOTE: QGenericMatrix is instanciated with number of columns
     * before number of rows.  That is, QGenericMatrix<NumCol, NumRow, Type>.
     */
    QGenericMatrix<3, 4, qreal> pointMatrix = buildPointMatrix(firstPointIndex);
    QGenericMatrix<4, 1, qreal> paramVector;

    for (int i = 0; i < numInterpolationPoints; i++)
    {
        float t = (float) i / numInterpolationPoints;

        paramVector = buildParameterVector(t);
        QGenericMatrix<3, 1, qreal> result = paramVector * basisMatrix * pointMatrix;
        interpolatedPoints.append(QVector3D(result(0, 0), result(0, 1), result(0, 2)));
    }

    return interpolatedPoints;
}

QGenericMatrix<4, 1, qreal> CatmullRomInterpolation::buildParameterVector(
        float t)
{
    qreal values[] = { 1, t, pow(t, 2), pow(t, 3) };
    return QGenericMatrix<4, 1, qreal>(values);
}

QGenericMatrix<4, 4, qreal> CatmullRomInterpolation::buildBasisMatrix()
{
   qreal values[] = { 0.0, 1.0, 0.0, 0.0,
                      -0.5, 0.0, 0.5, 0.0,
                      1.0, -2.5, 2.0, -0.5,
                      -0.5, 1.5, -1.5, 0.5 };
   return QGenericMatrix<4, 4, qreal>(values);
}

QGenericMatrix<3, 4, qreal> CatmullRomInterpolation::buildPointMatrix(
        unsigned int index)
{
    QGenericMatrix<3, 4, qreal> pointMatrix;

    /* Interpolate using the previous point before index and the next 2. */
    for (int i = 0; i < 4; i++)
    {
        QVector3D point = controlPoints[index + i];
        pointMatrix(i, 0) = point.x();
        pointMatrix(i, 1) = point.y();
        pointMatrix(i, 2) = point.z();
    }

    return pointMatrix;
}

size_t CatmullRomInterpolation::getNumPoints(size_t subdivisionLevel)
{
    return (controlPoints.size() - 3) * pow(2, subdivisionLevel) + 1;
}
