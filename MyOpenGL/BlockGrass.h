#pragma once

#include "Block.h"

class BlockGrass: public Block
{
public:
	BlockGrass(void) : Block() {
		construct();
	};
	BlockGrass(float _x, float _y, float _z) : Block(_x,_y,_z) {
		construct();
	};
	~BlockGrass(void) {

	};

	void construct() {
		textX1 = 0;
		textY1 = 0;
		textX2 = 1;
		textY2 = 1;
		transparent = false;
		hasBoundingbox = true;

		YuEngine::Color _particlesColors;
		_particlesColors.r = 23.0f / 255;
		_particlesColors.g = 120.0f / 255;
		_particlesColors.b = 17.0f / 255;
		_particlesColors.a = 1.0f;
		particlesColors = _particlesColors;

		maxWaterQuantity = 0;
		waterQuantity = 0;

		id = Block::GrassId;
	}

};

