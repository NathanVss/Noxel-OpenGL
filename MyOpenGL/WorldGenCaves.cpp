#include "WorldGenCaves.h"
#include <YuEngine\Perlin2D.h>
#include "World.h"
#include "BlockAir.h"
#include "Container.h"
#include "World.h"

WorldGenCaves::WorldGenCaves(void)
{
}


WorldGenCaves::~WorldGenCaves(void)
{
}

void WorldGenCaves::generate() {
	float caveHeight = 10;

	float delta = 20;
	float deepBase = 10;

	YuEngine::Perlin2D perlin;
	perlin.init(World::worldWidth, 20, 1);

	for(int x = 0; x < World::worldWidth; x++) {
		int y = (perlin.coherentNoise(x, 0.5) * delta);
		y = deepBase + y;

		for(int dy = y; dy <= y + caveHeight; dy++) {
			BlockAir* blockAir = new BlockAir(x*Block::size, dy*Block::size, Block::landZ);
			myContainer->getWorld()->setBlock(blockAir);
		}


	}
}
