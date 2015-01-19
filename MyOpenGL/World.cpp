#include "World.h"
#include "Block.h"
#include <YuEngine\Perlin2D.h>
#include "BlockGrass.h"
#include <iostream>
#include "BlockDirt.h"

#include <YuEngine\Camera2D.h>
#include <YuEngine\Container.h>

int World::worldHeight = 0;

World::~World(void){
	for(int i = 0; i < chunks.size(); i++) {
		delete chunks[i];
	}
}

void World::update() {
	float radius = 24;
	radius *= Block::size;
	glm::vec2 cameraPos = container->getCamera()->getPosition();

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
}

void World::generate() {

	// 0 = 50, 1 = WorldHeight
	int groundLevel = 50;

	Perlin2D perlin;
	perlin.init(chunksHoriz*Chunk::width, 20, 1);

	// Parcour en Block unit
	for(int x = 0; x < chunksHoriz*Chunk::width; x++) {

		double noiseValue = perlin.coherentNoise(x, 0.5);
		
		float y = (int)(groundLevel + ( World::worldHeight - groundLevel ) * noiseValue);
		
		BlockGrass *blockGrass = new BlockGrass(x*Block::size, y*Block::size);
		setBlock(blockGrass);

		for(int dy = y-1; dy >= 0; dy--) {
			BlockDirt* blockDirt = new BlockDirt(x*Block::size, dy*Block::size);
			setBlock(blockDirt);
		}
	}
}

void World::init() {

	for(int x = 0; x < chunksHoriz; x++) {
		for(int y = 0; y < chunksVert; y++) {

			Chunk *chunk = new Chunk(x*Chunk::width*Block::size, y*Chunk::height*Block::size);
			chunk->setContainer(container);
			chunk->init();
			chunks.push_back(chunk);
		}

	}
	World::worldHeight = chunksVert*Chunk::height;

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

void World::render() {

	for(int i = 0; i < activeChunks.size(); i++) {
		activeChunks[i]->render();
	}

}