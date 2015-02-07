#pragma once

#include "EntityMob.h"
#include <YuEngine\EventTimer.h>

class MobChicken : public EntityMob
{
protected:
	YuEngine::EventTimer legsAnimationTimer;
	int walkSpeed;

public:
	MobChicken(void);
	virtual ~MobChicken(void);

	virtual void update();
	virtual void render();
};

