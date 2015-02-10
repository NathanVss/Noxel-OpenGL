#include "GuiPlayerHealth.h"
#include "HealthBuffer.h"
#include "Container.h"
#include "PlayerOverlay.h"
#include "GuiQuickInventory.h"
#include "Config.h"

#include <stdio.h>

#include <YuEngine\GameRenderer.h>
#include <YuEngine\SpritesheetsManager.h>

GuiPlayerHealth::GuiPlayerHealth(Container* c) : Gui(c, 0, 0, YuEngine::KeyName::none, YuEngine::KeyName::none){

	relY = myContainer->getPlayerOverlay()->getGuiQuickInventory()->getTopY() + 10 * myContainer->getConfig()->getScreenHeight() / 1280.0f;
	relX = 0;
}


GuiPlayerHealth::~GuiPlayerHealth(void)
{
}

void GuiPlayerHealth::update() {
	Gui::update();
}

void GuiPlayerHealth::render() {

	float heartSize = 30;
	float margin = 5;

	for(int i = 0; i < floor(healthBuffer->getMaxHealth()/3.0f + 0.5f); i++) {

		
		myContainer->getGameRenderer()->addGlyph(absX + i * (heartSize + margin), absY + heartSize, heartSize, heartSize, 31, 1.0f, 1.0f, 1.0f, 1.0f, myContainer->getSpritesheetsManager()->getMiscSpritesheet(), 12, 6);


	}

	int heartState = 0;
	int hearts = 0;
	for(int j = 0; j < healthBuffer->getHealth(); j++) {
		int texX = 0;
		int texY = 5;

		heartState++;
		if(heartState == 4) {
			heartState = 1;
		}

		if(heartState == 3) {
			texX = 15;
		} else if(heartState == 1) {
			hearts++;
			texX = 13;
		} else if(heartState == 2) {
			texX = 14;
		}
		myContainer->getGameRenderer()->addGlyph(absX + (hearts-1) * (heartSize + margin), absY + heartSize, heartSize, heartSize, 31, 1.0f, 1.0f, 1.0f, 1.0f, myContainer->getSpritesheetsManager()->getMiscSpritesheet(), texX, texY);

	}

}