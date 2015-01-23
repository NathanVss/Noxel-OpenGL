#pragma once

#include "Biome.h"

class BiomePlains : public Biome
{
public:
	BiomePlains(void);
	BiomePlains(float _baseX, float _firstBlockY);
	~BiomePlains(void);
	void generate();
};

