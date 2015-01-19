#include "FpsCounter.h"
#include <Dependecies\SDL2-2.0.3\include\SDL.h>

namespace YuEngine {


FpsCounter::FpsCounter(void){

	this->frames = 0;
	this->lastFps = 0;
	this->lastTime = SDL_GetTicks();

}

void FpsCounter::update() {

	int curTime = SDL_GetTicks();
	this->frames++;
	if(this->lastTime + 1000 < curTime) {

		this->lastFps = frames;
		this->lastTime = SDL_GetTicks();
		this->frames = 0;

	}

}

int FpsCounter::getLastFps() {
	return this->lastFps;
}



FpsCounter::~FpsCounter(void)
{
}

}