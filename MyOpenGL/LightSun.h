#pragma once

#include "Light.h"

class LightSun: public Light
{
public:
	LightSun(void);
	~LightSun(void);
	void setSeconds(int);
	int getSeconds();
	float getIndice();
private:
	int seconds;

};

