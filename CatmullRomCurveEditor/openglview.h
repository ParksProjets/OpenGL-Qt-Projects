#ifndef OPENGLVIEW_H
#define OPENGLVIEW_H

#include "animation.h"
#include "interaction.h"

#include <GL/glu.h>
#include <QGLWidget>
#include <QMatrix4x4>
#include <QMouseEvent>
#include <QPlane3D>

class OpenGLView : public QGLWidget
{
    Q_OBJECT

public:
    explicit OpenGLView(QWidget *parent = 0);
    ~OpenGLView();

    void enterMoveMode();
    void enterAddMode();
    void enterRemoveMode();

    void startAnimation();
    void advanceAnimation();

    float getParametricValue();
    float getArclength();

protected:
    /**
     * Called automatically by Qt after the OpenGL context is created.
     * Do all OpenGL setup here before the actual program execution starts.
     */
    void initializeGL();

    /**
     * Called whenever the widget is being redrawn.  Assumes that the
     * OpenGL context has already been made the current one, so no need
     * to call this->makeCurrent();
     */
    void paintGL();

    /**
     * Called when the widget is resized.
     */
    void resizeGL(int width, int height);

    /**
     * Called when a mouse button is pressed and the cursor is hovering
     * over the widget.
     */
    void mousePressEvent(QMouseEvent *event);

    void mouseReleaseEvent(QMouseEvent *event);

    /**
     * Called when the mouse cursor is moved inside the widget's region.
     */
    void mouseMoveEvent(QMouseEvent *event);

private:
    InteractionManager* interactionManager;
    PathAnimator *pathAnimator;

    QMatrix4x4 projectionMatrix;
    QMatrix4x4 viewMatrix;

    QVector<QVector3D> controlPoints;
    QVector<QVector3D> allInterpolatedPoints;
    static const int subdivisionLevel = 4;

    QVector3D convertScreenToObjectCoords(QPoint screenPoint);

    QVector3D eyePosition;
    QVector3D center;
    QVector3D upVector;

    QPlane3D screenPlane;

    void createInitialControlPoints();

    void drawInterpolatedPoints();
    void drawControlPoints();
};

#endif // OPENGLVIEW_H
