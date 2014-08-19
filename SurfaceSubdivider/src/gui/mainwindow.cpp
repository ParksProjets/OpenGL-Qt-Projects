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
    controlPanel(&containerWindow)
{
    DoLayout();

    setCentralWidget(&containerWindow);

    resize(defaults::APP_WIDTH, defaults::APP_HEIGHT);

    connect(controlPanel.GetSubdivideButton(),
            SIGNAL(clicked()),
            this,
            SLOT(OnSubdivide()));
    
    connect(controlPanel.GetUndivideButton(),
            SIGNAL(clicked()),
            this,
            SLOT(OnUndivide()));

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

void MainWindow::OnSubdivide()
{
    for (EventHandlerIterator it = controlEventHandlers.begin();
            it != controlEventHandlers.end(); it++) {
        (*it)->HandleSubdivide();
    }
}

void MainWindow::OnUndivide()
{
    for (EventHandlerIterator it = controlEventHandlers.begin();
            it != controlEventHandlers.end(); it++) {
        (*it)->HandleUndivide();
    }
}
