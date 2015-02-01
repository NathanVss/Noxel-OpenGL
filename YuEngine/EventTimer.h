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
	bool isUnder(int a, int b);
	void setOver();
	bool isOver(int ticks);
	void reset();


private:
	int curTicks;
	int ticksEvent;

};

}