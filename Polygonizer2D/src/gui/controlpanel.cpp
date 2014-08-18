#include "gui/controlpanel.h"

#include <QVBoxLayout>

ControlPanel::ControlPanel(QWidget *parent, double startingRadius,
		double startingScaleWeight, double startingRicciFactor) :
	QWidget(parent),
	radiusSpinBox(this, "Radius"),
	scaleWeightSpinBox(this, "Scale Weight"),
	ricciFactorSpinBox(this, "Ricci Factor"),
	clearButton("Clear", this)
{
	InitializeRadiusSpinBox(startingRadius);
	InitializeScaleWeightSpinBox(startingScaleWeight);
	InitializeRicciFactorSpinBox(startingRicciFactor);

	DoLayout();
}

void ControlPanel::InitializeRadiusSpinBox(double startingRadius)
{
	radiusSpinBox.SetValue(startingRadius);
	radiusSpinBox.SetDecimals(1);
	radiusSpinBox.SetSingleStep(0.1);
	radiusSpinBox.SetMinimum(0.1);
}

void ControlPanel::InitializeScaleWeightSpinBox(double startingScaleWeight)
{
	scaleWeightSpinBox.SetValue(startingScaleWeight);
	scaleWeightSpinBox.SetDecimals(1);
	scaleWeightSpinBox.SetSingleStep(0.1);
	scaleWeightSpinBox.SetMinimum(0.1);
}

void ControlPanel::InitializeRicciFactorSpinBox(double startingRicciFactor)
{
	ricciFactorSpinBox.SetValue(startingRicciFactor);
	ricciFactorSpinBox.SetDecimals(1);
	ricciFactorSpinBox.SetSingleStep(0.1);
	ricciFactorSpinBox.SetMinimum(0.1);
}

void ControlPanel::DoLayout()
{
	QVBoxLayout *layout = new QVBoxLayout;
	layout->addWidget(&radiusSpinBox);
	layout->addWidget(&scaleWeightSpinBox);
	layout->addWidget(&ricciFactorSpinBox);
	layout->addWidget(&clearButton);
	layout->addStretch(1);
	setLayout(layout);
}

QDoubleSpinBox *ControlPanel::GetRadiusSpinBox()
{
	return radiusSpinBox.GetSpinBox();
}

QDoubleSpinBox *ControlPanel::GetScaleWeightSpinBox()
{
	return scaleWeightSpinBox.GetSpinBox();
}

QDoubleSpinBox *ControlPanel::GetRicciFactorSpinBox()
{
	return ricciFactorSpinBox.GetSpinBox();
}

QPushButton *ControlPanel::GetClearButton()
{
	return &clearButton;
}
