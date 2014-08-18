#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include <list>

#include <QMainWindow>
#include <QWidget>

#include "gui/controlevents.h"
#include "gui/controlpanel.h"
#include "gui/glwidget.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow();
	~MainWindow();

	GLWidget *GetGLWidgetPtr();
	void RegisterControlEventHandler(ControlEventHandler *handler);

private slots:
	void OnRadiusChanged(double newRadius);
	void OnScaleWeightChanged(double newScaleWeight);
	void OnRicciFactorChanged(double newRicciFactor);
	void OnClear();

protected:
	void resizeEvent(QResizeEvent *event);

private:
	QWidget containerWindow;
	GLWidget glWidget;
	ControlPanel controlPanel;

	std::list<ControlEventHandler *> controlEventHandlers;

	void DoLayout();
};

#endif
