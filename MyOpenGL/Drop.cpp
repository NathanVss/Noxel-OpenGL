#include "Drop.h"
#include "Container.h"
#include "Item.h"
#include "Player.h"
#include <YuEngine\GameRenderer.h>
#include <YuEngine\SpritesheetsManager.h>

Drop::Drop(Container *c, Item* _item, float _width, float _height) : Entity() {
	myContainer = c;
	affectedByGravity = true;
	width = _width;
	height = _height;

	item = _item;

	YuEngine::YuBoudingbox _boudingBox(x, y, width, height);
	_boudingBox.setContainer(container);
	boundingBox = _boudingBox;

	age = 0;
	maxAge = 60*60;

	velocityX = 0;
	velocityY = 10;
	followPlayer = false;
}


Drop::~Drop(void){

}

void Drop::update() {
	age++;
	if(age >= maxAge) {
		destroy = true;
		if(item) {
			delete item;
		}
	}

	float playerX = myContainer->getPlayer()->getX() + myContainer->getPlayer()->getWidth() / 2;
	float playerY = myContainer->getPlayer()->getY() - myContainer->getPlayer()->getHeight() / 2;
	float deltaX = playerX - x;
	float deltaY = playerY - y;

	float maxDist = 200 * 200;
	float minDist = 20*20;
	float dist = deltaX * deltaX + deltaY * deltaY;

	if(dist <= minDist) {
		destroy = true;
		
		myContainer->getPlayer()->giveItem(item);
	}
	if(dist <= maxDist) {

		velocityX = playerX - x;
		velocityY = playerY - y;
		velocityX *= 0.1f;
		velocityY *= 0.1f;

		x += velocityX;
		y += velocityY;
		fixBoundingboxPosition();
		followPlayer = true;
	} else {

		if(followPlayer) {
			followPlayer = false;
			velocityX = 0;
			velocityY = 0;
		}
		Entity::applyGravity();

		Entity::handleMoving();
		
	}
	Entity::update();
}

void Drop::render() {


	item->render(width, height, x, y);

}