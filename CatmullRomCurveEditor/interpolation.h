#ifndef INTERPOLATION_H
#define INTERPOLATION_H

#include <QGenericMatrix>
#include <QVector>
#include <QVector3D>

class CatmullRomInterpolation
{
public:
    CatmullRomInterpolation(QVector<QVector3D> &points);

    QVector<QVector3D> interpolate(
            unsigned int numInterpolationPoints);
    QVector<QVector3D> interpolateSegment(
            unsigned int firstPointIndex, unsigned int numInterpolationPoints);

    size_t getNumPoints(size_t subdivisionLevel);

protected:
    QVector<QVector3D> controlPoints;
    QGenericMatrix<4, 4, qreal> basisMatrix;

private:
    QGenericMatrix<4, 1, qreal> buildParameterVector(float t);
    QGenericMatrix<4, 4, qreal> buildBasisMatrix();
    QGenericMatrix<3, 4, qreal> buildPointMatrix(unsigned int index);
};

#endif // INTERPOLATION_H
