#include "gui/glwidget.h"

#include <cstddef>

#include <GL/glu.h>

typedef std::list<GLEventHandler *>::iterator EventHandlerIterator;

GLWidget::GLWidget(QWidget *parent)
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent),
      currentPolyhedron(NULL),
      glEventHandlers(),
      eyePosition(4, 4, 3),
      center(0.0f, 0.0f, 0.0f),
      upVector(0.0f, 1.0f, 0.0f),
      viewMatrix()
{
}

GLWidget::~GLWidget()
{
}

void GLWidget::RegisterGLEventHandler(GLEventHandler *handler)
{
    glEventHandlers.push_back(handler);
}

void GLWidget::PaintGL()
{
    paintGL();
    
    // TODO: do we need this?
    update();
}

void GLWidget::SetCurrentPolyhedron(Polyhedron* polyhedron)
{
    currentPolyhedron = polyhedron;
}

void GLWidget::initializeGL()
{
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    /* XXX hack around weird behaviour where window is transparent until
     * the first polygon is drawn.  Draw a polygon with the same colour
     * as the background.  It will be cleared once paintGL is called.
     */
    glColor3f(1.0f, 1.0f, 1.0f);

    glBegin(GL_POLYGON);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(0.0f, 0.5f);
    glVertex2f(1.0f, 1.0f);
    glEnd();
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    viewMatrix.setToIdentity();
    viewMatrix.lookAt(eyePosition, center, upVector);
    glLoadMatrixf(viewMatrix.data());

    if (currentPolyhedron != NULL) {
        renderer.Render(currentPolyhedron);
    }

    glFlush();
}

void GLWidget::resizeGL(int width, int height)
{
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (float) width / (float) height, 0.01f, 50.0f);

    glMatrixMode(GL_MODELVIEW);
}
