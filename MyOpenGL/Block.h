#pragma once

#include <YuEngine\Object.h>
#include <YuEngine\Vertex.h>
#include <YuEngine\YuBoudingbox.h>

#include "Object.h"


class Item;

class Block: public Object
{
public:
	static const float size;
	static const int AirId = 0;
	static const int GrassId = 1;
	static const int DirtId = 2;
	static const int StoneId = 3;
	static const int SandId = 4;
	static const int TorchId = 5;


	static const int landZ = 1;
	static const int frontZ = 2;

	Block(void);
	Block(float _x, float _y, float _z);
	virtual ~Block(void);
	void construct();

	virtual void onDestroy();
	virtual void render(bool obstacles);
	virtual void update();
	virtual bool canBePlaced(float _x, float _y);
	virtual void onPlacing();

	void addDestructStateAmount(int amount);
	int getId();
	int getWaterPressure();
	void setWaterPressure(int p);
	void addDestructState();
	int getDestructState();
	void setPosition(float _x, float _y);
	float getX();
	float getY();
	int getTextX1();
	int getTextY1();
	int getTextX2();
	int getTextY2();
	bool isTransparent();
	void setLightIndice(YuEngine::Color l);
	bool getHasBoudingbox();
	YuEngine::YuBoudingbox getBoundingbox();
	bool canStoreWater();
	void setWaterQuantity(float quantity);
	float getWaterQuantity();
	float getWaterQuantityCanTake();
	void addWaterQuantity(float quantity);

	int getZ() {
		return z;
	}
	void setPosition(float _x, float _y, int _z) {
		x = _x;
		y = _y;
		z = _z;
	}


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
	int z;
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

