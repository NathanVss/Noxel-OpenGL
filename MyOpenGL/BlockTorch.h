#pragma once

#include "Block.h"

class LightRadius;

class BlockTorch : public Block
{
private:
	LightRadius* light;

public:
	BlockTorch(void);
	BlockTorch(float _x, float _y);
	~BlockTorch(void);
	void construct();


	virtual void onPlacing();
	virtual void render(bool flag);

};

