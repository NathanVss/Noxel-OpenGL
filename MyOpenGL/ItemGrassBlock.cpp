#include "ItemGrassBlock.h"


ItemGrassBlock::ItemGrassBlock(void){
}

ItemGrassBlock::ItemGrassBlock(Container* c) : Item(c) {
	id = Item::blockGrassId;
	stackSize = 64;
	texX1 = 0;
	texY1 = 0;
	texX2 = 1;
	texY2 = 1;
	spritesheet = myContainer->getSpritesheetsManager()->getBlocksSpritesheet();
}

ItemGrassBlock::~ItemGrassBlock(void)
{
}


void ItemGrassBlock::update() {


}