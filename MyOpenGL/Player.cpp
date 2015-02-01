#include "Player.h"
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

Player::Player(): Entity(){
	width = Block::size * 1.5;
	height = Block::size*2 * 1.5;
	jumpHeight = Block::size * 2;
	speedX = 15;

	// Bounding Box
	YuEngine::YuBoudingbox _boudingBox(0, 0, width-10*3, height-6*3);
	_boudingBox.setContainer(container);
	boundingBox = _boudingBox;
	placeBoundingBox();
	
	jumping = false;
	goingLeft = true;
	goingRight = false;
	moving = false;
	fly = true;

	legsAnimationTimer = YuEngine::EventTimer(0);
	jumpTimer = YuEngine::EventTimer(60);
}

void Player::teleport(float _x, float _y) {
	x = _x;
	y = _y;
	placeBoundingBox();
}


void Player::placeBoundingBox() {
	boundingBox.changePos(x + 4*3,y - 6*3);
}
void Player::transposeBBoxPosToPlayer(glm::vec2 boundingBoxPos) {

	x = boundingBoxPos.x - 4*3;
	y = boundingBoxPos.y + 6*3;

}

void Player::render() {

	//boundingBox.render(myContainer);
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

}




void Player::update() {



	if(fly) {
		handleFlyMoving();
	} else {
		handleMoving();

	}
	handleDigging();

}

void Player::handleFlyMoving() {
	YuEngine::Input* input = myContainer->getInput();

	velocityY = 0;
	velocityX = 0;

	if(input->getKeyZ()) {
		velocityY += speedX;
	}
	if(input->getKeyS()) {
		velocityY -= speedX;
	}
	if(input->getKeyQ()) {
		velocityX -= speedX;
	}
	if(input->getKeyD()) {
		velocityX += speedX;
	}

	if(velocityX > 0) {
		goingRight = true;
		goingLeft = false;
	} else if(velocityX < 0) {
		goingRight = false;
		goingLeft = true;
	}

	float destX = boundingBox.getX1() + velocityX;
	float destY = boundingBox.getY1() + velocityY;


	if(boundingBox.getX1() != destX) {
		moving = true;
	} else {
		moving = false;
	}

	glm::vec2 endLocation = checkCollisions(boundingBox.getX1(), boundingBox.getY1(), destX, destY);
	boundingBox.changePos(endLocation.x, endLocation.y);
	transposeBBoxPosToPlayer(endLocation);
}

void Player::handleMoving() {
	YuEngine::Input* input = myContainer->getInput();

	velocityX = 0;

	if(!collideOnBottom) {

		if(velocityY >= -100) {
			velocityY -= gravity;
		}

	} else {
		velocityY = 0;
	}

	if(myContainer->getFocusManager()->getPlayerFocus()) {

		//if(input->getKeyZ()) {
		//	velocityY += speedX;
		//}
		if(input->getKeyS()) {
			velocityY -= speedX;
		}
		if(input->getKeySpace() && !jumping) {

			jumping = true;
			jumpTimer.reset();
			velocityY = 25;
		}
		if(input->getKeyQ()) {
			velocityX -= speedX;
		}
		if(input->getKeyD()) {
			velocityX += speedX;
		}

	}


	if(velocityX > 0) {
		goingRight = true;
		goingLeft = false;
	} else if(velocityX < 0) {
		goingRight = false;
		goingLeft = true;
	}


	if(jumping && collideOnBottom) {
		jumping = false;
	}

	float destX = boundingBox.getX1() + velocityX;
	float destY = boundingBox.getY1() + velocityY;


	if(boundingBox.getX1() != destX) {
		moving = true;
	} else {
		moving = false;
	}

	// On simule le déplacement de la BBox
	glm::vec2 endLocation = checkCollisions(boundingBox.getX1(), boundingBox.getY1(), destX, destY);
	// On la mets à l'endroit final
	boundingBox.changePos(endLocation.x, endLocation.y);
	// On place le joueur en fonction de placement final de la BBox
	transposeBBoxPosToPlayer(endLocation);

}

void Player::handleDigging() {

	if(myContainer->getInput()->getLeftClick()) {
		YuEngine::YuBoudingbox cameraBox = myContainer->getCamera()->getCameraBox();
		glm::vec2 mouseWorld(cameraBox.getX1() + myContainer->getInput()->getMouseX(), cameraBox.getY1() - myContainer->getInput()->getMouseY());

		mouseWorld.x = floor(mouseWorld.x / Block::size) * 32;
		mouseWorld.y = floor(mouseWorld.y / Block::size) * 32;

		BlockAir* blockAir = new BlockAir(mouseWorld.x, mouseWorld.y);
		myContainer->getWorld()->setBlock(blockAir);

		std::cout << "Mouse : " << mouseWorld.x << ";" << mouseWorld.y << std::endl;
	}

}

Player::~Player(void)
{
}
