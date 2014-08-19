#include "interaction.h"

#include <QtGlobal>

#include <cmath>

InteractionState::~InteractionState()
{
}

MoveState::MoveState() : InteractionState(), selectedIndex(-1)
{
}

void MoveState::handleMouseClick(InteractionManager *interactionManager,
                                 QVector3D position)
{
    lastMousePosition = position;

    for (int i = 0; i < interactionManager->getNumControlPoints(); i++)
    {
        QVector3D controlPoint = interactionManager->getControlPoint(i);
        if (interactionManager->isHit(position, controlPoint))
        {
            selectedIndex = i;
        }
    }
}

void MoveState::handleMouseMove(InteractionManager *interactionManager,
                                QVector3D position)
{
    if (selectedIndex < 0)
    {
        return;
    }

    float dx = position.x() - lastMousePosition.x();
    float dy = position.y() - lastMousePosition.y();

    QVector3D oldPoint = interactionManager->getControlPoint(selectedIndex);
    float newX = oldPoint.x() + dx;
    float newY = oldPoint.y() + dy;

    interactionManager->setControlPoint(selectedIndex,
                                        QVector3D(newX, newY, 0.0f));

    lastMousePosition = position;
}

void MoveState::handleMouseRelease(InteractionManager *interactionManager)
{
    Q_UNUSED(interactionManager);
    selectedIndex = -1;
}

InteractionManager::InteractionManager(
        QVector<QVector3D>* controlPoints, float hitThreshold) :
    controlPoints(controlPoints), hitThreshold(hitThreshold),
    state(new MoveState())
{
}

AddState::AddState()
{
}

void AddState::handleMouseClick(InteractionManager *interactionManager,
                                QVector3D position)
{
    interactionManager->addControlPoint(position);
}

void AddState::handleMouseMove(InteractionManager *interactionManager,
                               QVector3D position)
{
    Q_UNUSED(interactionManager);
    Q_UNUSED(position);
}

void AddState::handleMouseRelease(InteractionManager *interactionManager)
{
    Q_UNUSED(interactionManager);
}

RemoveState::RemoveState(){
}

void RemoveState::handleMouseClick(InteractionManager *interactionManager,
                                   QVector3D position)
{
    for (int i = 0; i < interactionManager->getNumControlPoints(); i++)
    {
        QVector3D controlPoint = interactionManager->getControlPoint(i);
        if (interactionManager->isHit(position, controlPoint))
        {
            interactionManager->removeControlPoint(i);
        }
    }
}

void RemoveState::handleMouseMove(InteractionManager *interactionManager,
                                  QVector3D position)
{
    Q_UNUSED(interactionManager);
    Q_UNUSED(position);
}

void RemoveState::handleMouseRelease(InteractionManager *interactionManager)
{
   Q_UNUSED(interactionManager);
}

void InteractionManager::enterMoveMode()
{
    delete state;
    state = new MoveState();
}

void InteractionManager::enterAddMode()
{
    delete state;
    state = new AddState();
}

void InteractionManager::enterRemoveMode()
{
    delete state;
    state = new RemoveState();
}

void InteractionManager::handleMouseClick(QVector3D position)
{
    state->handleMouseClick(this, position);
}

void InteractionManager::handleMouseRelease()
{
    state->handleMouseRelease(this);
}

void InteractionManager::handleMouseMove(QVector3D position)
{
    state->handleMouseMove(this, position);
}

bool InteractionManager::isHit(QVector3D click, QVector3D point)
{
    return (fabs(click.x() - point.x()) < hitThreshold &&
            fabs(click.y() - point.y()) < hitThreshold);
}

int InteractionManager::getNumControlPoints()
{
    return controlPoints->size();
}

QVector3D InteractionManager::getControlPoint(int index)
{
    return (*controlPoints)[index];
}

void InteractionManager::setControlPoint(int index, QVector3D newPoint)
{
    (*controlPoints)[index] = newPoint;
}

void InteractionManager::addControlPoint(QVector3D newPoint)
{
    controlPoints->push_back(newPoint);
}

void InteractionManager::removeControlPoint(int index)
{
    controlPoints->removeAt(index);
}
