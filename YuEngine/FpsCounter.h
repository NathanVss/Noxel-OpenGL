#pragma once

namespace YuEngine {
class FpsCounter
{
public:
	FpsCounter(void);
	~FpsCounter(void);
	void update();
	int getLastFps();

private:
	int lastTime;
	int frames;
	int lastFps;
};

}