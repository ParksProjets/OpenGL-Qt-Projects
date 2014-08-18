#include "controller.h"

#include <QtGlobal>

#include "rendering/blending.h"
#include "rendering/continuation.h"
#include "rendering/grid.h"
#include "rendering/polygon.h"
#include "rendering/polygonization.h"

typedef std::list<Primitive *>::iterator PrimitiveIterator;

Controller::Controller(MainWindow *mainWindow, GLWidget *glWidget,
		double isoValue, double radius, double scaleWeight,
		double ricciFactor) :
	mainWindow(mainWindow),
	glWidget(glWidget),
	isoValue(isoValue),
	radius(radius),
	scaleWeight(scaleWeight),
	ricciFactor(ricciFactor),
	primitives(),
	selectedPrimitive(NULL),
	lastMousePosition(0.0, 0.0)
{
	glWidget->RegisterGLEventHandler(this);
	mainWindow->RegisterControlEventHandler(this);
}

Controller::~Controller()
{
	for (PrimitiveIterator primitive = primitives.begin();
			primitive != primitives.end(); primitive++) {
		delete *primitive;
	}
}

void Controller::HandleMousePress(MouseEvent *event)
{
	Point2D position = event->Position();

	Primitive *container = GetContainingPrimitive(position);

	if (container == NULL) {
		CreatePrimitive(position);
	} else {
		selectedPrimitive = container;
		lastMousePosition = position;
	}

	glWidget->PaintGL();

	delete event;
}

void Controller::HandleMouseRelease(MouseEvent *event)
{
	selectedPrimitive = NULL;
}

void Controller::HandleMouseMove(MouseEvent *event)
{
	if (selectedPrimitive == NULL) {
		return;
	}

	Point2D position = event->Position();

	double dx = position.x() - lastMousePosition.x();
	double dy = position.y() - lastMousePosition.y();

	selectedPrimitive->Shift(dx, dy);

	if (!glWidget->GetBounds().Contains(
			selectedPrimitive->GetSkeletonPoint())) {
		selectedPrimitive->Shift(-dx, -dy);
		delete event;
		return;
	}

	lastMousePosition = position;

	UpdateAllPolygons();

	glWidget->PaintGL();

	delete event;
}

void Controller::HandleRadiusChanged(double newRadius)
{
	radius = newRadius;
}

void Controller::HandleScaleWeightChanged(double newScaleWeight)
{
	scaleWeight = newScaleWeight;
	UpdateAllPolygons();
}

void Controller::HandleRicciFactorChanged(double newRicciFactor)
{
	ricciFactor = newRicciFactor;
	UpdateAllPolygons();
}

void Controller::HandleClear()
{
	for (PrimitiveIterator it = primitives.begin();
			it != primitives.end(); it++) {
		delete *it;
	}

	primitives.clear();

	glWidget->ClearPolygons();
	glWidget->PaintGL();
}

void Controller::CreatePrimitive(Point2D location)
{
	Primitive *primitive = new PointPrimitive(location, radius, isoValue);
	primitives.push_back(primitive);

	Polygon *polygon = new Polygon(GetSurfacePoints(primitive));
	primitive->AssociatePolygon(polygon);

	glWidget->AddPolygon(polygon);
}

std::list<Point2D> Controller::GetSurfacePoints(Primitive *primitive)
{
	Grid grid(glWidget->GetBounds());

	RicciBlend blend(primitives, isoValue, scaleWeight, ricciFactor);
	ContinuationAlgorithm continuationAlgorithm(&grid, primitive, &blend);
	PolygonizationAlgorithm polygonizationAlgorithm(
			continuationAlgorithm.GetSurfaceCells(), &blend);

	return polygonizationAlgorithm.GetSurfacePoints();
}

Primitive *Controller::GetContainingPrimitive(Point2D point)
{
	for (PrimitiveIterator it = primitives.begin();
			it != primitives.end(); it++) {
		Primitive *primitive = *it;

		if (primitive->ContainsPoint(point)) {
			return primitive;
		}
	}

	return NULL;
}

void Controller::UpdatePolygon(Primitive *primitive)
{
	primitive->GetPolygon()->UpdateSurface(GetSurfacePoints(primitive));
}

void Controller::UpdateAllPolygons()
{
	for (PrimitiveIterator it = primitives.begin();
			it != primitives.end(); it++) {
		Primitive * primitive= *it;

		UpdatePolygon(primitive);

		glWidget->PaintGL();
	}
}
