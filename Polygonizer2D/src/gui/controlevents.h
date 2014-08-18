#ifndef CONTROLEVENTS_H_
#define CONTROLEVENTS_H_

class ControlEventHandler
{
public:
	virtual ~ControlEventHandler() {};

	virtual void HandleRadiusChanged(double newRadius) = 0;
	virtual void HandleScaleWeightChanged(double newScaleWeight) = 0;
	virtual void HandleRicciFactorChanged(double newRicciFactor) = 0;
	virtual void HandleClear() = 0;
};

#endif
