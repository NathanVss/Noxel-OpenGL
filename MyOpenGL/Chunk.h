#pragma once

#include <YuEngine\Object.h>

class Block;
class YuEngine::Container;

class Chunk : public YuEngine::Object
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

