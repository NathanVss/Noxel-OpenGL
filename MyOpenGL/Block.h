#pragma once

#include <YuEngine\Object.h>
#include <YuEngine\Vertex.h>
#include <YuEngine\YuBoudingbox.h>

#include "Object.h"

class Block: public Object
{
public:
	static int AirId;
	static int GrassId;
	static int DirtId;
	static int StoneId;
	static int SandId;
	Block(void) {
	};
	Block(float _x, float _y) {
		x = _x;
		y = _y;
		boundingBox = YuEngine::YuBoudingbox(x, y+Block::size, Block::size, Block::size);
		YuEngine::Color c;
		c.r = 255;
		c.g = 255;
		c.b = 255;
		c.a = 255;
		lightIndice = c;
		emitParticlesOnDestroy = true;
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

	bool canStoreWater() {
		return maxWaterQuantity > waterQuantity;
	}
	void setWaterQuantity(float quantity) {
		waterQuantity = quantity;
	}
	float getWaterQuantity() {

		return waterQuantity;
	}
	float getWaterQuantityCanTake() {

		float quantity = maxWaterQuantity - waterQuantity;
		if(quantity < 0) {
			return 0;
		}
		return quantity;
	}
	void addWaterQuantity(float quantity) {
		waterQuantity += quantity;
	}
	int getId() {
		return id;
	}


	virtual void onDestroy();

	virtual void render(bool obstacles);
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
	bool emitParticlesOnDestroy;

	float maxWaterQuantity;
	float waterQuantity;

	YuEngine::YuBoudingbox boundingBox;
	YuEngine::Color lightIndice;
	YuEngine::Color particlesColors;

};

