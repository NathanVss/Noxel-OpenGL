#include "ItemBlock.h"
#include "ItemStack.h"

#include <YuEngine\Camera2D.h>
#include <YuEngine\Input.h>
#include "Block.h"
#include "World.h"

ItemBlock::ItemBlock(Container* c, Block* _block) : Item(c), block(_block)
{
	id = block->getId();
	stackSize = 64;
	texX1 = block->getTextX1();
	texY1 = block->getTextY1();
	texX2 = block->getTextX2();
	texY2 = block->getTextY2();
	spritesheet = myContainer->getSpritesheetsManager()->getBlocksSpritesheet();
}


ItemBlock::~ItemBlock(void)
{
}

void ItemBlock::onUse(ItemStack* itemStack) {


	if(itemStack) {

		YuEngine::Position mousePos = myContainer->getCamera()->getMouseAbsPos(myContainer->getInput()->getMouseX(), myContainer->getInput()->getMouseY());
		glm::vec2 mouseWorld;
		mouseWorld.x = floor(mousePos.x / Block::size) * 32;
		mouseWorld.y = floor(mousePos.y / Block::size) * 32;
		Block* curBlock = myContainer->getWorld()->getBlock(mouseWorld.x, mouseWorld.y);

		if(curBlock && curBlock->getId() == Block::AirId && curBlock->canBePlaced(mouseWorld.x, mouseWorld.y)) {
				
			block->setPosition(mouseWorld.x, mouseWorld.y);

			myContainer->getWorld()->setBlock(block);
			block->onPlacing();
			itemStack->emptyItem(this);

		}

	}
}