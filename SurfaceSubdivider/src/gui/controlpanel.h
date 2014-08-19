#ifndef CONTROLLPANEL_H_
#define CONTROLLPANEL_H_

#include <QDoubleSpinBox>
#include <QPushButton>
#include <QWidget>

class ControlPanel : public QWidget
{
	Q_OBJECT

public:
	ControlPanel(QWidget *parent);

	QPushButton *GetSubdivideButton();
    QPushButton *GetUndivideButton();

private:
	QPushButton subdivideButton;
   	QPushButton undivideButton;

	void DoLayout();
};

#endif
