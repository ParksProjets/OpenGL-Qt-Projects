#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include <list>

#include "gui/controlevents.h"
#include "gui/glevents.h"
#include "gui/glwidget.h"
#include "gui/mainwindow.h"
#include "rendering/primitives.h"
#include "util/geometry.h"

class Controller : GLEventHandler, ControlEventHandler
{
public:
	Controller(MainWindow *mainWindow, GLWidget *glWidget,
			double isoValue, double radius, double scaleWeight,
			double ricciFactor);
	~Controller();

	virtual void HandleMousePress(MouseEvent *event);
	virtual void HandleMouseRelease(MouseEvent *event);
	virtual void HandleMouseMove(MouseEvent *event);
	void CreatePrimitive(Point2D location);

	virtual void HandleRadiusChanged(double newRadius);
	virtual void HandleScaleWeightChanged(double newScaleWeight);
	virtual void HandleRicciFactorChanged(double newRicciFactor);
	virtual void HandleClear();

private:
	MainWindow *mainWindow;
	GLWidget *glWidget;
	double isoValue;
	double radius;
	double scaleWeight;
	double ricciFactor;
	std::list<Primitive *> primitives;
	Primitive *selectedPrimitive;
	Point2D lastMousePosition;

	std::list<Point2D> GetSurfacePoints(Primitive *primitive);
	Primitive *GetContainingPrimitive(Point2D point);
	void UpdatePolygon(Primitive *primitive);
	void UpdateAllPolygons();
};

#endif
