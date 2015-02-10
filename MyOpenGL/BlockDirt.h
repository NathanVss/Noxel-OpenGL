#pragma once

#include "Block.h"

class BlockDirt : public Block
{
public:
	BlockDirt(float _x, float _y, float _z) : Block(_x, _y, _z) {
		textX1 = 1;
		textY1 = 0;
		textX2 = 2;
		textY2 = 1;
		transparent = false;
		hasBoundingbox = true;

		YuEngine::Color _particlesColors;
		_particlesColors.r = 106.0f / 255;
		_particlesColors.g = 80.0f / 255;
		_particlesColors.b = 52.0f / 255;
		_particlesColors.a = 1.0f;
		particlesColors = _particlesColors;

		maxWaterQuantity = 0;
		waterQuantity = 0;

		id = Block::DirtId;
	};
	~BlockDirt(void);
};

