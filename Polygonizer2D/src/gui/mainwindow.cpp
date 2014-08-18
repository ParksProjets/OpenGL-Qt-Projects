#include "gui/mainwindow.h"

#include <QHBoxLayout>
#include <QtGui>
#include <QWidget>

#include "defaults.h"

typedef std::list<ControlEventHandler *>::iterator EventHandlerIterator;

MainWindow::MainWindow() :
	QMainWindow(),
	containerWindow(this),
	glWidget(&containerWindow),
	controlPanel(&containerWindow, defaults::RADIUS, defaults::SCALE_WEIGHT,
			defaults::RICCI_FACTOR)
{
	DoLayout();

	setCentralWidget(&containerWindow);

	resize(defaults::APP_WIDTH, defaults::APP_HEIGHT);

	connect(controlPanel.GetRadiusSpinBox(),
			SIGNAL(valueChanged(double)),
			this,
			SLOT(OnRadiusChanged(double)));

	connect(controlPanel.GetScaleWeightSpinBox(),
			SIGNAL(valueChanged(double)),
			this,
			SLOT(OnScaleWeightChanged(double)));

	connect(controlPanel.GetRicciFactorSpinBox(),
			SIGNAL(valueChanged(double)),
			this,
			SLOT(OnRicciFactorChanged(double)));

	connect(controlPanel.GetClearButton(),
			SIGNAL(clicked()),
			this,
			SLOT(OnClear()));
}

MainWindow::~MainWindow()
{
}

GLWidget *MainWindow::GetGLWidgetPtr()
{
	return &glWidget;
}

void MainWindow::RegisterControlEventHandler(ControlEventHandler *handler)
{
	controlEventHandlers.push_back(handler);
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
	QMainWindow::resizeEvent(event);

	glWidget.repaint();
}

void MainWindow::DoLayout()
{
	QHBoxLayout *layout = new QHBoxLayout;
	layout->addWidget(&glWidget, 6);
	layout->addWidget(&controlPanel, 1);

	containerWindow.setLayout(layout);
}

void MainWindow::OnRadiusChanged(double newRadius)
{
	for (EventHandlerIterator it = controlEventHandlers.begin();
			it != controlEventHandlers.end(); it++) {
		(*it)->HandleRadiusChanged(newRadius);
	}
}

void MainWindow::OnScaleWeightChanged(double newScaleWeight)
{
	for (EventHandlerIterator it = controlEventHandlers.begin();
			it != controlEventHandlers.end(); it++) {
		(*it)->HandleScaleWeightChanged(newScaleWeight);
	}
}

void MainWindow::OnRicciFactorChanged(double newRicciFactor)
{
	for (EventHandlerIterator it = controlEventHandlers.begin();
			it != controlEventHandlers.end(); it++) {
		(*it)->HandleRicciFactorChanged(newRicciFactor);
	}
}

void MainWindow::OnClear()
{
	for (EventHandlerIterator it = controlEventHandlers.begin();
			it != controlEventHandlers.end(); it++) {
		(*it)->HandleClear();
	}
}
