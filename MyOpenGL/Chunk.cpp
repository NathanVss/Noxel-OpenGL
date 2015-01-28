#include "Chunk.h"
#include "BlockAir.h"
#include "BlockGrass.h"
#include <iostream>
#include "Container.h"


int Chunk::width = 16;
int Chunk::height = 16;

Chunk::Chunk(float _x, float _y) : x(_x), y(_y) {

}

void Chunk::init() {
	blocks = new Block**[Chunk::width];
	for(int x = 0; x < Chunk::width; x++) {
		blocks[x] = new Block*[Chunk::height];
		for(int y = 0; y < Chunk::height; y++) {

			blocks[x][y] = new BlockAir(this->x + x*Block::size, this->y + y*Block::size);
			blocks[x][y]->setMyContainer(myContainer);
		}
	}
}


Chunk::~Chunk(void){
	for(int x = 0; x < Chunk::width; x++) {
		for(int y = 0; y < Chunk::height; y++) {
			delete blocks[x][y];
		}
		delete blocks[x];
	} 
	delete blocks;
}

void Chunk::setBlock(Block* block) {
	float absX = block->getX() - this->x;
	float absY = block->getY() - this->y;
	//std::cout << "Block : " << absX << ";" << absY << std::endl;
	absX /= Block::size;
	absY /= Block::size;
	
	delete blocks[(int)absX][(int)absY];
	blocks[(int)absX][(int)absY] = block;
	blocks[(int)absX][(int)absY]->setMyContainer(myContainer);
}



void Chunk::render(bool obstacles) {
	for(int x=0; x < Chunk::width; x++) {

		for(int y = 0; y < Chunk::height; y++) {

			if(obstacles) {

				if(!blocks[x][y]->isTransparent()) {
					blocks[x][y]->render(obstacles);

				}

			} else {
				blocks[x][y]->render(obstacles);

			}

		}
	}
}