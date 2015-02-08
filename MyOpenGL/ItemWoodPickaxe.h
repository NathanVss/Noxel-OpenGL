#pragma once

#include "Item.h"

class ItemWoodPickaxe : public Item
{
public:
	ItemWoodPickaxe(void);
	ItemWoodPickaxe(Container* c);
	~ItemWoodPickaxe(void);

	virtual void update();
};

