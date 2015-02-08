#pragma once

#include "Entity.h"

class Item;

class Drop : public Entity
{
public:
	Drop(Container* c, Item* item, float _width, float _height);
	~Drop(void);
	virtual void render();
	virtual void update();

private:
	Item* item;
	int age;
	int maxAge;
	bool followPlayer;
};

