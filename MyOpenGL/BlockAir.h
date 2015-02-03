#pragma once

#include "Block.h"

class BlockAir: public Block
{
public:
	BlockAir() {
	};
	BlockAir(float _x, float _y) : Block(_x, _y) {
		transparent = true;
		textX = 2;
		textY = 0;
		hasBoundingbox = false;
		emitParticlesOnDestroy = false;
		YuEngine::Color _particlesColors;
		_particlesColors.r = 23.0f / 255;
		_particlesColors.g = 120.0f / 255;
		_particlesColors.b = 17.0f / 255;
		_particlesColors.a = 1.0f;
		particlesColors = _particlesColors;
	};
	~BlockAir(void) {
	};
};

