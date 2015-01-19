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
	};
	~BlockGrass(void) {

	};
};

