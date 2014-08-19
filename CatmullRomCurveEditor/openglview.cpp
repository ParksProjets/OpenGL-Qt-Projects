#include "openglview.h"
#include "interpolation.h"

#include <QRay3D>
#include <QtGlobal>

OpenGLView::OpenGLView(QWidget *parent) :
    QGLWidget(QGLFormat(QGL::SampleBuffers), parent),
    projectionMatrix(),
    viewMatrix(),
    controlPoints()
{
    eyePosition = QVector3D(0.0f, 0.0f, 5.0f);
    center = QVector3D(0.0f, 0.0f, 0.0f);
    upVector = QVector3D(0.0f, 1.0f, 0.0f);

    screenPlane = QPlane3D(center, eyePosition);

    createInitialControlPoints();

    interactionManager = new InteractionManager(&controlPoints);
    pathAnimator = new PathAnimator(&allInterpolatedPoints);
}

OpenGLView::~OpenGLView()
{
    delete interactionManager;
    delete pathAnimator;
}

void OpenGLView::createInitialControlPoints()
{
    controlPoints.push_back(QVector3D(-2.0f, -2.0f, 0));
    controlPoints.push_back(QVector3D(-1.8f, 1.0f, 0));
    controlPoints.push_back(QVector3D(-1.0f, 0.0f, 0));
    controlPoints.push_back(QVector3D(0.0f, 2.0f, 0));
    controlPoints.push_back(QVector3D(1.0f, 0.0f, 0));
    controlPoints.push_back(QVector3D(1.8f, 1.0f, 0));
    controlPoints.push_back(QVector3D(2.0f, -2.0f, 0));
}

void OpenGLView::enterMoveMode()
{
    interactionManager->enterMoveMode();
}

void OpenGLView::enterAddMode()
{
    interactionManager->enterAddMode();
}

void OpenGLView::enterRemoveMode()
{
    interactionManager->enterRemoveMode();
}

void OpenGLView::startAnimation()
{
    pathAnimator->startAnimation();
}

void OpenGLView::advanceAnimation()
{
    pathAnimator->advance();
}

void OpenGLView::initializeGL()
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void OpenGLView::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    viewMatrix.setToIdentity();
    viewMatrix.lookAt(eyePosition, center, upVector);
    glLoadMatrixf(viewMatrix.data());

    drawInterpolatedPoints();
    drawControlPoints();
    pathAnimator->drawMarker();
}

void OpenGLView::drawInterpolatedPoints()
{
    allInterpolatedPoints.clear();

    CatmullRomInterpolation interpolator(controlPoints);

    size_t numInterpolationPoints = interpolator.getNumPoints(
                subdivisionLevel);

    allInterpolatedPoints = interpolator.interpolate(numInterpolationPoints);

    glColor3f(1.0f, 0.0f, 0.0f);
    glLineWidth(3.0f);
    glBegin(GL_LINE_STRIP);

    for (int i = 0; i < allInterpolatedPoints.size(); i++) {
        QVector3D currentPoint = allInterpolatedPoints[i];
        glVertex3d(currentPoint.x(), currentPoint.y(), currentPoint.z());
    }

    glEnd();
}

void OpenGLView::drawControlPoints()
{
    glColor3f(0.0f, 0.0f, 0.0f);
    glPointSize(6.0f);
    glBegin(GL_POINTS);

    for (int i = 0; i < controlPoints.size(); ++i)
    {
        QVector3D controlPoint = controlPoints[i];
        glVertex3d(controlPoint.x(), controlPoint.y(), controlPoint.z());
    }

    glEnd();
}

void OpenGLView::resizeGL(int width, int height)
{
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    projectionMatrix.setToIdentity();
    projectionMatrix.perspective(90.0f, (float) width / (float) height, 0.01f, 50.0f);
    glLoadMatrixf(projectionMatrix.data());

    glMatrixMode(GL_MODELVIEW);
}

void OpenGLView::mousePressEvent(QMouseEvent *event)
{
    interactionManager->handleMouseClick(convertScreenToObjectCoords(event->pos()));
}

void OpenGLView::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    interactionManager->handleMouseRelease();
}

void OpenGLView::mouseMoveEvent(QMouseEvent *event)
{
    interactionManager->handleMouseMove(convertScreenToObjectCoords(event->pos()));
}

QVector3D OpenGLView::convertScreenToObjectCoords(QPoint screenPoint)
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

    if (qIsNaN(t))
    {
        qWarning("No intersection found.");
    }
    else
    {
        point = ray.point(t);
    }

    return point;
}

float OpenGLView::getArclength()
{
    return pathAnimator->getArclength();
}

float OpenGLView::getParametricValue()
{
    return pathAnimator->getParametricValue();
}
