#include "gui/glwidget.h"

#include <GL/glu.h>

#include "util/geometry.h"

typedef std::list<Polygon *>::iterator PolygonIterator;
typedef std::list<GLEventHandler *>::iterator EventHandlerIterator;

GLWidget::GLWidget(QWidget *parent) :
	QGLWidget(QGLFormat(QGL::SampleBuffers), parent),
	glEventHandlers(),
	polygons(),
	eyePosition(0.0f, 0.0f, 5.0f),
	center(0.0f, 0.0f, 0.0f),
	upVector(0.0f, 1.0f, 0.0f),
	screenPlane(center, eyePosition),
	viewMatrix(),
	coordinateConverter(screenPlane)
{
}

GLWidget::~GLWidget()
{
	for (PolygonIterator it = polygons.begin(); it != polygons.end(); it++) {
		delete *it;
	}
}

Rectangle GLWidget::GetBounds()
{
	/* Viewport: x, y, width, height */
	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);

	/* Note y = 0 is the top of the screen in window coordinates, but
	 * OpenGL puts y = 0 at the bottom.
	 */
	Point2D topLeft = coordinateConverter.ConvertScreenToObjectCoords(
			Point2D(viewport[0], viewport[1]));
	Point2D bottomRight = coordinateConverter.ConvertScreenToObjectCoords(
			Point2D(viewport[0] + viewport[2], viewport[1] + viewport[3]));

	return Rectangle(topLeft.x(), bottomRight.x(),
			bottomRight.y(), topLeft.y());
}

void GLWidget::RegisterGLEventHandler(GLEventHandler *handler)
{
	glEventHandlers.push_back(handler);
}

void GLWidget::AddPolygon(Polygon *polygon)
{
	polygons.push_back(polygon);
}

void GLWidget::PaintGL()
{
	paintGL();
	update();
}

void GLWidget::ClearPolygons()
{
	for (PolygonIterator it = polygons.begin(); it != polygons.end(); it++) {
		delete *it;
	}

	polygons.clear();
}

void GLWidget::initializeGL()
{
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

	glColor3f(0.0f, 1.0f, 0.0f);

	for (PolygonIterator it = polygons.begin(); it != polygons.end(); it++) {
		(*it)->Draw();
	}

	glFlush();
}

void GLWidget::resizeGL(int width, int height)
{
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.0f, (float) width / (float) height, 0.01f, 50.0f);

	glMatrixMode(GL_MODELVIEW);
}

void GLWidget::mousePressEvent(QMouseEvent *qtEvent)
{
	for (EventHandlerIterator it = glEventHandlers.begin();
			it != glEventHandlers.end(); it++) {
		(*it)->HandleMousePress(ConvertToAppMouseEvent(qtEvent));
	}
}

void GLWidget::mouseReleaseEvent(QMouseEvent *qtEvent)
{
	for (EventHandlerIterator it = glEventHandlers.begin();
			it != glEventHandlers.end(); it++) {
		(*it)->HandleMouseRelease(ConvertToAppMouseEvent(qtEvent));
	}
}

void GLWidget::mouseMoveEvent(QMouseEvent * qtEvent)
{
	for (EventHandlerIterator it = glEventHandlers.begin();
			it != glEventHandlers.end(); it++) {
		(*it)->HandleMouseMove(ConvertToAppMouseEvent(qtEvent));
	}
}

MouseEvent *GLWidget::ConvertToAppMouseEvent(QMouseEvent *qtEvent)
{
	Point2D objectPoint = coordinateConverter.ConvertScreenToObjectCoords(
				Point2D(qtEvent->pos()));

	return new MouseEvent(objectPoint);
}
