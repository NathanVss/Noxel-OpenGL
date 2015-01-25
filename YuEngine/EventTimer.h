#pragma once


namespace YuEngine {

class EventTimer
{
public:
	EventTimer(void);
	EventTimer(int _ticksEvent);

	~EventTimer(void);
	void update();
	bool isOver();
	void reset();


private:
	int curTicks;
	int ticksEvent;

};

}