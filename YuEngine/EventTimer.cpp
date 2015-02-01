#include "EventTimer.h"

namespace YuEngine {

EventTimer::EventTimer(void)
{
}

EventTimer::EventTimer(int _ticksEvent)
{
	curTicks = 0;
	ticksEvent = _ticksEvent;
}

void EventTimer::update() {
	curTicks++;
}


bool EventTimer::isUnder(int a, int b) {

	return curTicks >= a && curTicks <= b;
}

bool EventTimer::isOver() {
	if(curTicks >= ticksEvent) {
		return true;
	}
	return false;
}
bool EventTimer::isOver(int ticks) {
	if(curTicks >= ticks) {
		return true;
	}
	return false;
}
void EventTimer::setOver() {
	curTicks = ticksEvent + 1;
}

void EventTimer::reset() {

	curTicks = 0;

}

EventTimer::~EventTimer(void)
{
}
}