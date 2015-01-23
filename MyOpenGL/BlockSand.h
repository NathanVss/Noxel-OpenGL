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
	};
	~BlockSand(void);
};

