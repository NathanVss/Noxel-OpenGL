#pragma once

#include "EntityLiving.h"
#include <YuEngine\EventTimer.h>


class EntityMob : public EntityLiving
{
protected:
	YuEngine::EventTimer timerWayDecision;
	bool isHit;
	bool hitOnLeft;
	bool hitOnRight;
	float knockbackX;
	float knockbackY;

public:
	EntityMob(void);
	virtual ~EntityMob(void);
	virtual void update();
	void handleBehavior();
	virtual void render() = 0;
	virtual void onDead();
	
	void hit(float value, bool hitOnLeft, bool hitOnRight);
	void checkHit();
};

