#pragma once

#include "Biome.h"

class BiomeDesert : public Biome
{
public:
	BiomeDesert(void);
	BiomeDesert(float _baseX, float _firstBlockY);
	~BiomeDesert(void);
	void generate();
};

