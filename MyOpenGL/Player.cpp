#include "Player.h"
#include <YuEngine\Container.h>
#include <YuEngine\GameRenderer.h>

Player::Player(float _x, float _y){
	x = _x;
	y = _y;
	YuEngine::YuBoudingbox _boudingBox(x, y, width, height);
	_boudingBox.setContainer(container);
	boudingBox = _boudingBox;
}

void Player::teleport(float _x, float _y) {
	x = _x;
	y = _y;
}

void Player::render() {

	//container->getGameRenderer()->addGlyph(
}

void Player::update() {
	boudingBox.changePos(x, y);
}

Player::~Player(void)
{
}
