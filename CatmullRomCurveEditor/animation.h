#ifndef ANIMATION_H
#define ANIMATION_H

#include <QVector>
#include <QVector3D>

class PathAnimator
{
public:
    PathAnimator(QVector<QVector3D> *pathPoints);

    /**
     * Starts the animation.  If animation was in progress, it restarts.
     */
    void startAnimation();

    void advance();

    void drawMarker();

    float getParametricValue();
    float getArclength();

private:
    QVector<QVector3D> *pathPoints;
    int pointIndex;
    bool isRunning;

    QVector3D getCurrentPoint();
};

#endif // ANIMATION_H
