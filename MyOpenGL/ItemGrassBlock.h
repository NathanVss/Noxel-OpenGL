#pragma once

#include "Item.h"

class ItemGrassBlock : public Item
{
public:
	ItemGrassBlock(void);
	ItemGrassBlock(Container *c);
	~ItemGrassBlock(void);

	virtual void update();
};

