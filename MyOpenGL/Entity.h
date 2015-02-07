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

protected:

	bool destroy;

	float x;
	float y;
	float gravity;

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

	float width;
	float height;

	YuEngine::YuBoudingbox boundingBox;

};

