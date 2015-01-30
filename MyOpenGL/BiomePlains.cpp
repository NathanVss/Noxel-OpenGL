#include "BiomePlains.h"
#include <random>
#include "World.h"
#include "Block.h"
#include "BlockGrass.h"
#include "BlockDirt.h"
#include "Container.h"
#include "BlockSand.h"

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
		//if(x == baseX) {
		//	YuEngine::Color c;
		//	c.r = 0;
		//	c.g = 0;
		//	c.b = 0;
		//	c.a = 255;
		//	blockGrass->setLightIndice(c);
		//}
		myContainer->getWorld()->setBlock(blockGrass);

		for(int dy = y-1; dy >= 0; dy--) {
			BlockDirt* blockDirt = new BlockDirt(x*Block::size, dy*Block::size);
			myContainer->getWorld()->setBlock(blockDirt);
		}
	}
}

BiomePlains::~BiomePlains(void)
{
}
