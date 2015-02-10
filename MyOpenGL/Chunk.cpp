#include "Chunk.h"
#include "BlockAir.h"
#include "BlockGrass.h"
#include <iostream>
#include "Container.h"


int Chunk::width = 16;
int Chunk::height = 16;
int Chunk::depth = 3;

Chunk::Chunk(float _x, float _y) : x(_x), y(_y) {

}

void Chunk::init() {
	blocks = new Block***[Chunk::width];
	for(int x = 0; x < Chunk::width; x++) {
		blocks[x] = new Block**[Chunk::height];
		for(int y = 0; y < Chunk::height; y++) {
			blocks[x][y] = new Block*[Chunk::depth];
			for(int z = 0; z < Chunk::depth; z++) {

				if(z == Block::landZ) {
					blocks[x][y][z] = new BlockAir(this->x + x*Block::size, this->y + y*Block::size, z);
					blocks[x][y][z]->setMyContainer(myContainer);
				} else {
					blocks[x][y][z]= false;
				}
			}
		}
	}
}

void Chunk::update() {
	for(int x = 0; x < Chunk::width; x++) {
		for(int y = 0; y < Chunk::height; y++) {
			for(int z = 0; z < Chunk::depth; z++) {

				if(blocks[x][y][z]) {
					blocks[x][y][z]->update();
				}
			}
		}

	}
}


Chunk::~Chunk(void){
	for(int x = 0; x < Chunk::width; x++) {
		for(int y = 0; y < Chunk::height; y++) {
			for(int z = 0; z < Chunk::depth; z++) {
				delete blocks[x][y][z];
			}
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
	
	delete blocks[(int)absX][(int)absY][block->getZ()];
	blocks[(int)absX][(int)absY][block->getZ()] = block;
	blocks[(int)absX][(int)absY][block->getZ()]->setMyContainer(myContainer);
}



void Chunk::render(bool obstacles) {
	for(int x=0; x < Chunk::width; x++) {

		for(int y = 0; y < Chunk::height; y++) {

			for(int z = 0; z < Chunk::depth; z++) {

				if(!blocks[x][y][z]) {
					continue;
				}
				if(obstacles) {

					if(!blocks[x][y][z]->isTransparent()) {
						blocks[x][y][z]->render(obstacles);

					}

				} else {
					blocks[x][y][z]->render(obstacles);

				}
			}

		}
	}
}