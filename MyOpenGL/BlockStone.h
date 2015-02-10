#pragma once

#include "Block.h"

class BlockStone : public Block
{
public:
	BlockStone(float _x, float _y, float _z) : Block(_x, _y, _z) {
		textX1 = 5;
		textY1 = 0;
		textX2 = 6;
		textY2 = 1;
		transparent = false;
		hasBoundingbox = true;

		YuEngine::Color _particlesColors;
		_particlesColors.r = 149.0f / 255;
		_particlesColors.g = 149.0f / 255;
		_particlesColors.b = 149.0f / 255;
		_particlesColors.a = 1.0f;
		particlesColors = _particlesColors;

		maxWaterQuantity = 0;
		waterQuantity = 0;

		id = Block::StoneId;
	};
	virtual ~BlockStone(void) {

	};
};

