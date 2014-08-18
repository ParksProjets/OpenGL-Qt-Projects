#ifndef CONTROLLPANEL_H_
#define CONTROLLPANEL_H_

#include <QDoubleSpinBox>
#include <QPushButton>
#include <QWidget>

#include "gui/spinbox.h"

class ControlPanel : public QWidget
{
	Q_OBJECT

public:
	ControlPanel(QWidget *parent, double startingRadius,
			double startingScaleWeight, double startingRicciFactor);

	QDoubleSpinBox *GetRadiusSpinBox();
	QDoubleSpinBox *GetScaleWeightSpinBox();
	QDoubleSpinBox *GetRicciFactorSpinBox();
	QPushButton *GetClearButton();

private:
	LabelledSpinBox radiusSpinBox;
	LabelledSpinBox scaleWeightSpinBox;
	LabelledSpinBox ricciFactorSpinBox;
	QPushButton clearButton;

	void InitializeRadiusSpinBox(double startingRadius);
	void InitializeScaleWeightSpinBox(double startingScaleWeight);
	void InitializeRicciFactorSpinBox(double startingRicciFactor);
	void DoLayout();
};

#endif
