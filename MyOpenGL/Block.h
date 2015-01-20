#pragma once

#include <YuEngine\Object.h>
#include <YuEngine\Vertex.h>
#include <YuEngine\YuBoudingbox.h>

class Block: public YuEngine::Object
{
public:
	Block(void) {
	};
	Block(float _x, float _y) {
		x = _x;
		y = _y;
			boundingBox = YuEngine::YuBoudingbox(x, y, Block::size, Block::size);
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
	bool getHasBoudingbox() {
		return hasBoundingbox;
	}
	YuEngine::YuBoudingbox getBoundingbox() {
		return boundingBox;
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
	bool hasBoundingbox;

	YuEngine::YuBoudingbox boundingBox;
	YuEngine::Color lightIndice;

};

