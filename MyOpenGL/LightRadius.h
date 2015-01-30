#pragma once
#include "light.h"
class LightRadius : public Light
{
public:
	LightRadius(float _radius, float _intensity);
	~LightRadius(void);

	float getRadius() {
		return radius;
	}
	float getIntensity() {
		return intensity;
	}
	void setRadius(float _radius) {
		radius = _radius;
	}

private:
	float radius;
	float intensity;
};

