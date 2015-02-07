#pragma once

#include "Block.h"

class BlockSand : public Block
{
public:
	BlockSand(float _x, float _y) : Block(_x, _y) {
		textX = 4;
		textY = 0;
		transparent = false;
		hasBoundingbox = true;

		YuEngine::Color _particlesColors;
		_particlesColors.r = 225.0f / 255;
		_particlesColors.g = 212.0f / 255;
		_particlesColors.b = 134.0f / 255;
		_particlesColors.a = 1.0f;
		particlesColors = _particlesColors;

		maxWaterQuantity = 0;
		waterQuantity = 0;

		id = Block::SandId;
	};
	~BlockSand(void);
};

