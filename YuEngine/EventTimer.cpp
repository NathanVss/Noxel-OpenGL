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

bool EventTimer::isOver() {
	if(curTicks >= ticksEvent) {
		return true;
	}
	return false;
}

void EventTimer::reset() {

	curTicks = 0;

}

EventTimer::~EventTimer(void)
{
}
}