#include "QuickInventory.h"
#include "GuiQuickInventory.h"
#include "Container.h"
#include "GuiManager.h"
#include "ItemStack.h"
#include "PlayerOverlay.h"

QuickInventory::QuickInventory(void){
}

QuickInventory::QuickInventory(Container* c) : Object(c) {
	gui = new GuiQuickInventory(myContainer);
	gui->setQuickInventory(this);
	myContainer->getGuiManager()->handleGui(gui, true);
	myContainer->getPlayerOverlay()->setGuiQuickInventory(gui);

	slots = 10;
	selectedSlot = 0;
}


QuickInventory::~QuickInventory(void){
}

void QuickInventory::addItem(Item* item) {

	for(int i = 0; i < itemStacks.size(); i++) {

		if(itemStacks[i]->addItem(item)) {
			return;
		}

	}

	if(itemStacks.size() < slots) {
		ItemStack* newItemStack = new ItemStack(myContainer);
		itemStacks.push_back(newItemStack);

		newItemStack->addItem(item);
	}

}


void QuickInventory::update() {


	selectedSlot += myContainer->getInput()->getMouseScrollY();
	if(selectedSlot >= slots) {
		selectedSlot = 0;
	}
	if(selectedSlot < 0 ) {
		selectedSlot = slots-1;
	}

}
void QuickInventory::render() {
}

Item* QuickInventory::getSelectedItem() {
	if(itemStacks.size() > selectedSlot) {

		return itemStacks[selectedSlot]->getFirstItem();
	}
	return false;
}
	
