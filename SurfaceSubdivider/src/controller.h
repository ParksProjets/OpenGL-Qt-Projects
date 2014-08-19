#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include "gui/controlevents.h"
#include "gui/glevents.h"
#include "gui/glwidget.h"
#include "gui/mainwindow.h"
#include "subdivision.h"

class Controller : GLEventHandler, ControlEventHandler
{
public:
	Controller(MainWindow *mainWindow, GLWidget *glWidget);

    virtual void HandleSubdivide();
    virtual void HandleUndivide();

private:
	MainWindow *mainWindow;
	GLWidget *glWidget;
    CatmullClarkSubdivider subdivider;
};

#endif
