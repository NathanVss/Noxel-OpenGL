#pragma once

#include "Entity.h"

class EntityLiving : public Entity
{
public:
	EntityLiving(void);
	virtual ~EntityLiving(void);
	virtual void update();
	virtual void applyGravity();
	virtual void render() = 0;

	virtual float getHealth() {
		return health;
	}
	virtual float getMaxHealth() {
		return maxHealth;
	}
	virtual bool getDead() {
		return dead;
	}
protected:
	bool jumping;

	float speedX;
	float jumpVel;
	bool goingLeft;
	bool goingRight;
	bool moving;

	bool affectedByGravity;

	float lastX;
	float lastY;

	float health;
	float maxHealth;
	bool dead;

};

