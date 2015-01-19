#pragma once

#include <YuEngine\Object.h>
#include <YuEngine\Vertex.h>

class Block: public YuEngine::Object
{
public:
	Block(void) {
	};
	Block(float _x, float _y) {
		x = _x;
		y = _y;

	};
	virtual ~Block(void) {

	};
	float getX() {
		return x;
	}
	float getY() {
		return y;
	}
	bool isTransparent() {
		return transparent;
	}
	void setLightIndice(YuEngine::Color l) {
		lightIndice = l;
	}

	virtual void render();
	virtual void update();
	static float size;

protected:
	int id;
	bool transparent;
	float x;
	float y;
	int textX;
	int textY;

	YuEngine::Color lightIndice;

};

