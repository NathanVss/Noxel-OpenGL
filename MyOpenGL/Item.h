#pragma once

#include "Object.h"
#include "Container.h"
#include <YuEngine\GameRenderer.h>
#include <YuEngine\SpritesheetsManager.h>
#include <YuEngine\Spritesheet.h>


class ItemStack;

class Item: public Object
{
public:
	Item(void);
	Item(Container *c);
	~Item(void);

	virtual void render(float width, float height, float x, float y);
	virtual void render(float width, float height, float x, float y, float angle, float pointToRotateArroundX, float pointToRotateArroundY, float depth);
	virtual void update();
	virtual void onUse(ItemStack* itemStack);

	int getId() {
		return id;
	}
	int getStackSize() {
		return stackSize;
	}
	float getWidthHeightRatio() {
		return (texX2 - texX1) / (float)(texY2 - texY1);
	}
	float getHeldingHeight() {
		return heldingHeight;
	}
	const static int woodPickaxeId = 1;
	const static int blockGrassId = 10000;
protected:
	YuEngine::Spritesheet* spritesheet;

	int id;
	int stackSize;

	int texX1;
	int texY1;

	int texX2;
	int texY2;

	float heldingHeight;

	float widthHeightRatio;


};

