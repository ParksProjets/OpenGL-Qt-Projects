#ifndef GLWIDGET_H_
#define GLWIDGET_H_

#include <list>

#include <QGLWidget>
#include <QMatrix4x4>
#include <QMouseEvent>
#include <QPlane3D>

#include "gui/coords.h"
#include "gui/glevents.h"
#include "gui/glwidget.h"
#include "rendering/polygon.h"
#include "util/geometry.h"

class GLWidget: public QGLWidget
{
	Q_OBJECT

public:
	explicit GLWidget(QWidget *parent = 0);
	~GLWidget();

	Rectangle GetBounds();
	void RegisterGLEventHandler(GLEventHandler *handler);
	void AddPolygon(Polygon *polygon);
	void PaintGL();
	void ClearPolygons();

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
	void mousePressEvent(QMouseEvent *qtEvent);

	/**
	 * Called when a mouse button is released.
	 */
	void mouseReleaseEvent(QMouseEvent *qtEvent);

    /**
     * Called when the mouse cursor is moved inside the widget's region.
     */
	void mouseMoveEvent(QMouseEvent *qtEvent);

private:
	std::list<GLEventHandler *> glEventHandlers;
	std::list<Polygon *> polygons;

	QVector3D eyePosition;
	QVector3D center;
	QVector3D upVector;

	QPlane3D screenPlane;
	QMatrix4x4 viewMatrix;

	CoordinateConverter coordinateConverter;

	MouseEvent *ConvertToAppMouseEvent(QMouseEvent *qtEvent);
};

#endif
