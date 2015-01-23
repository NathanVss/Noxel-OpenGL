#pragma once

#include "Object.h"

class Block;
class YuEngine::Container;

class Chunk : public Object
{
public:
	Chunk() {
	};
	Chunk(float _x, float _y);
	~Chunk(void);

	void init();
	void render();
	void setBlock(Block* block);
	Block*** getBlocks() {
		return blocks;
	}
	Block* getBlock(int x, int y) {
		return blocks[x][y];
	}

	static int width;
	static int height;

	float getX() {
		return x;
	}
	float getY() {
		return y;
	}

private:
	Block*** blocks;
	float x;
	float y;
};

