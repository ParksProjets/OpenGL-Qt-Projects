#ifndef INTERACTION_H
#define INTERACTION_H

#include <QVector>
#include <QVector3D>

class InteractionManager;

class InteractionState
{
public:
    virtual ~InteractionState();
    virtual void handleMouseClick(InteractionManager *interactionManager,
                                  QVector3D position) = 0;
    virtual void handleMouseRelease(InteractionManager *interactionManager) = 0;
    virtual void handleMouseMove(InteractionManager *interactionManager,
                                 QVector3D position) = 0;
};

class MoveState : public InteractionState
{
public:
    MoveState();

    virtual void handleMouseClick(InteractionManager *interactionManager,
                                  QVector3D position);
    virtual void handleMouseRelease(InteractionManager *interactionManager);
    virtual void handleMouseMove(InteractionManager *interactionManager,
                                 QVector3D position);

private:
    QVector3D lastMousePosition;
    int selectedIndex;
};

class AddState : public InteractionState
{
public:
    AddState();

    virtual void handleMouseClick(InteractionManager *interactionManager,
                                  QVector3D position);
    virtual void handleMouseRelease(InteractionManager *interactionManager);
    virtual void handleMouseMove(InteractionManager *interactionManager,
                                 QVector3D position);
};

class RemoveState : public InteractionState
{
public:
    RemoveState();

    virtual void handleMouseClick(InteractionManager *interactionManager,
                                  QVector3D position);
    virtual void handleMouseRelease(InteractionManager *interactionManager);
    virtual void handleMouseMove(InteractionManager *interactionManager,
                                 QVector3D position);
};

class InteractionManager
{
    friend class InteractionState;

public:
    InteractionManager(QVector<QVector3D> *controlPoints,
                       float hitThreshold = 0.1);

    void handleMouseClick(QVector3D position);
    void handleMouseRelease();
    void handleMouseMove(QVector3D position);

    void enterMoveMode();
    void enterAddMode();
    void enterRemoveMode();

    int getNumControlPoints();
    bool isHit(QVector3D click, QVector3D point);
    QVector3D getControlPoint(int index);
    void setControlPoint(int index, QVector3D newPoint);
    void addControlPoint(QVector3D newPoint);
    void removeControlPoint(int index);

private:
    QVector<QVector3D> *controlPoints;
    float hitThreshold;
    InteractionState *state;
};

#endif // INTERACTION_H
