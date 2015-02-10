#pragma once

#include "Object.h"
#include <YuEngine\YuBoudingbox.h>
#include <Dependecies\glm\glm.hpp>


class Entity: public Object
{
public:
	Entity(void);
	virtual ~Entity(void);
	glm::vec2 checkCollisions(float starX, float startY, float destX, float destY);
	virtual void handleMoving();
	virtual void applyGravity();

	virtual void update();
	virtual void render() = 0;

	float getX() {
		return x;
	}
	float getY() {
		return y;
	}
	YuEngine::YuBoudingbox getBoundingbox() {
		return boundingBox;
	}

	bool getDestroy() {
		return destroy;
	}
	void teleport(float _x, float _y) {
		x = _x;
		y = _y;
	}
	void fixBoundingboxPosition() {
		boundingBox.changePos(x, y);
	}
	float getWidth() {
		return width;
	}
	float getHeight() {

		return height;
	}

protected:

	bool destroy;

	float x;
	float y;
	float gravity;
	bool affectedByGravity;


	float velocityX;
	float velocityY;

	bool collideOnLeft;
	bool collideOnRight;
	bool collideOnTop;
	bool collideOnBottom;
	bool collideOnTopLeft;
	bool collideOnTopRight;
	bool collideOnBottomLeft;
	bool collideOnBottomRight;


	bool lastCollideOnLeft;
	bool lastCollideOnRight;
	bool lastCollideOnTop;
	bool lastCollideOnBottom;
	bool lastCollideOnTopLeft;
	bool lastCollideOnTopRight;
	bool lastCollideOnBottomLeft;
	bool lastCollideOnBottomRight;

	float lastX;
	float lastY;

	float width;
	float height;

	YuEngine::YuBoudingbox boundingBox;

};

