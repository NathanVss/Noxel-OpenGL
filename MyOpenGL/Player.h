#pragma once

#include <YuEngine\Object.h>
#include <YuEngine\YuBoudingbox.h>

class Player: public YuEngine::Object
{
public:
	Player(void) {};
	Player(float _x, float _y);
	~Player(void);
	void teleport(float _x, float _y);
	void update();
	void render();
private:
	float x;
	float y;
	float width;
	float height;
	YuEngine::YuBoudingbox boudingBox;
};

