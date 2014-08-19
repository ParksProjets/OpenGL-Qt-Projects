#ifndef ARCLENGTH_H
#define ARCLENGTH_H

#include <QVector>
#include <QVector3D>

float EuclideanDistance(QVector3D point1, QVector3D point2);

class ArclengthTable
{
public:
    ArclengthTable(QVector<QVector3D> *points);
    ~ArclengthTable();

    float GetParametricEntry(float arclength);
    float GetArclength(float parametricEntry);

private:
    QVector<QVector3D> *points;
    int numTableEntries;

    int *indices;
    float *parametricEntries;
    float *arclengths;

    void BuildTable();
    void Normalize(float array[]);
    QVector3D GetPoint(int index);
};

#endif // ARCLENGTH_H
