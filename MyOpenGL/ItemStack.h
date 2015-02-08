#pragma once

#include "Object.h"
#include <vector>
#include "Item.h"

class ItemStack : public Object
{
public:
	ItemStack(void);
	ItemStack(Container* c);
	~ItemStack(void);

	int getSize();
	bool isEmpty();
	bool isFull();

	void render(float width, float height, float x, float y);
	void renderSize(float width, float height, float x, float y, float size);
	bool addItem(Item* item);
	void emptyItem(Item* item);

	Item* getFirstItem() {
		if(!isEmpty()) {
			return items[0];
		}
		return false;
	}

private:
	int capacity;
	std::vector<Item*> items;

};

