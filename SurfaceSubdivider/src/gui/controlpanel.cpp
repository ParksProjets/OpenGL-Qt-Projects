#include "gui/controlpanel.h"

#include <QVBoxLayout>

ControlPanel::ControlPanel(QWidget *parent) :
    QWidget(parent),
    subdivideButton("Subdivide", this),
    undivideButton("Undivide", this)
{
    DoLayout();
}

void ControlPanel::DoLayout()
{
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(&subdivideButton);
    layout->addWidget(&undivideButton);
    layout->addStretch(1);
    setLayout(layout);
}

QPushButton *ControlPanel::GetSubdivideButton()
{
    return &subdivideButton;
}

QPushButton *ControlPanel::GetUndivideButton()
{
    return &undivideButton;
}
