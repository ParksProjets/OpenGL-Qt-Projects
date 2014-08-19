#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    repaintTimer(NULL),
    animationTimer(NULL)
{
    ui->setupUi(this);
    connect(ui->animateButton, SIGNAL(clicked()), this, SLOT(onAnimateClicked()));
    connect(ui->moveModeButton, SIGNAL(clicked()), this, SLOT(onMoveModeSelected()));
    connect(ui->addModeButton, SIGNAL(clicked()), this, SLOT(onAddModeSelected()));
    connect(ui->removeModeButton, SIGNAL(clicked()), this, SLOT(onRemoveModeSelected()));

    repaintTimer = new QTimer(this);
    connect(repaintTimer, SIGNAL(timeout()), this, SLOT(DrawOpenGL()));

    animationTimer = new QTimer(this);
    connect(animationTimer, SIGNAL(timeout()), this, SLOT(AdvanceAnimation()));

    // Timing interval in milliseconds
    repaintTimer->start(20);
    animationTimer->start(40);
}

void MainWindow::DrawOpenGL()
{
    ui->oglwidget->repaint();

    float parametricValue = ui->oglwidget->getParametricValue();
    float arclength = ui->oglwidget->getArclength();
    ui->parametricDisplay->display(parametricValue);
    ui->arclengthDisplay->display(arclength);
}

void MainWindow::AdvanceAnimation()
{
   ui->oglwidget->advanceAnimation();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onAnimateClicked()
{
    ui->oglwidget->startAnimation();
}

void MainWindow::onMoveModeSelected()
{
    ui->oglwidget->enterMoveMode();
}

void MainWindow::onAddModeSelected()
{
    ui->oglwidget->enterAddMode();
}

void MainWindow::onRemoveModeSelected()
{
    ui->oglwidget->enterRemoveMode();
}
