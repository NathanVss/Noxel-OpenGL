#include "LightSun.h"


LightSun::LightSun(void)
{
	this->seconds = 0;
}


LightSun::~LightSun(void)
{
}

void LightSun::setSeconds(int s) {
	if(s >= 24*3600) {
		s = s%(24*3600); 
	}
	this->seconds = s;
}

int LightSun::getSeconds() {
	return this->seconds;
}

float LightSun::getIndice() {
	if(seconds >= 6*3600 && seconds < 9*3600) {
		//return 0.5f;
		int curSec = seconds - 6*3600;
		return 540/10800.0f + (0.95/10800) * curSec;
		// TO 0.05 -> 1.0f en 3*3600
	} else if(seconds >= 22*3600 && seconds < 24 * 3600) {
		// TO 1.0f -> 0.05f en 2*3600
		//return 0.3f;

		int curSec = seconds - 22*3600;
		//return -0.00013*curSec + 1;
		return 1.0f - (0.95/7200.0f)*curSec;

	} else if(seconds >= 0 && seconds < 6*3600) {
		return 0.05f;
	} else if(seconds >= 9*3600 && seconds < 22*3600) {
		return 1.0f;
	} else {
		return 1.0f;
	}
}