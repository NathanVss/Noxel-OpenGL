#pragma once

#include "Object.h"

#include <vector>
class GuiQuickInventory;
class ItemStack;
class Item;

class QuickInventory : public Object
{
public:
	QuickInventory(void);
	QuickInventory(Container* c);
	~QuickInventory(void);

	void update();
	void render();
	void addItem(Item* item);

	int getSlots() {
		return slots;
	}
	int getSelectedSlot() {
		return selectedSlot;
	}
	std::vector<ItemStack*>* getItemStacks() {
		return &itemStacks;
	}
	ItemStack* getSelectedItemStack() {
		if(itemStacks.size() > selectedSlot) {
			return itemStacks[selectedSlot];
		}
		return false;
	}
	Item* getSelectedItem();
	

private:
	int slots;
	int selectedSlot;
	GuiQuickInventory* gui;
	std::vector<ItemStack*> itemStacks;
};

