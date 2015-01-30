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

Player::Player(): Entity(){
	width = Block::size;
	height = Block::size*2;
	//speedX = Block::size * 1;
	speedX = 10;
	jumpHeight = Block::size * 2;
	jumping = false;
	YuEngine::YuBoudingbox _boudingBox(x, y+height, width, height);
	_boudingBox.setContainer(container);
	boundingBox = _boudingBox;
}

void Player::teleport(float _x, float _y) {
	x = _x;
	y = _y;
}

void Player::render() {

	myContainer->getGameRenderer()->addGlyph(x, y, width, height, 16.0f, 1.0f, 1.0f, 1.0f, 1.0f, myContainer->getSpritesheetsManager()->getBlocksSpritesheet(), 1,0);
	//boundingBox.render(myContainer);
	myContainer->getGameRenderer()->addGlyph(boundingBox.getX1(), boundingBox.getY1(), width, height, 18.0f, 1.0f, 1.0f, 1.0f, 1.0f, myContainer->getSpritesheetsManager()->getBlocksSpritesheet(), 3,0);

}

void Player::update() {
	YuEngine::Input* input = myContainer->getInput();

	velocityX = 0;
	velocityY = 0;
	if(input->getKeyQ()) {
		velocityX -= speedX;
	}
	if(input->getKeyD()) {
		velocityX += speedX;
	}
	if(!collideOnBottom) {
		if(velocityY == 0) {
			velocityY = -1.0f;
		}
		velocityY *= gravity;
		if(velocityY > 0) {
			velocityY = -velocityY;
		}

	}
	if(input->getKeyZ()) {
		velocityY += speedX;
	}
	if(input->getKeyS()) {
		velocityY -= speedX;
	}
	if(input->getKeySpace() && !jumping) {

		jumping = true;
		velocityY += jumpHeight;
	}
	if(jumping && collideOnBottom) {
		jumping = false;
	}

	float destX = x + velocityX;
	float destY = y + velocityY;

	checkCollisions(destX, destY);
	
	boundingBox.changePos(x, y);

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
