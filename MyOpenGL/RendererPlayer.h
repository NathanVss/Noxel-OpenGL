#pragma once

#include "Object.h"
#include <YuEngine\EventTimer.h>

class Player;

class RendererPlayer : public Object
{
public:
	RendererPlayer(void);
	RendererPlayer(Container* c, Player* player);
	~RendererPlayer(void);
	void update();
	void render();
	void renderArm();


	float getPixelSize() {
		return pixelSize;
	}

private:
	float pixelSize;
	float armAngle;
	bool armAnglePhase;

	Player* player;
	YuEngine::EventTimer legsAnimationTimer;
};

