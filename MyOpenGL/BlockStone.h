#pragma once

#include "Block.h"

class BlockStone : public Block
{
public:
	BlockStone(float _x, float _y) : Block(_x, _y) {
		textX = 5;
		textY = 0;
		transparent = false;
		hasBoundingbox = true;
	};
	virtual ~BlockStone(void) {

	};
};

