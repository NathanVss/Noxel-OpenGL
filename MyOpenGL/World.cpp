#include "World.h"
#include "Block.h"
#include <YuEngine\Perlin2D.h>
#include "BlockGrass.h"
#include <iostream>
#include "BlockDirt.h"
#include "BiomePlains.h"
#include "Container.h"
#include "BiomeDesert.h"

#include "WorldGenCaves.h"
#include <YuEngine\Camera2D.h>
#include <YuEngine\Container.h>

int World::worldHeight = 0;
int World::worldWidth = 0;

World::~World(void){
	for(int i = 0; i < chunks.size(); i++) {
		delete chunks[i];
	}
}

void World::update() {
	float radius = 24;
	radius *= Block::size;
	glm::vec2 cameraPos = myContainer->getCamera()->getPosition();

	activeChunks.clear();
	for(int i = 0; i < chunks.size(); i++) {

		if(chunks[i]->getX() + Chunk::width*Block::size < cameraPos.x - radius) {
			continue;
		}
		if(chunks[i]->getX() > cameraPos.x + radius) {
			continue;
		}
		if(chunks[i]->getY() > cameraPos.y + radius) {
			continue;
		}
		if(chunks[i]->getY() + Chunk::height*Block::size < cameraPos.y - radius) {
			continue;
		}
		activeChunks.push_back(chunks[i]);
	}

	for(int i = 0; i < activeChunks.size(); i++) {

		activeChunks[i]->update();
	}
}



void World::generate() {

	// 0 = 50, 1 = WorldHeight
	int groundLevel = 50;
	int curX = 0;
	int preX = 0;
	int lastBlockY = 55;


	while(curX <= World::worldWidth) {

		Biome* biome;

	double r = (double)rand()/RAND_MAX;

		if(r >= 0 && r < 0.5) {
			biome = new BiomePlains(curX, lastBlockY);
		} else if(r >= 0.5 && r <= 1) {
			biome = new BiomeDesert(curX, lastBlockY);
		}

		biome->setMyContainer(myContainer);
		biome->generate();
		curX = biome->getLastBlockX();
		lastBlockY = biome->getLastBlockY();

	}
	WorldGenCaves worldGenCaves;
	worldGenCaves.setMyContainer(myContainer);
	worldGenCaves.generate();
}

void World::init() {

	for(int x = 0; x < chunksHoriz; x++) {
		for(int y = 0; y < chunksVert; y++) {

			Chunk *chunk = new Chunk(x*Chunk::width*Block::size, y*Chunk::height*Block::size);
			chunk->setMyContainer(myContainer);
			chunk->init();
			chunks.push_back(chunk);
		}

	}
	World::worldHeight = chunksVert*Chunk::height;
	World::worldWidth = chunksHoriz*Chunk::width;

}

void World::resetBlocks() {
	for(int i = 0; i < chunks.size(); i++) {

		chunks[i]->init();
	}
}

Block* World::getBlock(float x, float y, int z) {

	for(int i = 0; i < chunks.size(); i++) {
		if(chunks[i]->getX() + Chunk::width*Block::size > x && 
			x >= chunks[i]->getX() &&
			y >= chunks[i]->getY() &&
			y < chunks[i]->getY() + Chunk::height*Block::size) {

				float relX = x - chunks[i]->getX();
				float relY = y - chunks[i]->getY();
				relX /= Block::size;
				relY /= Block::size;
				return chunks[i]->getBlock(relX, relY, z);

		}
	}
	return false;

}

Block* World::getFrontBlock(float x, float y) {

	Block* block;
	for(int i = Chunk::depth - 1; i >= 0; i--) {
		block = getBlock(x, y, i);
		if(block) {
			return block;
		}
	}
	return false;
}


void World::setBlock(Block* block) {

	float blockX = block->getX();
	float blockY = block->getY();

	for(int i = 0; i < chunks.size(); i++) {
		if(chunks[i]->getX() + Chunk::width*Block::size > blockX && 
			blockX >= chunks[i]->getX() &&
			blockY >= chunks[i]->getY() &&
			blockY < chunks[i]->getY() + Chunk::height*Block::size) {

				chunks[i]->setBlock(block);
				break;

		}
	}

}

void World::deleteBlock(Block* block) {
	
	float blockX = block->getX();
	float blockY = block->getY();

	for(int i = 0; i < chunks.size(); i++) {
		if(chunks[i]->getX() + Chunk::width*Block::size > blockX && 
			blockX >= chunks[i]->getX() &&
			blockY >= chunks[i]->getY() &&
			blockY < chunks[i]->getY() + Chunk::height*Block::size) {

				chunks[i]->deleteBlock(block);
				break;

		}
	}

}

void World::render(bool obstacles) {

	for(int i = 0; i < activeChunks.size(); i++) {
		activeChunks[i]->render(obstacles);
	}

}