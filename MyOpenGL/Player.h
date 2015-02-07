#pragma once

#include <YuEngine\YuBoudingbox.h>
#include <YuEngine\EventTimer.h>
#include "EntityLiving.h"
#include <YuEngine\KeyEvent.h>

class Player: public EntityLiving
{
public:
	Player(void);
	void init();
	virtual ~Player(void);
	void teleport(float _x, float _y);
	void update();
	void render();
	void renderArm();
	void placeBoundingBox();
	void updateOffsets();
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
	float jumpHeight;
	bool fly;

	float armAngle;
	bool armAnglePhase;
	float pixelSize;
	bool isDigging;

	float textureOffsetX;
	float textureOffsetY;
	float bboxOffsetX;
	float bboxOffsetY;

	int switchMode;

	YuEngine::KeyEvent leftClickEvent;
	YuEngine::KeyEvent switchEvent;
	YuEngine::EventTimer legsAnimationTimer;
	YuEngine::EventTimer jumpTimer;

};

