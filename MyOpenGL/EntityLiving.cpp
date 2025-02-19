#include "EntityLiving.h"


EntityLiving::EntityLiving(void) : Entity() {
	jumping = false;
	speedX = 5;
	jumpVel = 10;
	goingLeft = true;
	goingRight = false;
	moving = false;
	affectedByGravity = true;
	dead = false;
}


EntityLiving::~EntityLiving(void){
}

void EntityLiving::update() {
	Entity::update();

	if(health < 0) {
		dead = true;
	}

	if(velocityX > 0) {
		goingRight = true;
		goingLeft = false;
	} else if(velocityX < 0) {
		goingRight = false;
		goingLeft = true;
	}

	if(lastX != x || lastY != y) {
		moving = true;
	} else {
		moving = false;
	}
	lastX = x;
	lastY = y;

	Entity::applyGravity();
}