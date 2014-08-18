#include "gui/spinbox.h"

#include <QtGui>
#include <QVBoxLayout>

LabelledSpinBox::LabelledSpinBox(QWidget *parent, QString text) :
	QWidget(parent), text(text), label(this), spinBox(this)
{
	label.setText(text);

	DoLayout();

	setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
}

void LabelledSpinBox::SetValue(double value)
{
	spinBox.setValue(value);
}

void LabelledSpinBox::SetDecimals(int decimals)
{
	spinBox.setDecimals(decimals);
}

void LabelledSpinBox::SetSingleStep(double step)
{
	spinBox.setSingleStep(step);
}

void LabelledSpinBox::SetMinimum(double minimum)
{
	spinBox.setMinimum(minimum);
}

void LabelledSpinBox::DoLayout()
{
	QVBoxLayout *layout = new QVBoxLayout;
	layout->addWidget(&label);
	layout->addWidget(&spinBox);
	layout->addStretch(1);

	setLayout(layout);
}

QDoubleSpinBox *LabelledSpinBox::GetSpinBox()
{
	return &spinBox;
}
