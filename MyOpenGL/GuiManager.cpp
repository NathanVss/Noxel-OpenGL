#include "GuiManager.h"
#include "Gui.h"
#include "Container.h"
#include <YuEngine\Input.h>
#include "Config.h"

GuiManager::GuiManager(void){
}


GuiManager::~GuiManager(void) {
}

void GuiManager::handleGui(Gui* g, bool display) {
	idsCounter++;
	g->setId(idsCounter);
	if(display) {
		g->setDisplay(display);
	}
	guis.push_back(g);
}

void GuiManager::render() {

	for(int i = 0; i < guis.size(); i++) {

		if(guis[i]->getDisplay()) {

			guis[i]->render();
		}

	}


}

void GuiManager::update() {

	std::vector<Gui*> tempVector;
	for(int i = 0; i < guis.size(); i++) {

		guis[i]->update();
		if(guis[i]->getDestroy()) {
			delete guis[i];
		} else {
			tempVector.push_back(guis[i]);
		}

	}
	guis = tempVector;


	if(myContainer->getInput()->getLeftClick()) {

		float mouseX = myContainer->getInput()->getMouseX();
		float mouseY = myContainer->getConfig()->getScreenHeight() - myContainer->getInput()->getMouseY();

		Gui* clickedGui;
		bool hasReached = false;

		for(int i = 0; i < guis.size(); i++) {
			Gui* curGui = guis[i];

			if(mouseX > curGui->getRelX() && curGui->getRelX() + curGui->getWidth() > mouseX &&
				mouseY > curGui->getRelY() && curGui->getRelY() + curGui->getHeight() > mouseY && curGui->getDisplay()) {

					hasReached = true;
					clickedGui = curGui;
					clickedGui->setFocus(true);
			} else {
				curGui->setFocus(false);
			}

		}
	}

	for(int i = 0; i < guis.size(); i++) {

		if(guis[i]->getFocus()) {

			guis[i]->setDepth(30.01f);
		} else {

			guis[i]->setDepth(30.0f);
		}

	}

}