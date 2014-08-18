#include "rendering/blending.h"

#include <cmath>

typedef std::list<Primitive *>::iterator PrimitiveIterator;

Blend::Blend(std::list<Primitive *> primitives,
		double isoValue, double scaleWeight) :
	primitives(primitives), isoValue(isoValue), scaleWeight(scaleWeight)
{
}

double Blend::GetIsoValue()
{
	return isoValue;
}

bool Blend::ContainsPoint(Point2D location)
{
	return GetGlobalField(location) > isoValue;
}

SummationBlend::SummationBlend(std::list<Primitive *> primitives,
		double isoValue, double scaleWeight) :
	Blend(primitives, isoValue, scaleWeight)
{
}

double SummationBlend::GetGlobalField(Point2D location)
{
	double sum = 0;

	for (PrimitiveIterator it = primitives.begin();
			it != primitives.end(); it++) {
		Primitive *primitive = *it;

		sum += primitive->GetFieldValue(location);
	}

	return scaleWeight * sum;
}

RicciBlend::RicciBlend(std::list<Primitive *> primitives,
		double isoValue, double scaleWeight, double ricciFactor) :
	Blend(primitives, isoValue, scaleWeight), ricciFactor(ricciFactor)
{
}

double RicciBlend::GetGlobalField(Point2D location)
{
	double sum = 0;

	for (PrimitiveIterator it = primitives.begin();
			it != primitives.end(); it++) {
		Primitive *primitive = *it;

		sum += pow(primitive->GetFieldValue(location), ricciFactor);
	}

	return scaleWeight * pow(sum, 1.0 / ricciFactor);
}
