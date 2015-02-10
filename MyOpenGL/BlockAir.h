#pragma once

#include "Block.h"

class BlockAir: public Block
{
public:
	BlockAir() {
	};
	BlockAir(float _x, float _y, float _z) : Block(_x, _y, _z) {
		transparent = true;
		textX1 = 2;
		textY1 = 0;
		textX2 = 3;
		textY2 = 1;
		hasBoundingbox = false;
		emitParticlesOnDestroy = false;
		YuEngine::Color _particlesColors;
		_particlesColors.r = 23.0f / 255;
		_particlesColors.g = 120.0f / 255;
		_particlesColors.b = 17.0f / 255;
		_particlesColors.a = 1.0f;
		particlesColors = _particlesColors;
		maxWaterQuantity = 100;
		waterQuantity = 0;

		id = Block::AirId;
	};
	~BlockAir(void) {
	};
};

