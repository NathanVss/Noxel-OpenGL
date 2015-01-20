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
	};
	~BlockAir(void) {
	};
};

