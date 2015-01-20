#pragma once

#include <YuEngine\Object.h>
#include <vector>
#include "Chunk.h"
#include <YuEngine\Vertex.h>

#include <Dependecies\glm\glm.hpp>
#include <Dependecies\glm\gtc\type_ptr.hpp>
#include <Dependecies\glm\gtx\transform.hpp>

class Block;

class World: public YuEngine::Object
{
public:
	World(void) {
		chunksHoriz = 20;
		chunksVert = 5;

	};
	static int worldHeight;

	~World(void);
	void init();
	void generate();
	void render();
	void update();
	void setBlock(Block* block);
	Block* getBlock(float x, float y);
	std::vector<Chunk*>* getActiveChunks() {
		return &activeChunks;
	}

private:
	int chunksHoriz;
	int chunksVert;
	std::vector<Chunk*> chunks;
	std::vector<Chunk*> activeChunks;
};

