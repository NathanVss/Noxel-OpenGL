#include "GameConsole.h"
#include "Container.h"
#include <YuEngine\Input.h>
#include <YuEngine\YuBoudingbox.h>
#include <YuEngine\Camera2D.h>
#include <YuEngine\GameRenderer.h>
#include <YuEngine\SpritesheetsManager.h>
#include <YuEngine\Spritesheet.h>

GameConsole::GameConsole(void){
	displayTimer = YuEngine::EventTimer(8);
	letterTimer = YuEngine::EventTimer(5);
	width = 600;
	height =300;
	display = false;
}


GameConsole::~GameConsole(void)
{
}

void GameConsole::update() {
	displayTimer.update();
	letterTimer.update();

	if(displayTimer.isOver()) {
		if(myContainer->getInput()->getKeyEnter()) {
			display = !display;
		}

		displayTimer.reset();
	}
	YuEngine::YuBoudingbox cameraBox = myContainer->getCamera()->getCameraBox();

	x = cameraBox.getX1() + cameraBox.getWidth() - width;
	y = cameraBox.getY1() - cameraBox.getHeight() + height;

}

void GameConsole::render() {
	if(display) {
		myContainer->getGameRenderer()->addGlyph(x,y, width, height, 35, 1.0f, 1.0f, 1.0f, 0.5f, myContainer->getSpritesheetsManager()->getMiscSpritesheet(), 0,0);
	} else {
		myContainer->getGameRenderer()->addGlyph(x,y, width, height, 35, 1.0f, 1.0f, 1.0f, 0.2f, myContainer->getSpritesheetsManager()->getMiscSpritesheet(), 0,0);

	}
}