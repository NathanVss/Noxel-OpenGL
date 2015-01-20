#include "Player.h"
#include <YuEngine\Container.h>
#include <YuEngine\GameRenderer.h>
#include "Block.h"
#include <YuEngine\SpritesheetsManager.h>
#include <YuEngine\Input.h>

Player::Player(): Entity(){
	width = Block::size;
	height = Block::size;
	speedX = Block::size * 2;
	jumpHeight = Block::size * 2;
	jumping = false;
	YuEngine::YuBoudingbox _boudingBox(x, y, width, height);
	_boudingBox.setContainer(container);
	boudingBox = _boudingBox;
}

void Player::teleport(float _x, float _y) {
	x = _x;
	y = _y;
}

void Player::render() {

	container->getGameRenderer()->addGlyph(x, y, width, height, 16.0f, 1.0f, 1.0f, 1.0f, 1.0f, container->getSpritesheetsManager()->getBlocksSpritesheet(), 0,0);
}

void Player::update() {
	YuEngine::Input* input = this->container->getInput();

	velocityX = 0;
	velocityY = 0;
	if(input->getKeyQ()) {
		velocityX -= speedX;
	}
	if(input->getKeyD()) {
		velocityX += speedX;
	}
	if(input->getKeyZ()) {
		velocityY += speedX;
	}
	if(input->getKeyS()) {
		velocityY -= speedX;
	}
	if(input->getKeySpace()) {

		if(!jumping) {
			jumping = true;
			velocityY += jumpHeight;
		}
	}

	float destX = x + velocityX;
	float destY = y + velocityY;
	std::cout << "CurPos [" << x << ";" << y << "]" << std::endl;
	std::cout << "DestPos [" << destX << ";" << destY << "]" << std::endl;

	boudingBox.changePos(x, y);

	checkCollisions(destX, destY);
}

Player::~Player(void)
{
}
