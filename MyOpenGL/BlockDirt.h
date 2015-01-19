#pragma once

#include "Block.h"

class BlockDirt : public Block
{
public:
	BlockDirt(float _x, float _y) : Block(_x, _y) {
		textX = 1;
		textY = 0;
		transparent = false;

	};
	~BlockDirt(void);
};

