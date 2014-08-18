#ifndef BLENDING_H_
#define BLENDING_H_

#include <list>

#include "rendering/primitives.h"
#include "util/geometry.h"

class Blend
{
public:
	Blend(std::list<Primitive *> primitives, double isoValue,
			double scaleWeight = 1.0);
	virtual ~Blend() {};

	virtual double GetIsoValue();
	virtual double GetGlobalField(Point2D location) = 0;
	virtual bool ContainsPoint(Point2D location);

protected:
	std::list<Primitive *> primitives;
	double isoValue;
	double scaleWeight;
};

class SummationBlend : public Blend
{
public:
	SummationBlend(std::list<Primitive *> primitives, double isoValue,
			double scaleWeight = 1.0);

	double GetGlobalField(Point2D location);
};

class RicciBlend : public Blend
{
public:
	RicciBlend(std::list<Primitive *> primitives, double isoValue,
			double scaleWeight, double ricciFactor);

	double GetGlobalField(Point2D location);

private:
	double ricciFactor;
};

#endif
