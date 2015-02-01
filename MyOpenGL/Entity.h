#pragma once

#include "Object.h"
#include <YuEngine\YuBoudingbox.h>
#include <Dependecies\glm\glm.hpp>


class Entity: public Object
{
public:
	Entity(void);
	~Entity(void);
	glm::vec2 checkCollisions(float starX, float startY, float destX, float destY);

	float getX() {
		return x;
	}
	float getY() {
		return y;
	}


protected:
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

