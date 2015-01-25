#pragma once
#include "light.h"
class LightRadius : public Light
{
public:
	LightRadius(float _radius);
	~LightRadius(void);

	float getRadius() {
		return radius;
	}

private:
	float radius;
};

