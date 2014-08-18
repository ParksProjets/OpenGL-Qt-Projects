#ifndef SPINBOX_H_
#define SPINBOX_H_

#include <QDoubleSpinBox>
#include <QLabel>
#include <QString>
#include <QWidget>

class LabelledSpinBox : public QWidget
{
	Q_OBJECT;

public:
	LabelledSpinBox(QWidget *parent, QString text);

	void SetValue(double value);
	void SetDecimals(int decimals);
	void SetSingleStep(double step);
	void SetMinimum(double minimum);

	QDoubleSpinBox *GetSpinBox();

private:
	QString text;

	QLabel label;
	QDoubleSpinBox spinBox;

	void DoLayout();
};



#endif
