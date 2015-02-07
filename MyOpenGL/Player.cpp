#include "Player.h"
#include "EntityManager.h"
#include <YuEngine\Container.h>
#include <YuEngine\Camera2D.h>
#include <YuEngine\GameRenderer.h>
#include "Block.h"
#include <YuEngine\SpritesheetsManager.h>
#include <YuEngine\Input.h>
#include "Container.h"
#include "BlockAir.h"
#include "World.h"
#include "FocusManager.h"
#include <math.h>
Player::Player(): EntityLiving(){
	pixelSize = 3;
	textureOffsetX = 0;
	textureOffsetY = 4;

	width = pixelSize * 2 * 8;
	height = pixelSize * 4 * 8;
	jumpHeight = 25;
	speedX = 15;
	updateOffsets();

	// Bounding Box
	YuEngine::YuBoudingbox _boudingBox(0, 0, width-pixelSize*9, height-pixelSize*4);
	_boudingBox.setContainer(container);
	boundingBox = _boudingBox;
	placeBoundingBox();

	legsAnimationTimer = YuEngine::EventTimer(0);
	jumpTimer = YuEngine::EventTimer(60);

	armAngle = 0;
	armAnglePhase = false;
	isDigging = false;

	switchMode = 0;
}

void Player::init() {

	leftClickEvent = YuEngine::KeyEvent(YuEngine::KeyName::mouseLeft, myContainer->getInput());
	switchEvent = YuEngine::KeyEvent(YuEngine::KeyName::w, myContainer->getInput());
}

void Player::teleport(float _x, float _y) {
	x = _x;
	y = _y;
	placeBoundingBox();
}

void Player::updateOffsets() {
	
	if(goingLeft) {
		bboxOffsetX = 3;
		bboxOffsetY = 4;
	} else if(goingRight) {
		bboxOffsetX = 2;
		bboxOffsetY = 4;
	}
}

void Player::placeBoundingBox() {
		boundingBox.changePos(x + bboxOffsetX*pixelSize,y - bboxOffsetY*pixelSize);
}
void Player::transposeBBoxPosToPlayer(glm::vec2 boundingBoxPos) {
	x = boundingBoxPos.x - bboxOffsetX*pixelSize;
	y = boundingBoxPos.y + bboxOffsetY*pixelSize;
}

void Player::render() {

	//myContainer->getGameRenderer()->addGlyph(boundingBox.getX1(), boundingBox.getY1(),boundingBox.getWidth(), boundingBox.getHeight(), 15.5f, 1.0f, 1.0f, 1.0f, 1.0f,myContainer->getSpritesheetsManager()->getBlocksSpritesheet(), 3,0);
	
	int walkSpeed = 8;
	if(goingRight) {
		

		if(moving) {

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


	} else if(goingLeft) {

		if(moving) {

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

void Player::renderArm() {

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

	if(goingLeft) {
		armTexX = 15;
		armTexY = 7;

		armX = x;
		armY = y - 17*pixelSize + 5 * pixelSize;

		rotX = armX + armWidth - pixelSize * 1;
		rotY = armY - pixelSize * 4;

		lowAngle = -90;
		maxAngle = 0;
		idleAngle = 90;
	} else {
		armTexX = 14;
		armTexY = 7;

		armX = x + 4 * pixelSize;
		armY = y - 17*pixelSize + 5 * pixelSize;

		rotX = armX + pixelSize * 1;
		rotY = armY - pixelSize * 4;

		lowAngle = 0;
		maxAngle = 90;

		idleAngle = -90;
	}

	if(isDigging) {


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
}



void Player::update() {

	EntityLiving::update();

	if(fly) {
		handleFlyMoving();
	} else {
		handleMoving();

	}
	handleDigging();
	updateOffsets();

	switchEvent.update();
	if(switchEvent.getEvent()) {
		if(switchMode == 0) {
			switchMode = 1;
		} else if(switchMode == 1) {
			switchMode = 0;
		}
	}

}

void Player::handleFlyMoving() {
	affectedByGravity = false;
	YuEngine::Input* input = myContainer->getInput();

	velocityX = 0;
	velocityY = 0;
	if(myContainer->getFocusManager()->getPlayerFocus()) {

		if(input->getKeyZ()) {
			velocityY = speedX;
		}
		if(input->getKeyS()) {
			velocityY = -speedX;
		}
		if(input->getKeyQ()) {
			velocityX = -speedX;
		}
		if(input->getKeyD()) {
			velocityX = speedX;
		}
	}

	float destX = boundingBox.getX1() + velocityX;
	float destY = boundingBox.getY1() + velocityY;


	glm::vec2 endLocation = checkCollisions(boundingBox.getX1(), boundingBox.getY1(), destX, destY);
	boundingBox.changePos(endLocation.x, endLocation.y);
	transposeBBoxPosToPlayer(endLocation);
}

void Player::handleMoving() {
	affectedByGravity = true;

	YuEngine::Input* input = myContainer->getInput();

	velocityX = 0;
	if(myContainer->getFocusManager()->getPlayerFocus()) {

		if(input->getKeyS()) {
			velocityY = -speedX;
		}
		if(input->getKeySpace() && !jumping) {

			jumping = true;
			jumpTimer.reset();
			velocityY = jumpHeight;
		}
		if(input->getKeyQ()) {
			velocityX = -speedX;
		}
		if(input->getKeyD()) {
			velocityX = speedX;
		}

	}


	if(jumping && collideOnBottom) {
		jumping = false;
	}

	float destX = boundingBox.getX1() + velocityX;
	float destY = boundingBox.getY1() + velocityY;

	// On simule le déplacement de la BBox
	glm::vec2 endLocation = checkCollisions(boundingBox.getX1(), boundingBox.getY1(), destX, destY);
	// On la mets à l'endroit final
	boundingBox.changePos(endLocation.x, endLocation.y);
	// On place le joueur en fonction de placement final de la BBox
	transposeBBoxPosToPlayer(endLocation);

}

void Player::handleDigging() {

	leftClickEvent.update();
	if(leftClickEvent.getEvent()) {
		YuEngine::Position mousePos = myContainer->getCamera()->getMouseAbsPos(myContainer->getInput()->getMouseX(), myContainer->getInput()->getMouseY());

		myContainer->getEntityManager()->hit(mousePos.x, mousePos.y);
	}
	if(myContainer->getInput()->getLeftClick()) {
		YuEngine::Position mousePos = myContainer->getCamera()->getMouseAbsPos(myContainer->getInput()->getMouseX(), myContainer->getInput()->getMouseY());
		glm::vec2 mouseWorld;
		mouseWorld.x = floor(mousePos.x / Block::size) * 32;
		mouseWorld.y = floor(mousePos.y / Block::size) * 32;
		Block* curBlock = myContainer->getWorld()->getBlock(mouseWorld.x, mouseWorld.y);

		if(switchMode == 0) {
			curBlock->setWaterQuantity(100);

		} else if(switchMode == 1) {

			if(curBlock->getId() != Block::AirId) {

				curBlock->onDestroy();

				BlockAir* blockAir = new BlockAir(mouseWorld.x, mouseWorld.y);
				myContainer->getWorld()->setBlock(blockAir);
				isDigging = true;
			}
		}

	} else {
		isDigging = false;
	}

}

Player::~Player(void)
{
}
