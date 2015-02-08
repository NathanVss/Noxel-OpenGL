#include "Item.h"


Item::Item(void){
}

Item::Item(Container *c) : Object(c) {
	spritesheet = myContainer->getSpritesheetsManager()->getItemsSpritesheet();
	widthHeightRatio = 1;
	heldingHeight = 32;
}


Item::~Item(void){
}


void Item::update() {


}

void Item::onUse(ItemStack* itemStack) {


}

void Item::render(float width, float height, float x, float y) {

	myContainer->getGameRenderer()->addGlyph(x, y, width, height,31.0f, 1.0f,1.0f,1.0f,1.0f, spritesheet, texX1,texY1,texX2,texY2);

}

 void Item::render(float width, float height, float x, float y, float pointToRotateArroundX, float pointToRotateArroundY, float angle, float depth) {
	myContainer->getGameRenderer()->addGlyph(x, y, width, height, pointToRotateArroundX, pointToRotateArroundY, angle,  depth, 1.0f,1.0f,1.0f,1.0f, spritesheet, texX1,texY1,texX2,texY2);

 }

