#pragma once

#include "Entity.h"
#include <YuEngine\YuBoudingbox.h>

class Player: public Entity
{
public:
	Player(void);
	~Player(void);
	void teleport(float _x, float _y);
	void update();
	void render();

	
private:
	float speedX;
	float jumpHeight;

	bool jumping;

};

