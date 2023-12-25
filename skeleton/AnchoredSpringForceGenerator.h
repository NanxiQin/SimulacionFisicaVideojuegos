#pragma once
#include "SpringForceGenerator.h"
class AnchoredSpringForceGenerator :public SpringForceGenerator
{
public:
	AnchoredSpringForceGenerator(double K, double restingLength, Vector3 anchorPos, double maxLength = 200,Color boxColor=Blue);
	~AnchoredSpringForceGenerator();
};

