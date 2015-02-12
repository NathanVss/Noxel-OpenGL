#pragma once

#include "Block.h"

class LightRadius;

class BlockTorch : public Block
{
private:
	LightRadius* light;
	int position;

public:
	BlockTorch(void);
	BlockTorch(float _x, float _y, float _z);
	~BlockTorch(void);
	void construct();

	virtual void update();
	virtual bool canBePlaced(float _x, float _y);
	virtual void onPlacing();
	virtual void onDestroy();
	virtual void render(bool flag);

};

