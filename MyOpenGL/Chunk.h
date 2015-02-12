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
	void render(bool obstacles);
	void update();
	void setBlock(Block* block);
	void deleteBlock(Block* block);
	Block**** getBlocks() {
		return blocks;
	}
	Block* getBlock(int x, int y, int z) {
		return blocks[x][y][z];
	}

	static int width;
	static int height;
	static int depth;

	float getX() {
		return x;
	}
	float getY() {
		return y;
	}

private:
	Block**** blocks;
	float x;
	float y;
};

