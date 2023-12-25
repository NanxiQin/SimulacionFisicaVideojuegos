#include "AnchoredSpringForceGenerator.h"

AnchoredSpringForceGenerator::AnchoredSpringForceGenerator(double K, double restingLength, Vector3 anchorPos, double maxLength, Color boxColor):
	SpringForceGenerator(new Particle({ PxTransform(anchorPos), { 0,0,0 }, 1, 1e6,1, colorRGB[boxColor], -1, 0, NONE }, true, PxGeometryType::eBOX),K,restingLength, maxLength)
{}

AnchoredSpringForceGenerator::~AnchoredSpringForceGenerator()
{
	delete other;
}
