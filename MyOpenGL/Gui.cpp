#include "Gui.h"
#include <YuEngine\YuBoudingbox.h>
#include "Container.h"
#include <YuEngine\Camera2D.h>

Gui::Gui(void){
}

Gui::Gui(int _relX, int _relY, YuEngine::KeyName _closingKey, YuEngine::KeyName _displayingKey) {

	
	relX = _relX;
	relY = _relY;
	destroy = false;
	display = false;
	focus = false;
	closingKey = _closingKey;
	displayingKey = _displayingKey;
	depth = 30.0f;
}


Gui::~Gui(void)
{
}


void Gui::baseInit() {
	closingEvent = YuEngine::KeyEvent(closingKey, myContainer->getInput());
	displayingEvent = YuEngine::KeyEvent(displayingKey, myContainer->getInput());
}

void Gui::baseUpdate() {

	if(focus) {
		closingEvent.update();
		if(closingEvent.getEvent() && display) {
			display = false;
		}

		YuEngine::Color _color;
		_color.r = 1.0f;
		_color.g = 1.0f;
		_color.b = 1.0f;
		_color.a = 1.0f;
		color = _color;

	} else {
		YuEngine::Color _color;
		_color.r = 0.8f;
		_color.g = 0.8f;
		_color.b = 0.8f;
		_color.a = 1.0f;
		color = _color;
	}

	displayingEvent.update();
	if(displayingEvent.getEvent() && !display) {
		display = true;
	}

	YuEngine::YuBoudingbox cameraBox = myContainer->getCamera()->getCameraBox();
	absX = cameraBox.getX1() + relX;
	absY = cameraBox.getY1() - cameraBox.getHeight() + relY;
}

void Gui::switchDisplayState() {

	display = !display;

}