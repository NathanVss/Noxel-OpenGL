#pragma once

#include <YuEngine\Perlin2D.h>
#include "Object.h"
#include "World.h"

class Biome: public Object
{
public:
	Biome(void);
	Biome(float _baseX, float _firstBlockY);
	~Biome(void);
	virtual void generate() = 0;


	float getLastBlockX() {
		return baseX + length;
	}
	float getLastBlockY() {
		return lastBlockY;
	}
	void setFirstBlockYRelNoise(float firstBlockYRelAbs) {
		firstBlockYRelNoise = ( firstBlockYRelAbs - groundLevel ) / ( topLevel - groundLevel);
	}
protected:
	float groundLevel;
	float topLevel;
	float length;
	float baseX;
	float firstBlockY;
	float firstBlockYRelNoise;

	bool firstGenIteration;
	float lastBlockY;
	YuEngine::Perlin2D perlin;
};

