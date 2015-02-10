#pragma once

#include "Item.h"

class Block;

class ItemBlock : public Item
{
public:
	ItemBlock(Container* c, Block* _block);
	~ItemBlock(void);
	virtual void onUse(ItemStack* itemStack);

private:
	Block* block;
};

