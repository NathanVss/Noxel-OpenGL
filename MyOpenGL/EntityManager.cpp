#include "EntityManager.h"
#include "Container.h"
#include <YuEngine\Input.h>
#include <YuEngine\Vertex.h>
#include <YuEngine\Camera2D.h>
#include <YuEngine\FontRenderer.h>

EntityManager::EntityManager(void)
{
}


EntityManager::~EntityManager(void)
{
}

void EntityManager::update() {

	std::vector<Entity*> tempEntities;
	for(int i = 0; i < entities.size(); i++) {
		if(!entities[i]->getDestroy()) {
			tempEntities.push_back(entities[i]);
			entities[i]->update();
		} else {
			delete entities[i];
		}
	}
	entities = tempEntities;

	std::vector<EntityMob*> tempMobEntities;
	for(int j = 0; j < mobEntities.size();j++) {
		if(!mobEntities[j]->getDestroy()) {
			tempMobEntities.push_back(mobEntities[j]);
			mobEntities[j]->update();

		} else {
			delete mobEntities[j];
		}
	}
	mobEntities = tempMobEntities;





}

void EntityManager::hit(float _x, float _y) {
	for(int i = 0; i < mobEntities.size(); i++) {

		YuEngine::YuBoudingbox boundingbox = mobEntities[i]->getBoundingbox();
		bool insideLeft = boundingbox.isInsideLeft(_x, _y);
		bool insideRight = boundingbox.isInsideRight(_x, _y);

		if(insideLeft || insideRight) {
			mobEntities[i]->hit(10, insideLeft, insideRight);
			return;
		}
	}
}


void EntityManager::render() {

	for(int i = 0; i < entities.size(); i++) {
		entities[i]->render();
	}
	for(int i = 0; i < mobEntities.size(); i++) {
		mobEntities[i]->render();
	}

}

void EntityManager::renderText() {

	for(int i = 0; i < mobEntities.size(); i++) {
		YuEngine::Position mousePos = myContainer->getCamera()->getMouseAbsPos(myContainer->getInput()->getMouseX(), myContainer->getInput()->getMouseY());
		if(mobEntities[i]->getBoundingbox().isInside(mousePos.x, mousePos.y)) {

			myContainer->getFontRenderer()->renderText("Health : " + std::to_string((int)mobEntities[i]->getHealth()) + "/" + std::to_string((int)mobEntities[i]->getMaxHealth()), mousePos.x + YuEngine::FontRenderer::letterHeight*2, mousePos.y + YuEngine::FontRenderer::letterHeight, 26, 2, 1.0f,1.0f,1.0f,1.0f);
			return;
		}
	}

}