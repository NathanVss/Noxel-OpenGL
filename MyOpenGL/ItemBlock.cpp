#include "ItemBlock.h"
#include "ItemStack.h"

#include <YuEngine\Camera2D.h>
#include <YuEngine\Input.h>
#include "Block.h"
#include "World.h"

ItemBlock::ItemBlock(Container* c, Block* _block, int _id) : Item(c), block(_block)
{
	id = _id;
	stackSize = 64;
	texX1 = 0;
	texY1 = 0;
	texX2 = 1;
	texY2 = 1;
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

		if(curBlock && curBlock->getId() == Block::AirId) {
				
			block->setPosition(mouseWorld.x, mouseWorld.y);

			myContainer->getWorld()->setBlock(block);
			itemStack->emptyItem(this);

		}

	}
}