#include "GuiQuickInventory.h"
#include "Container.h"
#include "QuickInventory.h"
#include <YuEngine\GameRenderer.h>
#include <YuEngine\SpritesheetsManager.h>
#include <YuEngine\FontRenderer.h>
#include "Config.h"
#include "ItemStack.h"
GuiQuickInventory::GuiQuickInventory(Container* c) : Gui(c, 0,5, YuEngine::KeyName::none, YuEngine::KeyName::none) {
	slotSize = 50 * myContainer->getConfig()->getScreenWidth() / 1280.0f;

}


GuiQuickInventory::~GuiQuickInventory(void){
}

void GuiQuickInventory::render() {

	marginBetweenSlots = 5 * myContainer->getConfig()->getScreenWidth() / 1280.0f;
	if(display) {
		for(int i = 0; i < quickInventory->getSlots(); i++) {
			if(i == quickInventory->getSelectedSlot()) {
				myContainer->getGameRenderer()->addGlyph(absX+(slotSize+marginBetweenSlots)*i, absY+slotSize, slotSize, slotSize, depth, color.r, color.g, color.b, 0.7f, myContainer->getSpritesheetsManager()->getGuiSpritesheet(), 2,0,4,2);

			} else {
				myContainer->getGameRenderer()->addGlyph(absX+(slotSize+marginBetweenSlots)*i, absY+slotSize, slotSize, slotSize, depth, color.r, color.g, color.b, 0.7f, myContainer->getSpritesheetsManager()->getGuiSpritesheet(), 0,0,2,2);

			}
		}	
		std::vector<ItemStack*>* itemStacks = quickInventory->getItemStacks();
		for(int i = 0; i < itemStacks->size(); i++) {
			ItemStack* itemStack = (*itemStacks)[i];
			float itemSize = slotSize * 0.6f;
			float offsetY = slotSize-(slotSize-itemSize)/2;
			float offsetX = (slotSize-itemSize)/2;

			itemStack->render(itemSize, itemSize, absX+(slotSize+marginBetweenSlots)*i + offsetX, absY+offsetY);

			float textSize = 2;
			float textOffsetX = slotSize - YuEngine::FontRenderer::letterHeight * textSize;
			float textOffsetY = YuEngine::FontRenderer::letterHeight * textSize;

			itemStack->renderSize(itemSize, itemSize, absX+(slotSize+marginBetweenSlots)*i+textOffsetX , absY+textOffsetY, textSize);

		}
	}
}

void GuiQuickInventory::update() {


	Gui::update();

}