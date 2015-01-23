#include "Biome.h"
#include "World.h"

Biome::Biome(void)
{
}

Biome::Biome(float _baseX, float _firstBlockY) {
	baseX = _baseX;
	firstBlockY = _firstBlockY;
	firstGenIteration = true;
}



Biome::~Biome(void)
{
}
