#include "ItemStack.h"
#include <YuEngine\FontRenderer.h>

ItemStack::ItemStack(void){
}


ItemStack::ItemStack(Container* c) : Object(c) {
	capacity = -1;
	
}


ItemStack::~ItemStack(void)
{
}

int ItemStack::getSize() {
	return items.size();
}
bool ItemStack::isEmpty() {
	return items.size() == 0;
}
bool ItemStack::isFull() {
	return items.size() == capacity;
}

void ItemStack::emptyItem(Item* item) {

	std::vector<Item*> temp;
	for(int i = 0; i < items.size(); i++) {

		if(item != items[i]) {
			temp.push_back(items[i]);
		} else if(item == items[i]) {
			//delete item;
		}

	}
	items = temp;
}


void ItemStack::render(float width, float height, float x, float y) {

	if(!isEmpty()) {
		items[0]->render(width, height, x, y);
	}

}
void ItemStack::renderSize(float width, float height, float x, float y, float size) {
	if(getSize() > 1) {

		myContainer->getFontRenderer()->renderText(std::to_string(getSize()), x, y, 31.01f, size, 1.0f, 1.0f, 1.0f, 1.0f);
	}
}


bool ItemStack::addItem(Item* item) {

	if(isFull()) {
		return false;
	}
	if(isEmpty()) {
		items.push_back(item);
		capacity = item->getStackSize();
		return true;
	} else {
		if(item->getId() != items[0]->getId()) {
			return false;
		}

		items.push_back(item);
		capacity = item->getStackSize();

		return true;

	}

}
