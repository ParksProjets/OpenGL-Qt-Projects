#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void DrawOpenGL();
    void AdvanceAnimation();

private slots:
    void onAnimateClicked();
    void onMoveModeSelected();
    void onAddModeSelected();
    void onRemoveModeSelected();

private:
    Ui::MainWindow *ui;
    QTimer *repaintTimer;
    QTimer *animationTimer;
};

#endif // MAINWINDOW_H
