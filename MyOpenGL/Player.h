#pragma once

#include <YuEngine\YuBoudingbox.h>
#include <YuEngine\EventTimer.h>
#include <YuEngine\KeyEvent.h>

#include "EntityLiving.h"

class QuickInventory;
class Item;
class RendererPlayer;
class HealthBuffer;
class GuiPlayerHealth;

enum class MovingStates {

	WALK,
	FLY

};

class Player: public EntityLiving
{
public:
	Player(void);
	Player(Container* c);
	virtual ~Player(void);
	void teleport(float _x, float _y);
	void update();
	void render();
	void renderArm();
	void placeBoundingBox();
	void updateOffsets();
	void transposeBBoxPosToPlayer(glm::vec2 boundingBoxPos);
	void giveItem(Item* item);
	void handleDigging();
	void handleMoving();
	void handleFlyMoving();
	void handleAction();
	void handleFalling();

	void setSpeedX(float _speedX) {
		speedX = _speedX;
	}
	void setMovingState(MovingStates state) {
		movingState = state;
	}
	bool getIsDigging() {
		return isDigging;
	}
	Item* getHeldItem() {
		return heldItem;
	}
	HealthBuffer* getHealthBuffer() {
		return healthBuffer;
	}

	
private:
	RendererPlayer* rendererPlayer;

	HealthBuffer* healthBuffer;
	GuiPlayerHealth* guiHealth;
	MovingStates movingState;

	int ticks;

	float jumpHeight;
	int fallingTicks;
	float fallingHeight;
	float affectedByFallingDamages;
	float fallingDamagesMutliplicator;

	float pixelSize;
	bool isDigging;

	float textureOffsetX;
	float textureOffsetY;
	float bboxOffsetX;
	float bboxOffsetY;

	int switchMode;

	Item* heldItem;

	YuEngine::KeyEvent leftClickEvent;
	YuEngine::KeyEvent rightClickEvent;
	YuEngine::KeyEvent switchEvent;
	YuEngine::EventTimer jumpTimer;

	QuickInventory* quickInventory;

};

