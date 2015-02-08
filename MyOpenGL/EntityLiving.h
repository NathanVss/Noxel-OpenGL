#pragma once

#include "Entity.h"

class EntityLiving : public Entity
{
public:
	EntityLiving(void);
	virtual ~EntityLiving(void);
	virtual void update();
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
	virtual bool getGoingRight() {
		return goingRight;
	}
	virtual bool getGoingLeft() {
		return goingLeft;
	}
	virtual bool getMoving() {
		return moving;
	}
protected:
	bool jumping;

	float speedX;
	float jumpVel;
	bool goingLeft;
	bool goingRight;
	bool moving;


	float lastX;
	float lastY;

	float health;
	float maxHealth;
	bool dead;

};

