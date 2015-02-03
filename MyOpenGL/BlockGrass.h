#pragma once

#include "Block.h"

class BlockGrass: public Block
{
public:
	BlockGrass(void){
	};
	BlockGrass(float _x, float _y) : Block(_x,_y) {
		textX = 0;
		textY = 0;
		transparent = false;
		hasBoundingbox = true;

		YuEngine::Color _particlesColors;
		_particlesColors.r = 23.0f / 255;
		_particlesColors.g = 120.0f / 255;
		_particlesColors.b = 17.0f / 255;
		_particlesColors.a = 1.0f;
		particlesColors = _particlesColors;


	};
	~BlockGrass(void) {

	};
};

