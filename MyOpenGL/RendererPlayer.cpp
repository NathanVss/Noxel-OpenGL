#include "RendererPlayer.h"
#include "Player.h"
#include "Container.h"
#include "Item.h"

#include <YuEngine\GameRenderer.h>
#include <YuEngine\SpritesheetsManager.h>

RendererPlayer::RendererPlayer(void)
{
}

RendererPlayer::RendererPlayer(Container* c, Player* _player) : Object(c) {
	legsAnimationTimer = YuEngine::EventTimer(0);
	player = _player;
	pixelSize = 3;
	armAngle = 0;
	armAnglePhase = false;
}


RendererPlayer::~RendererPlayer(void)
{
}

void RendererPlayer::render() {


	int walkSpeed = 8;
	float x = player->getX();
	float y = player->getY();
	float width = player->getWidth();
	float height = player->getHeight();


	if(player->getGoingRight()) {
		

		if(player->getMoving()) {

			legsAnimationTimer.update();
			if(legsAnimationTimer.isUnder(0, walkSpeed)) {
				myContainer->getGameRenderer()->addGlyph(x, y, width, height, 16.0f, 1.0f, 1.0f, 1.0f, 1.0f, myContainer->getSpritesheetsManager()->getMiscSpritesheet(), 10,12, 12,16);


			} else if(legsAnimationTimer.isUnder(walkSpeed, 2*walkSpeed)) {
				myContainer->getGameRenderer()->addGlyph(x, y, width, height, 16.0f, 1.0f, 1.0f, 1.0f, 1.0f, myContainer->getSpritesheetsManager()->getMiscSpritesheet(), 14,12, 16,16);


			} else if(legsAnimationTimer.isUnder(2*walkSpeed, 3*walkSpeed)) {
				myContainer->getGameRenderer()->addGlyph(x, y, width, height, 16.0f, 1.0f, 1.0f, 1.0f, 1.0f, myContainer->getSpritesheetsManager()->getMiscSpritesheet(), 12,12, 14,16);

			} else if(legsAnimationTimer.isOver(3*walkSpeed)) {
				myContainer->getGameRenderer()->addGlyph(x, y, width, height, 16.0f, 1.0f, 1.0f, 1.0f, 1.0f, myContainer->getSpritesheetsManager()->getMiscSpritesheet(), 14,12, 16,16);

				if(legsAnimationTimer.isOver(4*walkSpeed)) {
					legsAnimationTimer.reset();
				}
			}

		} else {


			myContainer->getGameRenderer()->addGlyph(x, y, width, height, 16.0f, 1.0f, 1.0f, 1.0f, 1.0f, myContainer->getSpritesheetsManager()->getMiscSpritesheet(), 14,12, 16,16);

			legsAnimationTimer.reset();

		}


	} else if(player->getGoingLeft()) {

		if(player->getMoving()) {

			legsAnimationTimer.update();
			if(legsAnimationTimer.isUnder(0, walkSpeed)) {

				myContainer->getGameRenderer()->addGlyph(x, y, width, height, 16.0f, 1.0f, 1.0f, 1.0f, 1.0f, myContainer->getSpritesheetsManager()->getMiscSpritesheet(), 10,8, 12,12);
			} else if(legsAnimationTimer.isUnder(walkSpeed, 2*walkSpeed)) {
				myContainer->getGameRenderer()->addGlyph(x, y, width, height, 16.0f, 1.0f, 1.0f, 1.0f, 1.0f, myContainer->getSpritesheetsManager()->getMiscSpritesheet(), 14,8, 16,12);


			} else if(legsAnimationTimer.isUnder(2*walkSpeed, 3*walkSpeed)) {
				myContainer->getGameRenderer()->addGlyph(x, y, width, height, 16.0f, 1.0f, 1.0f, 1.0f, 1.0f, myContainer->getSpritesheetsManager()->getMiscSpritesheet(), 12,8, 14,12);


			} else if(legsAnimationTimer.isOver(3*walkSpeed)) {
				myContainer->getGameRenderer()->addGlyph(x, y, width, height, 16.0f, 1.0f, 1.0f, 1.0f, 1.0f, myContainer->getSpritesheetsManager()->getMiscSpritesheet(), 14,8, 16,12);

				if(legsAnimationTimer.isOver(4*walkSpeed)) {
					legsAnimationTimer.reset();
				}
			}
		} else {
			myContainer->getGameRenderer()->addGlyph(x, y, width, height, 16.0f, 1.0f, 1.0f, 1.0f, 1.0f, myContainer->getSpritesheetsManager()->getMiscSpritesheet(), 14,8, 16,12);

			legsAnimationTimer.reset();


		}

	}
	renderArm();

}

void RendererPlayer::renderArm() {
	float x = player->getX();
	float y = player->getY();


	float armWidth = pixelSize*8;
	float armHeight = pixelSize*8;
	float armSpeed = 10.0f;

	int armTexX;
	int armTexY;
	float armX;
	float armY;
	float rotX;
	float rotY;

	float lowAngle;
	float maxAngle;
	float idleAngle;

	// where must be placed the top left corner of armtext relative to topLeft player texture
	float armTexOffsetY = 12;
	// The same
	float armTexOffsetX;

	// Rotation point offset from topleft of arm texture
	float armRotOffsetY = 4;
	float armRotOffsetX;

	if(player->getGoingLeft()) {
		armTexOffsetX = 0;
		armRotOffsetX = armWidth - pixelSize;

		armTexX = 15;
		armTexY = 7;

		lowAngle = -90;
		maxAngle = 0;
		idleAngle = 90;
	} else {
		armTexOffsetX = 4;
		armRotOffsetX = pixelSize;

		armTexX = 14;
		armTexY = 7;

		lowAngle = 0;
		maxAngle = 90;
		idleAngle = -90;
	}

	armX = x + armTexOffsetX * pixelSize;
	armY = y - armTexOffsetY * pixelSize;

	rotX = armX + armRotOffsetX;
	rotY = armY - pixelSize * armRotOffsetY;

	if(player->getIsDigging()) {


		if(!armAnglePhase) {
			armAngle -= armSpeed;
			if(armAngle <= lowAngle) {
				armAnglePhase = true;
			}
		} else {
			armAngle += armSpeed;
			if(armAngle >= maxAngle) {
				armAnglePhase = false;

			}
		}


	} else {
		armAngle = idleAngle;
	}



	myContainer->getGameRenderer()->addGlyph(armX, armY, armWidth, armHeight, rotX, rotY, armAngle, 20.0f, 1.0f, 1.0f, 1.0f, 1.0f, myContainer->getSpritesheetsManager()->getMiscSpritesheet(), armTexX,armTexY);

	Item* heldItem = player->getHeldItem();

	if(heldItem) {
		float height = heldItem->getHeldingHeight();
		float width = height * heldItem->getWidthHeightRatio();

		// Offset relative to top of arm texture to place bottom of item
		float heldItemTexOffset = 4;

		float itemX;
		if(player->getGoingRight()) {
			itemX = armX + armWidth - width / 2;
		} else {
			itemX = armX - width / 2;
		}

		float itemY = armY - heldItemTexOffset  * pixelSize + height;

		heldItem->render(width, height, itemX, itemY, rotX, rotY, armAngle, 19);

	}
}