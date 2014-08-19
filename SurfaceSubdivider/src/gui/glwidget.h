#ifndef GLWIDGET_H_
#define GLWIDGET_H_

#include "gui/glwidget.h"

#include <list>

#include <QGLWidget>
#include <QMatrix4x4>
#include <QMouseEvent>
#include <QPlane3D>

#include "gui/glevents.h"
#include "polyhedron.h"
#include "rendering.h"

class GLWidget: public QGLWidget
{
	Q_OBJECT

public:
	explicit GLWidget(QWidget *parent = 0);
	~GLWidget();

    /**
     * Registers a handler for interaction events in the graphics widget.
     */
	void RegisterGLEventHandler(GLEventHandler *handler);
    
    /**
     * Tells the widget to repaint the current polyhedron.
     */
	void PaintGL();
    
    /**
     * Sets the polyhedron to be rendered in this widget.
     */
    void SetCurrentPolyhedron(Polyhedron *polyhedron);

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

private:
    Polyhedron *currentPolyhedron;
	std::list<GLEventHandler *> glEventHandlers;

	QVector3D eyePosition;
	QVector3D center;
	QVector3D upVector;

	QMatrix4x4 viewMatrix;
    
    Renderer renderer;
};

#endif
