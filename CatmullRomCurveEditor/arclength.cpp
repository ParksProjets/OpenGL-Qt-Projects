#include "arclength.h"

#include <algorithm>
#include <cmath>

float EuclideanDistance(QVector3D point1, QVector3D point2)
{
    float sum = 0.0f;

    int i;
    for (i = 0; i < 3; i++) {
        sum += pow(point1[i] - point2[i], 2);
    }

    return sqrt(sum);
}

ArclengthTable::ArclengthTable(QVector<QVector3D> *points) :
    points(points),
    numTableEntries(points->size())
{
    indices = new int[numTableEntries];
    parametricEntries = new float[numTableEntries];
    arclengths = new float[numTableEntries];

    BuildTable();
}

ArclengthTable::~ArclengthTable()
{
    delete [] indices;
    delete [] parametricEntries;
    delete [] arclengths;
}

void ArclengthTable::BuildTable()
{
    indices[0] = 0;
    parametricEntries[0] = 0.0f;
    arclengths[0] = 0.0f;

    float parametricStep = 1.0 / points->size();
    float distanceToNextPoint;

    int i;
    for (i = 1; i < points->size(); i++) {
        indices[i] = i;
        parametricEntries[i] = i * parametricStep;

        distanceToNextPoint = EuclideanDistance(GetPoint(i - 1),
                                                GetPoint(i));
        arclengths[i] = arclengths[i - 1] + distanceToNextPoint;
    }

    Normalize(arclengths);
}

void ArclengthTable::Normalize(float *array)
{
    float maxValue = *std::max_element(array, array + numTableEntries);

    for (int i = 0; i < numTableEntries; i++) {
        array[i] = array[i] / maxValue;
    }
}

QVector3D ArclengthTable::GetPoint(int index)
{
    return (*points)[index];
}

float ArclengthTable::GetParametricEntry(float arclength)
{
    int lowerBoundIndex;
    int upperBoundIndex;

    for (int i = 0; i < numTableEntries; i++) {
        if (arclength <= arclengths[i]) {
            lowerBoundIndex = i;
        }
        if (arclength >= arclengths[i]) {
            upperBoundIndex = i;
            break;
        }
    }

    float lowerBoundArclength = arclengths[lowerBoundIndex];
    float upperBoundArclength = arclengths[upperBoundIndex];

    float slope = (arclength - lowerBoundArclength) /
            (upperBoundArclength - lowerBoundArclength);

    float lowerBoundParametricEntry = parametricEntries[lowerBoundIndex];
    float upperBoundParametricEntry = parametricEntries[upperBoundIndex];

    return lowerBoundParametricEntry +
            slope * (upperBoundParametricEntry - lowerBoundParametricEntry);
}

float ArclengthTable::GetArclength(float parametricEntry)
{
    float distanceBetweenEntries = 1.0f / (numTableEntries - 1);
    int index = (int) (parametricEntry / distanceBetweenEntries);

    return arclengths[index] +
            ((parametricEntry - parametricEntries[index]) /
             (parametricEntries[index + 1] - parametricEntries[index])) *
            (arclengths[index + 1] - arclengths[index]);
}
