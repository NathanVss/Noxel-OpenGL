#pragma once

#include "WorldGen.h"

class WorldGenCaves : public WorldGen
{
public:
	WorldGenCaves(void);
	~WorldGenCaves(void);
	virtual void generate();
};

