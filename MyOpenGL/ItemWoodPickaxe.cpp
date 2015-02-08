#include "ItemWoodPickaxe.h"


ItemWoodPickaxe::ItemWoodPickaxe(void){

}

ItemWoodPickaxe::ItemWoodPickaxe(Container* c) : Item(c) {
	id = Item::woodPickaxeId;
	stackSize = 1;
	texX1 = 0;
	texY1 = 0;
	texX2 = 2;
	texY2 = 2;
}

ItemWoodPickaxe::~ItemWoodPickaxe(void)
{
}

void ItemWoodPickaxe::update() {


}
