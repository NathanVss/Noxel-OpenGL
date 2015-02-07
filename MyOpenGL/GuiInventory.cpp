#include "GuiInventory.h"
#include "Container.h"
#include <YuEngine\GameRenderer.h>
#include <YuEngine\SpritesheetsManager.h>
#include <YuEngine\Input.h>

GuiInventory::GuiInventory(float _relX, float _relY) : Gui(_relX,_relY, YuEngine::KeyName::escape, YuEngine::KeyName::i) {

	displayTimer = YuEngine::EventTimer(20);
	closingKey = YuEngine::KeyName::escape;
	width = 400;
	height = 250;
	
}


GuiInventory::~GuiInventory(void) {
}

void GuiInventory::init() {
	baseInit();

}

void GuiInventory::render() {
	if(display) {

		myContainer->getGameRenderer()->addGlyph(absX, absY+height, width, height, depth, color.r, color.g, color.b, color.a, myContainer->getSpritesheetsManager()->getBlocksSpritesheet(), 0,0);
	}
}

void GuiInventory::update() {
	baseUpdate();

}