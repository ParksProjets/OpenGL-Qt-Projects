#include "controller.h"

#include <QtGlobal>

Controller::Controller(MainWindow *mainWindow, GLWidget *glWidget)
    : mainWindow(mainWindow),
      glWidget(glWidget)
{
    glWidget->RegisterGLEventHandler(this);
    mainWindow->RegisterControlEventHandler(this);
    
    glWidget->SetCurrentPolyhedron(subdivider.GetCurrentPolyhedron());
    glWidget->PaintGL();
}

void Controller::HandleSubdivide()
{
    glWidget->SetCurrentPolyhedron(subdivider.Subdivide());
    glWidget->PaintGL();
}

void Controller::HandleUndivide()
{
    glWidget->SetCurrentPolyhedron(subdivider.Undivide());
    glWidget->PaintGL();
}
