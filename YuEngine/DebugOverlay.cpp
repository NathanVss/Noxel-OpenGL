#include "DebugOverlay.h"
#include "Container.h"
#include "FontRenderer.h"
#include "Camera2D.h"
#include <iostream>

namespace YuEngine {


DebugOverlay::DebugOverlay(void)
{
}


DebugOverlay::~DebugOverlay(void)
{
}


void DebugOverlay::update() {
	this->debugStrings.clear();
}

void DebugOverlay::addDebugString(std::string s) {
	this->debugStrings.push_back(s);
}

void DebugOverlay::render() {

	int size = 2;
	glm::vec2 cameraPosition = this->container->getCamera()->getPosition();
	int screenWidth = this->container->getCamera()->getScreenWidth();
	int screenHeight = this->container->getCamera()->getScreenHeight();
	for(int i=0; i<this->debugStrings.size(); i++) {

		this->container->getFontRenderer()->renderText(this->debugStrings[i], cameraPosition.x-screenWidth/2, (cameraPosition.y+screenHeight/2)-(i)*8*2,26, 2, 1.0f, 1.0f, 1.0f, 1.0f);
	}
}
}