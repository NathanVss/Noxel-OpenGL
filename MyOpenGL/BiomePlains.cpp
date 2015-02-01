#include "BiomePlains.h"
#include <random>
#include "World.h"
#include "Block.h"
#include "BlockGrass.h"
#include "BlockDirt.h"
#include "Container.h"
#include "BlockSand.h"
#include "BlockStone.h"

BiomePlains::BiomePlains(void)
{
}

BiomePlains::BiomePlains(float _baseX, float _firstBlockY) : Biome(_baseX, _firstBlockY) {
	groundLevel = 50;
	topLevel = 80;
	setFirstBlockYRelNoise(firstBlockY);

	YuEngine::Perlin2D _perlin;
	length = floor(20 + (double)rand()/RAND_MAX * 20.0f);
	_perlin.init(length, 10, 1, firstBlockYRelNoise);
	perlin = _perlin;
	 
}

void BiomePlains::generate() {


	for(int x = baseX; x < baseX+length; x++) {

		
		float noiseValue;
		if(firstGenIteration) {
			noiseValue = firstBlockYRelNoise;
			firstGenIteration = false;
		} else {
			noiseValue = perlin.coherentNoise(x-baseX, 0.5);

		}
		

		float y = (int)(groundLevel + ( topLevel - groundLevel ) * noiseValue);


		if( x == (baseX + length - 1) ) {
			lastBlockY = y;
		}
		BlockGrass *blockGrass = new BlockGrass(x*Block::size, y*Block::size);
		myContainer->getWorld()->setBlock(blockGrass);

		int relDepth = 0;
		int stoneDepth = 5 + rand() / RAND_MAX * 10;
		for(int dy = y-1; dy >= 0; dy--) {
			relDepth++;

			if(relDepth > stoneDepth) {
				BlockStone* blockStone = new BlockStone(x*Block::size, dy*Block::size);
				myContainer->getWorld()->setBlock(blockStone);
			} else {
				BlockDirt* blockDirt = new BlockDirt(x*Block::size, dy*Block::size);
				myContainer->getWorld()->setBlock(blockDirt);
			}

		}
	}
}

BiomePlains::~BiomePlains(void)
{
}
