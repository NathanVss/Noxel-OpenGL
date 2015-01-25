#include "BiomeDesert.h"
#include "BlockSand.h"
#include "BlockDirt.h"
#include "World.h"
#include "Container.h"

BiomeDesert::BiomeDesert(float _baseX, float _firstBlockY) : Biome(_baseX, _firstBlockY) {
	groundLevel = 50;
	setFirstBlockYRelNoise(firstBlockY);

	YuEngine::Perlin2D _perlin;
	length = floor(30 + (double)rand()/RAND_MAX * 20.0f);
	_perlin.init(length, 20, 1, firstBlockYRelNoise);
	perlin = _perlin;
	 
}

void BiomeDesert::generate() {


	for(int x = baseX; x < baseX+length; x++) {

		
		float noiseValue;
		if(firstGenIteration) {
			noiseValue = firstBlockYRelNoise;
			firstGenIteration = false;
		} else {
			noiseValue = perlin.coherentNoise(x-baseX, 0.5);

		}
		

		float y = (int)(groundLevel + ( World::worldHeight - groundLevel ) * noiseValue);


		if( x == (baseX + length - 1) ) {
			lastBlockY = y;
		}
		BlockSand *blockGrass = new BlockSand(x*Block::size, y*Block::size);
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
			
			Block* block;
			if( dy >= y-1-4) {
				block = new BlockSand(x*Block::size, dy*Block::size);
			} else {
				block = new BlockDirt(x*Block::size, dy*Block::size);
			}
			myContainer->getWorld()->setBlock(block);
		}
	}
}


BiomeDesert::~BiomeDesert(void)
{
}
