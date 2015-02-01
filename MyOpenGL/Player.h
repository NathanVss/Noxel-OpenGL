#pragma once

#include "Entity.h"
#include <YuEngine\YuBoudingbox.h>
#include <YuEngine\EventTimer.h>

class Player: public Entity
{
public:
	Player(void);
	~Player(void);
	void teleport(float _x, float _y);
	void update();
	void render();
	void placeBoundingBox();
	void transposeBBoxPosToPlayer(glm::vec2 boundingBoxPos);
	void setSpeedX(float _speedX) {
		speedX = _speedX;
	}

	void handleDigging();
	void handleMoving();
	void handleFlyMoving();

	void setFly(bool _fly) {
		fly = _fly;
	}
	
private:
	float speedX;
	float jumpHeight;

	bool jumping;

	bool goingLeft;
	bool goingRight;
	bool moving;

	bool fly;

	YuEngine::EventTimer legsAnimationTimer;
	YuEngine::EventTimer jumpTimer;

};

