#pragma once

#include <YuEngine\Object.h>
#include <YuEngine\Vertex.h>
#include <YuEngine\YuBoudingbox.h>

#include "Object.h"


class Item;

class Block: public Object
{
public:
	static int AirId;
	static int GrassId;
	static int DirtId;
	static int StoneId;
	static int SandId;
	static const int TorchId = 5;
	Block(void) {
		
		construct();
	};
	Block(float _x, float _y) {
		x = _x;
		y = _y;
		construct();
		boundingBox = YuEngine::YuBoudingbox(x, y+Block::size, Block::size, Block::size);

	};
	virtual ~Block(void) {

	};

	void construct() {
		YuEngine::Color c;
		c.r = 255;
		c.g = 255;
		c.b = 255;
		c.a = 255;
		lightIndice = c;
		emitParticlesOnDestroy = true;
		waterPressure = 0;
		age = 0;
		destructState = 0;
		destructStateAmount = 0;
		resistance = 10;
	}

	void setPosition(float _x, float _y) {
		x = _x;
		y = _y;
		boundingBox = YuEngine::YuBoudingbox(x, y+Block::size, Block::size, Block::size);

	}
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
	int getWaterPressure() {

		return waterPressure;
	}
	void setWaterPressure(int p) {
		waterPressure = p;
	}
	void addDestructState() {
		destructState++;
	}
	int getDestructState() {
		return destructState;
	}
	void addDestructStateAmount(int amount) {
		destructStateAmount += amount;
	}

	virtual bool canBePlaced(float _x, float _y) {
		return true;
	}

	virtual void onPlacing() {

	};

	int getTextX1() {
		return textX1;
	}
	int getTextY1() {
		return textY1;
	}
	int getTextX2() {
		return textX2;
	}
	int getTextY2() {
		return textY2;
	}

	virtual void onDestroy();
	virtual void render(bool obstacles);
	virtual void update();
	static float size;

protected:
	int id;
	int destructState;
	int destructStateAmount;
	int resistance;
	int lastHitTicks;

	int age;
	bool transparent;
	float x;
	float y;
	int textX1;
	int textY1;
	int textX2;
	int textY2;
	bool hasBoundingbox;
	bool emitParticlesOnDestroy;

	float maxWaterQuantity;
	float waterQuantity;
	int waterPressure;

	YuEngine::YuBoudingbox boundingBox;
	YuEngine::Color lightIndice;
	YuEngine::Color particlesColors;

};

